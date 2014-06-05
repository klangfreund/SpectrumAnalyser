/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "HiReMeAudioProcessor.h"
#include "HiReMeAudioProcessorEditor.h"


//==============================================================================
HiReMeAudioProcessorEditor::HiReMeAudioProcessorEditor (HiReMeAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
    // This is where our plugin's editor size is set.
    setSize (400, 300);
}

HiReMeAudioProcessorEditor::~HiReMeAudioProcessorEditor()
{
}

//==============================================================================
void HiReMeAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);
    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Zviel Arbet? HiRe sam@klangfreund.com!",
                      0, 0, getWidth(), getHeight(),
                      Justification::centred, 1);
}
