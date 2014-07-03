/*
  ==============================================================================

  This file is part of the dRowAudio JUCE module
  Copyright 2004-13 by dRowAudio.

  ------------------------------------------------------------------------------

  dRowAudio is provided under the terms of The MIT License (MIT):

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
  SOFTWARE.

  ==============================================================================
*/

#include "Spectroscope.h"

#if JUCE_MAC || JUCE_IOS || DROWAUDIO_USE_FFTREAL

// static member initialisation
// ============================

const int Spectroscope::frequenciesToPlot[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000};
const int Spectroscope::numberOfFrequenciesToPlot = 29;

//==============================================================================
Spectroscope::Spectroscope (int fftSizeLog2)
:   sampleRate      {44100.0},
    fftEngine       (fftSizeLog2),
    needsRepaint    {true},
	tempBlock       (fftEngine.getFFTSize()),
	circularBuffer  (fftEngine.getMagnitudesBuffer().getSize() * 4)
{
	setOpaque (true);

	fftEngine.setWindowType (drow::Window::Hann);
	numBins = fftEngine.getFFTProperties().fftSizeHalved;
    
    circularBuffer.reset();
    
    scopeImage = Image (Image::RGB,
                        100, 100,
                        false);
    scopeImage.clear (scopeImage.getBounds(), Colours::black);
}

Spectroscope::~Spectroscope()
{
}

void Spectroscope::resized()
{
    scopeImage = scopeImage.rescaled (jmax (1, getWidth()), jmax (1, getHeight()));
}

void Spectroscope::paint(Graphics& g)
{
    g.drawImageAt (scopeImage, 0, 0, false);
}

//==============================================================================
void Spectroscope::setSampleRate (double newSampleRate)
{
    sampleRate = newSampleRate;
}

void Spectroscope::copySamples (const float* samples, int numSamples)
{
	circularBuffer.writeSamples (samples, numSamples);
	needToProcess = true;
}

void Spectroscope::timerCallback()
{
	const int magnitudeBufferSize = fftEngine.getMagnitudesBuffer().getSize();
	float* magnitudeBuffer = fftEngine.getMagnitudesBuffer().getData();

    renderScopeImage();

	// fall levels here
	for (int i = 0; i < magnitudeBufferSize; i++)
		magnitudeBuffer[i] *= JUCE_LIVE_CONSTANT (0.707f);
}

void Spectroscope::process()
{
    jassert (circularBuffer.getNumFree() != 0); // buffer is too small!
    
    while (circularBuffer.getNumAvailable() > fftEngine.getFFTSize())
	{
		circularBuffer.readSamples (tempBlock.getData(), fftEngine.getFFTSize());
		fftEngine.performFFT (tempBlock);
		fftEngine.updateMagnitudesIfBigger();
		
		needsRepaint = true;
	}
}

void Spectroscope::flagForRepaint()
{	
    needsRepaint = true;
    repaint();
}

//==============================================================================
void Spectroscope::renderScopeImage()
{
    if (needsRepaint)
	{
        Graphics g (scopeImage);
        
		const int w = getWidth();
		const int h = getHeight();
        
		g.setColour (Colours::black);
		g.fillAll();
        
        // Draw the background lines
        // -------------------------
        g.setColour (Colours::darkgreen.darker().darker());
        
        for (int i = 0; i < numberOfFrequenciesToPlot; ++i)
        {
            const double proportion = frequenciesToPlot[i] / (sampleRate * 0.5);
            int xPos = logTransformInRange0to1 (proportion) * getWidth();
            g.drawVerticalLine(xPos, 0.0f, getHeight());
        }
        
        // Draw the actual result from the FFT
        // -----------------------------------
		g.setColour (Colours::white);
		
        const int numBins = fftEngine.getMagnitudesBuffer().getSize() - 1;
        const float* data = fftEngine.getMagnitudesBuffer().getData();
        
// NOTE TO DAVE96: The jlimit is not needed. Puts the load off the CPU by 1-2%.
// Original line:      float y2, y1 = jlimit (0.0f, 1.0f, float (1 + (drow::toDecibels (data[0]) / 100.0f)));
        float y2, y1 = float (1 + (drow::toDecibels (data[0]) / 100.0f));
        float x2, x1 = 0;
        
        // The path which will be the border of the filled area.
        Path spectrumPath;
        // Add the top left point.
        spectrumPath.startNewSubPath(x1, h - h * y1);
        
        for (int i = 0; i < numBins; ++i)
        {
// NOTE TO DAVE96: Same as above.
            y2 = float (1 + (drow::toDecibels (data[i]) / 100.0f));
            x2 = logTransformInRange0to1 ((i + 1.0f) / numBins) * w;
            
            spectrumPath.lineTo(x2, h - h * y2);
            
//            g.drawLine (x1, h - h * y1,
//                        x2, h - h * y2);
//            
//            y1 = y2;
//            x1 = x2;
        }
        
        g.setColour (Colours::darkgreen);
        float lineThickness = 1.0f;
        g.strokePath (spectrumPath, PathStrokeType(lineThickness));
        
        // Bottom right point.
        spectrumPath.lineTo(x2, getHeight());
        // Bottom left point.
        spectrumPath.lineTo(x1, getHeight());
        spectrumPath.closeSubPath();
        
        // Draw the graph.
        ColourGradient gradient (Colours::darkgreen, 0.0f, 0.8f * getHeight(), Colours::black, 0.0f, getHeight(), false);
        g.setGradientFill(gradient);
        g.setOpacity(0.6f);
        //g.setColour (Colours::green.withAlpha(0.8f));
        g.fillPath(spectrumPath);
		
		needsRepaint = false;
        
        repaint();
	}
}

#endif // JUCE_MAC || JUCE_IOS || DROWAUDIO_USE_FFTREAL
