/*
  ==============================================================================

    SamWithBubble.h
    Created: 12 Jul 2014 9:17:15am
    Author:  Samuel Gaehwiler

  ==============================================================================
*/

#ifndef SAM_WITH_BUBBLE_H_INCLUDED
#define SAM_WITH_BUBBLE_H_INCLUDED

#include "SpectrumAnalyserHeader.h"

//==============================================================================
/*
*/
class SamWithBubble    : public Component
{
public:
    SamWithBubble();
    ~SamWithBubble();

    void paint (Graphics&);
    void resized();
    void referToFrequencyTextValue (const Value & valueToReferTo);
    
private:
    Path bubblePath;
    Label pitchLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamWithBubble)
};


#endif  // SAM_WITH_BUBBLE_H_INCLUDED
