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
    : sampleRate {44100.0},
      pitch {0},
      sampleBuffer (1, 512),
      pitchTextValue ("0 Hz ()"),
      mouseMode {false},
      mouseXPosition {0}
{
    pitchDetector.setMinMaxFrequency (20, 20000);
    
    startTimer (25);
}

PitchDetectorComponent::~PitchDetectorComponent()
{
}

void PitchDetectorComponent::paint (Graphics& g)
{
    // Draw a vertical line at the mouse position
    if (mouseMode)
    {
        g.setColour (Colours::lightgoldenrodyellow);
        g.drawVerticalLine(mouseXPosition, 0, getHeight());
    }
    else
    {
        g.setColour (Colours::green);
        g.drawVerticalLine (pitchXCoord.getCurrent(), 0.0f, (float) getHeight());
    }
}

void PitchDetectorComponent::resized()
{
}

void PitchDetectorComponent::timerCallback()
{
    if (!mouseMode)
    {
        setPitchTextValue(pitch);
        
        const double proportion = pitch / (sampleRate / 2.0);
        pitchXCoord = roundToInt (logTransformInRange0to1 (proportion) * getWidth());
        
        if (! pitchXCoord.areEqual())
        {
            repaint (pitchXCoord.getPrevious(), 0, 1, getHeight());
            repaint (pitchXCoord.getCurrent(), 0, 1, getHeight());
        }
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

Value& PitchDetectorComponent::getPitchTextValue()
{
    return pitchTextValue;
}

void PitchDetectorComponent::mouseEnter (const MouseEvent &event)
{
    mouseMode = true;
}

void PitchDetectorComponent::mouseMove (const MouseEvent &event)
{
    mouseXPosition = event.getPosition().getX();
    
    // Results are more accurate if 1 is added to the mouse position. I assume because of
    // rounding in the log as well as in the exp transformations.
    const float normalizedXPosition = (mouseXPosition + 1) / (float)getWidth();
    const float frequency = sampleRate / 2.0f * expTransformInRange0to1 (normalizedXPosition);
    setPitchTextValue (frequency);
}

void PitchDetectorComponent::mouseExit (const MouseEvent &event)
{
    mouseMode = false;
}

void PitchDetectorComponent::setPitchTextValue (int pitch)
{
    pitchString = String (pitch);
    pitchString << " Hz";
    if (pitch > 7) // At 7 Hz, the function below returns "-1" where a letter in front of it is missing.
    {
// TO DAVE: At 7 Hz, the function below returns "-1" where a letter in front of it is missing.
        pitchString << " (" << drow::Pitch::fromFrequency (pitch).getMidiNoteName() << ")";
    }
    pitchTextValue = pitchString;
}
