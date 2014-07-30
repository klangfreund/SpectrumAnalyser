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

#ifndef SPECTRUM_VIEWER_H__
#define SPECTRUM_VIEWER_H__

#include "HiReSamHeader.h"

#if JUCE_MAC || JUCE_IOS || DROWAUDIO_USE_FFTREAL

//==============================================================================
/** Creates a standard Spectroscope.
    This will display the amplitude of each frequency bin from an FFT in a
    continuous line which will decay with time.
    This is very simple to use, it is a GraphicalComponent so just register one
    with a TimeSliceThread, make sure its running and then continually call the
    copySamples() method. The FFT itself will be performed on a background thread.
 */
class SpectrumViewer :  public Component,
                        public Timer
{
public:
    //==============================================================================
    /** Provide it with the parameters from the SpectrumViewer.
     */
	SpectrumViewer (Value& repaintViewerValue,
                    drow::Buffer& magnitudeBuffer,
                    Value& pitch);
	
    /** Destructor. */
	~SpectrumViewer();
	
    /** @internal */
	void resized() override;
	
    /** @internal */
	void paint (Graphics &g) override;

    //==============================================================================
    void setSampleRate (double newSampleRate);
    
    int getHeightOfFrequencyCaption();

	void timerCallback() override;
    
    void mouseEnter (const MouseEvent &event) override;
    
    void mouseMove (const MouseEvent &event) override;
    
    void mouseExit (const MouseEvent &event) override;
	

private:
    //==============================================================================
    static const int frequenciesToPlot[];
    static const int numberOfFrequenciesToPlot;
    
    double sampleRate;
    Value repaintViewer;
    drow::Buffer& fftMagnitudeBuffer;
    
    Value pitchValue;
    bool mouseMode;
    int mouseXPosition;
    
    //==============================================================================
    /*  The numbers below the graph, indication the frequency.
     */
    class FrequencyCaption    : public Component
    {
    public:
        FrequencyCaption();
        ~FrequencyCaption();
        
        void paint (Graphics&);
        void resized();
        
        void setSampleRate (double newSampleRate);
        
    private:
        OwnedArray<Label> frequencyLabels;
        
        double sampleRate;
    };
    //==============================================================================
    
    FrequencyCaption frequencyCaption;
    int heightForFrequencyCaption;
	
    Image gradientImage;
    Image scopeImage;
    
    void createGradientImage();
    void renderScopeImage();
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectrumViewer);
};

#endif
#endif  // SPECTRUM_VIEWER_H__