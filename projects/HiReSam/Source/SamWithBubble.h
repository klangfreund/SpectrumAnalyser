/*
  ==============================================================================

    SamWithBubble.h
    Created: 12 Jul 2014 9:17:15am
    Author:  Samuel Gaehwiler

  ==============================================================================
*/

#ifndef SAMWITHBUBBLE_H_INCLUDED
#define SAMWITHBUBBLE_H_INCLUDED

#include "HiReSamHeader.h"

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

private:
    Path bubblePath;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamWithBubble)
};


#endif  // SAMWITHBUBBLE_H_INCLUDED
