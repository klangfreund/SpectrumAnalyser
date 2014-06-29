/*
  ==============================================================================

    FrequencyCaptions.cpp
    Created: 28 Jun 2014 8:51:49pm
    Author:  Samuel Gaehwiler

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "FrequencyCaption.h"

// static member initialisation
// ============================

const int FrequencyCaption::frequenciesToPlot[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000};
const int FrequencyCaption::numberOfFrequenciesToPlot = 29;

//==============================================================================
FrequencyCaption::FrequencyCaption()
    : sampleRate (44100.0)
{
    for (int i = 0; i < numberOfFrequenciesToPlot; ++i)
    {
        // Generate the frequencyString...
        const int frequency = frequenciesToPlot[i];
        String frequencyString;
        if (frequency % 1000 == 0)
        {
            frequencyString = String (frequency/1000) + "K";
        }
        else
        {
            frequencyString = String (frequency);
        }
        
        // ... and put it into a new Label.
        Label* frequencyLabel = new Label();
        frequencyLabel->setText(frequencyString, dontSendNotification);
        
        // Figuring out the width and height of the text and setting the Label accordingly.
        Font labelFont = Font(12.0f);
        frequencyLabel->setFont(labelFont);
        frequencyLabel->setColour (Label::textColourId, Colours::white);
        const int textWidth = labelFont.getStringWidth (frequencyLabel->getText());
        const int textHeight = labelFont.getHeight();
        frequencyLabel->setBorderSize (BorderSize<int>(0,0,0,0));
        frequencyLabel->setSize(textWidth, textHeight);
        
        frequencyLabels.add(frequencyLabel);
        addAndMakeVisible(frequencyLabel);
    }
}

FrequencyCaption::~FrequencyCaption()
{
}

void FrequencyCaption::paint (Graphics& g)
{
    // Background
    // ----------
    g.fillAll (Colours::black); // Clear the background
    
    // Lines and the labels
    // --------------------
    static float lineLength = 5.0f;
    g.setColour (Colours::white);
    
    for (int i = 0; i < numberOfFrequenciesToPlot; ++i)
    {
        const double proportion = frequenciesToPlot[i] / (sampleRate * 0.5);
        int xPos = logTransformInRange0to1 (proportion) * getWidth();
        g.drawVerticalLine(xPos, 0.0f, lineLength);
        
        const int widthOfLabel = frequencyLabels[i]->getWidth();
        frequencyLabels[i]->setTopLeftPosition(xPos - widthOfLabel / 2, lineLength);
    }
//
//    g.setColour (Colours::lightblue);
//    g.setFont (14.0f);
//    g.drawText ("FrequencyCaptions", getLocalBounds(),
//                Justification::centred, true);   // draw some placeholder text
}

void FrequencyCaption::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void FrequencyCaption::setSampleRate (double newSampleRate)
{
    sampleRate = newSampleRate;
}
