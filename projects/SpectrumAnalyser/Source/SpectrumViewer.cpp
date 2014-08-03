/*
  ==============================================================================

    SpectroscopeViewer.cpp
    Created: 27 Jul 2014 2:34:48pm
    Author:  Samuel Gaehwiler

    Heavily based on the dRowAudio Spectroscope class by David Rowland.
 
  ==============================================================================
*/

#include "SpectrumViewer.h"

#if JUCE_MAC || JUCE_IOS || DROWAUDIO_USE_FFTREAL


// static member initialisation
// ============================

const int SpectrumViewer::frequenciesToPlot[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000};
const int SpectrumViewer::numberOfFrequenciesToPlot = 29;

//==============================================================================
SpectrumViewer::SpectrumViewer (Value& repaintViewerValue,
                                drow::Buffer& magnitudeBuffer,
                                Value& detectedFrequencyValue)
  : sampleRate                {44100.0},
    repaintViewer             (var(false)),
    fftMagnitudeBuffer        {magnitudeBuffer},
    detectedFrequency         {var(0)},
    frequencyToDisplay        {var(0)},
    mouseMode                 {false},
    mouseXPosition            {0},
    heightForFrequencyCaption {20},
    gradientImage             (Image::RGB, 100, 100, false),
    scopeImage                (Image::RGB, 100, 100, false)
{
// TODO: Is this ok?
	setOpaque (true);
    
    repaintViewer.referTo (repaintViewerValue);
    
    detectedFrequency.referTo (detectedFrequencyValue);
    detectedFrequency.addListener(this);

    gradientImage.clear (scopeImage.getBounds(), Colours::black);
    scopeImage.clear (scopeImage.getBounds(), Colours::black);
    
    addAndMakeVisible (&frequencyCaption);
    
    startTimer (30);
}

SpectrumViewer::~SpectrumViewer()
{
}

void SpectrumViewer::resized()
{
    gradientImage = gradientImage.rescaled (jmax (1, getWidth()), jmax (1, getHeight() - heightForFrequencyCaption));
    createGradientImage();
    
    scopeImage = scopeImage.rescaled (jmax (1, getWidth()), jmax (1, getHeight() - heightForFrequencyCaption));

    frequencyCaption.setBounds (0, getHeight() - heightForFrequencyCaption,
                                 getWidth(), heightForFrequencyCaption);
}

void SpectrumViewer::paint(Graphics& g)
{
    g.drawImageAt (scopeImage, 0, 0, false);
    

}

//==============================================================================
void SpectrumViewer::setSampleRate (double newSampleRate)
{
    sampleRate = newSampleRate;
    frequencyCaption.setSampleRate (newSampleRate);
}


int SpectrumViewer::getHeightOfFrequencyCaption()
{
    return heightForFrequencyCaption;
}

Value & SpectrumViewer::getFrequencyToDisplay()
{
    return frequencyToDisplay;
}

void SpectrumViewer::timerCallback()
{
	const int magnitudeBufferSize = fftMagnitudeBuffer.getSize();
	float* magnitudeBuffer = fftMagnitudeBuffer.getData();

    renderScopeImage();

	// fall levels here
	for (int i = 0; i < magnitudeBufferSize; i++)
		magnitudeBuffer[i] *= JUCE_LIVE_CONSTANT (0.707f);
}

void SpectrumViewer::valueChanged (Value &value)
{
    if (!mouseMode && value.refersToSameSourceAs(detectedFrequency))
    {
        frequencyToDisplay = detectedFrequency.getValue();
    }
}


//==============================================================================
void SpectrumViewer::createGradientImage()
{
    Graphics g (gradientImage);
    ColourGradient gradient (Colours::darkgreen, 0.0f, 0.8f * gradientImage.getHeight(), Colours::black, 0.0f, gradientImage.getHeight(), false);
    g.setGradientFill(gradient);
    g.fillAll();
}

void SpectrumViewer::renderScopeImage()
{
    if (repaintViewer == true)
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
		
        const int numBins = fftMagnitudeBuffer.getSize() - 1;
        const float* data = fftMagnitudeBuffer.getData();
        
// NOTE TO DAVE96: The jlimit is not needed. Puts the load off the CPU by 1-2%.
// Original line:      float y2, y1 = jlimit (0.0f, 1.0f, float (1 + (drow::toDecibels (data[0]) / 100.0f)));
        float x = 0;
        float y = 0;
        
        // The path which will be the border of the filled area.
        Path spectrumPath;
        // Add the top left point.
        // Ensure that only values > 0 are passed to your drow::toDecibels().
        const float yInPercent = data[0]>0 ? float (1 + (drow::toDecibels (data[0]) / 100.0f)) : -0.01;
        y = h - h * yInPercent;
        // No coordinate should be NaN
        jassert (x == x && y == y);
        spectrumPath.startNewSubPath(x, y);
        
        for (int i = 0; i < numBins; ++i)
        {
            x = logTransformInRange0to1 ((i + 1.0f) / numBins) * w;
            // Ensure that only values > 0 are passed to your drow::toDecibels().
            const float yInPercent = data[i]>0 ? float (1 + (drow::toDecibels (data[i]) / 100.0f)) : -0.01;
            y = h - h * yInPercent;
            
            spectrumPath.lineTo(x, y);
            
//            g.drawLine (x1, h - h * y1,
//                        x2, h - h * y2);
//            
//            y1 = y2;
//            x1 = x2;
        }
        
        g.setColour (Colours::darkgreen);
        float lineThickness = 0.75f;
        g.strokePath (spectrumPath, PathStrokeType(lineThickness));
        
        // Bottom right point.
        spectrumPath.lineTo(x, getHeight());
        // Bottom left point.
        spectrumPath.lineTo(0, getHeight());
        spectrumPath.closeSubPath();
        
        // Draw the graph.
        const float opacity = 0.6f;
        g.setTiledImageFill(gradientImage, 0, 0, opacity);
        g.fillPath(spectrumPath);
        
        
        // Draw a vertical line at the mouse position
        if (mouseMode)
        {
            g.setColour (Colours::lightgoldenrodyellow);
            g.drawVerticalLine(mouseXPosition - 1, 0, getHeight());
                // Don't know why the -1 offset for the x position
                // is needed. (It is also needed if the drawing
                // would be placed directly on the component, i.e.
                // in the paint() function.
        }
        else
        {
            const double proportion = (double)detectedFrequency.getValue() / (sampleRate / 2.0);
            const int pitchXCoord = roundToInt (logTransformInRange0to1 (proportion) * getWidth());
            
            g.setColour (Colours::green);
            g.drawVerticalLine (pitchXCoord, 0.0f, (float) getHeight());
        }

		
		repaintViewer = false;
        
        repaint(0, 0, scopeImage.getWidth(), scopeImage.getHeight());
	}
}

