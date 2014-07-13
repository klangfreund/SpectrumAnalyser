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
// An ugly hack (= redefinition) to disable the LIVE_CONSTANT_EDITOR.
#define JUCE_LIVE_CONSTANT(initialValue) \
initialValue

#ifndef    JUCE_ENABLE_REPAINT_DEBUGGING
  //#define JUCE_ENABLE_REPAINT_DEBUGGING 1
#endif

// Helper Functions
// ----------------

/**
 *  @return a value between 0 and 1.
 */
inline float logTransformInRange0to1 (const float between0and1)
{
    const float minimum = 1.0f;
    const float maximum = JUCE_LIVE_CONSTANT (1000.0f);
    // return drow::logBase10Scale (frequency, 1.0f, maximum);
    return log10 (minimum + ((maximum - minimum) * between0and1)) / log10 (maximum);
}

/**
 *  @return a value between 0 and 1.
 */
inline float expTransformInRange0to1 (const float between0and1)
{
    const float minimum = 1.0f;
    const float maximum = JUCE_LIVE_CONSTANT (1000.0f);
    return (pow(maximum, between0and1) - minimum) / (maximum - minimum);
}




#endif  // HIRESAMHEADER_H_INCLUDED
