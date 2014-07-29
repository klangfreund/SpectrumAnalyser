/*
  ==============================================================================

    PitchDetectorComponent.h
    Created: 28 Dec 2012 5:52:04pm
    Author:  David Rowland

  ==============================================================================
*/

#ifndef PITCH_DETECTOR_COMPONENT_H
#define PITCH_DETECTOR_COMPONENT_H

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
    drow::PitchDetector pitchDetector;

    drow::StateVariable<int> pitchXCoord;
    String pitchString;
    Value pitchTextValue;
    bool mouseMode;
    int mouseXPosition;
    
    CriticalSection detectorLock;
    
    void inline setPitchTextValue (int pitch);
    
	//==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PitchDetectorComponent)
};


#endif  // PITCH_DETECTOR_COMPONENT_H
