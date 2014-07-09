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

// Preprocessor business
// ---------------------

// The DEBUG flag enables JUCE_DEBUG.
// JUCE_DEBUG enables JUCE_ENABLE_LIVE_CONSTANT_EDITOR.
// Therefore you can't turn off the live constant editor in debug mode
// by not defining JUCE_ENABLE_LIVE_CONSTANT_EDITOR.
//
// An ugly hack (= redefinition) to disable the LIVE_CONSTANT_EDITOR
#define JUCE_LIVE_CONSTANT(initialValue) \
initialValue

#ifndef    JUCE_ENABLE_REPAINT_DEBUGGING
  //#define JUCE_ENABLE_REPAINT_DEBUGGING 1
#endif

// Helper Functions
// ----------------

inline float logTransformInRange0to1 (const float valueToScale) noexcept
{
    const float maximum = JUCE_LIVE_CONSTANT (1000.0f);
    return drow::logBase10Scale (valueToScale, 1.0f, maximum);
}




#endif  // HIRESAMHEADER_H_INCLUDED
