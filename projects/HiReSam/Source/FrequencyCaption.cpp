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
        frequencyLabel->setBorderSize (BorderSize<int>(0,1,0,1));
        frequencyLabel->setSize(textWidth + 2, textHeight);
        
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
    
    // Labels and lines
    // ----------------
    static float lineLength = 5.0f;
    g.setColour (Colours::white);
    
    for (int i = numberOfFrequenciesToPlot - 1; i >= 0; --i)
    {
        // Figure out the line position...
        const double proportion = frequenciesToPlot[i] / (sampleRate * 0.5);
        int xPosOfLine = logTransformInRange0to1 (proportion) * getWidth();
        
        // ...and the label position.
        const int widthOfLabel = frequencyLabels[i]->getWidth();
        frequencyLabels[i]->setTopLeftPosition(xPosOfLine - widthOfLabel / 2, lineLength);
        
        // Do labels overlap? Hide if neccessary
        frequencyLabels[i]->setVisible (true);
        for (int j = i+1; j < numberOfFrequenciesToPlot; ++j)
        {
            if (frequencyLabels[j]->isVisible()
                && frequencyLabels[j]->getX() <= frequencyLabels[i]->getX() + frequencyLabels[i]->getWidth())
            {
                frequencyLabels[i]->setVisible(false);
                break;
            }
        }
        // Only show the 20K label if it isn't truncated by the border of the whole component.
        if (i == numberOfFrequenciesToPlot - 1)
        {
            if (frequencyLabels[i]->getX() + frequencyLabels[i]->getWidth() > getWidth())
            {
                frequencyLabels[i]->setVisible(false);
            }
        }
        
        if (frequencyLabels[i]->isVisible())
        {
            g.drawVerticalLine(xPosOfLine, 0.0f, lineLength);
        }
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
