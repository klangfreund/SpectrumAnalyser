/*
  ==============================================================================

    PitchDetectorComponent.cpp
    Created: 28 Dec 2012 5:52:04pm
    Author:  David Rowland

  ==============================================================================
*/

#include "PitchDetectorComponent.h"

//==============================================================================
PitchDetectorComponent::PitchDetectorComponent()
    : sampleRate (44100.0),
      pitch (0.0),
      sampleBuffer (1, 512)
{
    addAndMakeVisible (&pitchLabel);
    pitchLabel.setColour (Label::textColourId, Colours::green);
    
    pitchDetector.setMinMaxFrequency(20, 20000);
    
    startTimer (25);
}

PitchDetectorComponent::~PitchDetectorComponent()
{
}

void PitchDetectorComponent::paint (Graphics& g)
{
    g.setColour (Colours::green);
    g.drawVerticalLine (pitchXCoord.getCurrent(), 0.0f, (float) getHeight());
}

void PitchDetectorComponent::resized()
{
    pitchLabel.setBounds (getLocalBounds().removeFromTop (20).removeFromRight (150));
}

void PitchDetectorComponent::timerCallback()
{
    pitchString = String (pitch, 2);
    pitchString << " Hz" << " (" << drow::Pitch::fromFrequency (pitch).getMidiNoteName() << ")";
    pitchLabel.setText (pitchString, dontSendNotification);

    const double proportion = pitch / (sampleRate / 2);
    const int w = getWidth();
    pitchXCoord = roundToInt (logTransformInRange0to1 (proportion) * w);

    if (! pitchXCoord.areEqual())
    {
        repaint (pitchXCoord.getPrevious(), 0, 1, getHeight());
        repaint (pitchXCoord.getCurrent(), 0, 1, getHeight());
    }
}

//==============================================================================
void PitchDetectorComponent::setSampleRate (double newSampleRate)
{
    sampleRate = newSampleRate;
    
    const ScopedLock sl (detectorLock);
    pitchDetector.setSampleRate (sampleRate);
}

void PitchDetectorComponent::processBlock (const float* inputChannelData, int numSamples)
{
    const ScopedLock sl (detectorLock);
    pitchDetector.processSamples (inputChannelData, numSamples);
    pitch = pitchDetector.getPitch();
}