void SpectrumViewer::mouseEnter (const MouseEvent &event)
{
    mouseMode = true;
}

void SpectrumViewer::mouseMove (const MouseEvent &event)
{
    mouseXPosition = event.getPosition().getX();
    
    // Results are more accurate if 1 is added to the mouse position. I assume because of
    // rounding in the log as well as in the exp transformations.
    const float normalizedXPosition = (mouseXPosition + 1) / (float)getWidth();
    const float frequency = sampleRate / 2.0f * expTransformInRange0to1 (normalizedXPosition);
    frequencyToDisplay = (int)frequency;
}

void SpectrumViewer::mouseExit (const MouseEvent &event)
{
    mouseMode = false;
}



//==============================================================================
//==============================================================================
SpectrumViewer::FrequencyCaption::FrequencyCaption()
: sampleRate {44100.0}
{
    for (int i = 0; i < numberOfFrequenciesToPlot; ++i)
    {
        // Generate the frequencyString...
        const int frequency = frequenciesToPlot[i];
        String frequencyString;
        if (frequency % 1000 == 0)
        {
            frequencyString = String (frequency/1000) + "K";
        }
        else
        {
            frequencyString = String (frequency);
        }
        
        // ... and put it into a new Label.
        Label* frequencyLabel = new Label();
        frequencyLabel->setText(frequencyString, dontSendNotification);
        
        // Figuring out the width and height of the text and setting the Label accordingly.
        Font labelFont = Font(12.0f);
        frequencyLabel->setFont(labelFont);
        frequencyLabel->setColour (Label::textColourId, Colours::lightgoldenrodyellow);
        const int textWidth = labelFont.getStringWidth (frequencyLabel->getText());
        const int textHeight = labelFont.getHeight();
        frequencyLabel->setBorderSize (BorderSize<int>(0,1,0,1));
        frequencyLabel->setSize(textWidth + 2, textHeight);
        
        frequencyLabels.add(frequencyLabel);
        addAndMakeVisible(frequencyLabel);
    }
}

SpectrumViewer::FrequencyCaption::~FrequencyCaption()
{
}

void SpectrumViewer::FrequencyCaption::paint (Graphics& g)
{
    // Background
    // ----------
    g.fillAll (Colours::black); // Clear the background
    
    // Labels and lines
    // ----------------
    static float lineLength = 5.0f;
    g.setColour (Colours::lightgoldenrodyellow);
    
    for (int i = numberOfFrequenciesToPlot - 1; i >= 0; --i)
    {
        // Figure out the line position...
        const double proportion = frequenciesToPlot[i] / (sampleRate * 0.5);
        int xPosOfLine = logTransformInRange0to1 (proportion) * getWidth();
        
        // ...and the label position.
        const int widthOfLabel = frequencyLabels[i]->getWidth();
        frequencyLabels[i]->setTopLeftPosition(xPosOfLine - widthOfLabel / 2, lineLength);
        
        // Do labels overlap? Hide if neccessary
        frequencyLabels[i]->setVisible (true);
        for (int j = i+1; j < numberOfFrequenciesToPlot; ++j)
        {
            if (frequencyLabels[j]->isVisible()
                && frequencyLabels[j]->getX() <= frequencyLabels[i]->getX() + frequencyLabels[i]->getWidth())
            {
                frequencyLabels[i]->setVisible(false);
                break;
            }
        }
        // Only show the 20K label if it isn't truncated by the border of the whole component.
        if (i == numberOfFrequenciesToPlot - 1)
        {
            if (frequencyLabels[i]->getX() + frequencyLabels[i]->getWidth() > getWidth())
            {
                frequencyLabels[i]->setVisible(false);
            }
        }
        
        if (frequencyLabels[i]->isVisible())
        {
            g.drawVerticalLine(xPosOfLine, 0.0f, lineLength);
        }
    }
}

void SpectrumViewer::FrequencyCaption::resized()
{
}

void SpectrumViewer::FrequencyCaption::setSampleRate (double newSampleRate)
{
    sampleRate = newSampleRate;
}

#endif // JUCE_MAC || JUCE_IOS || DROWAUDIO_USE_FFTREAL
