/*
  ==============================================================================

    PitchDetectorComponent.h
    Created: 28 Dec 2012 5:52:04pm
    Author:  David Rowland

  ==============================================================================
*/

#ifndef __PITCHDETECTORCOMPONENT_H_FCCBFF40__
#define __PITCHDETECTORCOMPONENT_H_FCCBFF40__

#include "HiReSamHeader.h"

//==============================================================================
/*
*/
class PitchDetectorComponent :  public Component,
                                public Timer
{
public:
	//==============================================================================
    PitchDetectorComponent();

    ~PitchDetectorComponent();

    void paint (Graphics&);
    
    void resized();

    void timerCallback();
    
	//==============================================================================
    void setSampleRate (double newSampleRate);
    
    void processBlock (const float* inputChannelData, int numSamples);
    
    Value& getPitchTextValue();
    
    void mouseEnter (const MouseEvent &event) override;
    
    void mouseMove (const MouseEvent &event) override;
    
    void mouseExit (const MouseEvent &event) override;

private:
	//==============================================================================
    double sampleRate;
    int pitch;
    AudioSampleBuffer sampleBuffer;
    drow::PitchDetector pitchDetector;

    drow::StateVariable<int> pitchXCoord;
    String pitchString;
    Value pitchTextValue;
    bool drawMousePosition;
    int mouseXPosition;
    
    CriticalSection detectorLock;
    
	//==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PitchDetectorComponent)
};


#endif  // __PITCHDETECTORCOMPONENT_H_FCCBFF40__
