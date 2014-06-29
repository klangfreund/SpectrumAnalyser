/*
  ==============================================================================

    FrequencyCaptions.h
    Created: 28 Jun 2014 8:51:49pm
    Author:  Samuel Gaehwiler

  ==============================================================================
*/

#ifndef FREQUENCYCAPTION_H_INCLUDED
#define FREQUENCYCAPTION_H_INCLUDED

#include "HiReSamHeader.h"

//==============================================================================
/*
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
    static const int frequenciesToPlot[];
    static const int numberOfFrequenciesToPlot;
    OwnedArray<Label> frequencyLabels;
    
    double sampleRate;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FrequencyCaption)
};


#endif  // FREQUENCYCAPTION_H_INCLUDED
