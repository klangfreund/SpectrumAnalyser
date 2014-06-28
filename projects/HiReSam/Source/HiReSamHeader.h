/*
  ==============================================================================

    HiReSamHeader.h
    Created: 10 Jun 2014 8:19:00pm
    Author:  Samuel Gaehwiler

  ==============================================================================
*/

#ifndef HIRESAMHEADER_H_INCLUDED
#define HIRESAMHEADER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

// Switches
// --------

#ifndef    JUCE_ENABLE_LIVE_CONSTANT_EDITOR
#define JUCE_ENABLE_LIVE_CONSTANT_EDITOR 1
#endif

// Helper Functions
// ----------------

inline float logTransformInRange0to1 (const float valueToScale) noexcept
{
    const float maximum = JUCE_LIVE_CONSTANT (1000.0f);
    return drow::logBase10Scale (valueToScale, 1.0f, maximum);
}




#endif  // HIRESAMHEADER_H_INCLUDED
