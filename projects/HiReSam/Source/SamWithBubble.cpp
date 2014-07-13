/*
  ==============================================================================

    SamWithBubble.cpp
    Created: 12 Jul 2014 9:17:15am
    Author:  Samuel Gaehwiler

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SamWithBubble.h"

//==============================================================================
SamWithBubble::SamWithBubble()
{
    pitchLabel.setColour (Label::textColourId, Colours::lightgoldenrodyellow);
//    pitchLabel.setColour (Label::backgroundColourId, Colours::red);
    Font pitchLabelFont = Font (18.0f);
    pitchLabel.setFont (pitchLabelFont);
    pitchLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible (&pitchLabel);
}

SamWithBubble::~SamWithBubble()
{
}

void SamWithBubble::paint (Graphics& g)
{
    // image
    const int borderRight = 30;
    const int borderBottom = 10;
    const int imageHeight = 150;
    const int imageWidth = 150;
    g.drawImage(ImageCache::getFromMemory (BinaryData::Samuel_Gaehwiler_png, BinaryData::Samuel_Gaehwiler_pngSize), getWidth() - imageWidth - borderRight, getHeight() - imageHeight - borderBottom, imageWidth, imageHeight, 0, 0, 300, 300);
    
    // bubble
    g.setColour (Colours::black);
    g.fillPath (bubblePath);
//    g.setColour (Colour (0xff6f6f6f));
    g.setColour (Colours::lightgoldenrodyellow);
    g.strokePath (bubblePath, PathStrokeType (5.200f));

    // bubble text
    pitchLabel.setBounds (40, 60, getWidth() - 80, 20);
    
    g.setColour (Colours::lightgoldenrodyellow);
    g.setFont (17.0f);
    Rectangle<int> bubblePathBounds = bubblePath.getBounds().getSmallestIntegerContainer();
    bubblePathBounds.removeFromTop (80);
    bubblePathBounds.removeFromLeft (20);
    const int maximumNumberOfLines = 3;
    const String bubbleText = String("Zu viel Arbeit? Ich helfe gerne.\n") + "078 624 68 64\n" + "sam@klangfreund.com";
    g.drawFittedText(bubbleText, bubblePathBounds, Justification::horizontallyCentred, maximumNumberOfLines);

    
    //    g.setColour (Colours::black);
    //    g.setFont (15.0f);
    //    g.drawFittedText ("Zviel Arbet? HiRe sam@klangfreund.com!",
    //                      0, 0, getWidth(), getHeight(),
    //                      Justification::centred, 1);

//    g.fillAll (Colours::white);   // clear the background
//
//    g.setColour (Colours::grey);
//    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
//
//    g.setColour (Colours::lightblue);
//    g.setFont (14.0f);
//    g.drawText ("SamWithBubble", getLocalBounds(),
//                Justification::centred, true);   // draw some placeholder text
}

void SamWithBubble::resized()
{
    bubblePath.clear();
    //    bubblePath.startNewSubPath (136.0f, 80.0f);
    //    bubblePath.quadraticTo (176.0f, 24.0f, 328.0f, 32.0f);
    //    bubblePath.quadraticTo (472.0f, 40.0f, 472.0f, 104.0f);
    //    bubblePath.quadraticTo (472.0f, 192.0f, 232.0f, 176.0f);
    //    bubblePath.lineTo (184.0f, 216.0f);
    //    bubblePath.lineTo (200.0f, 168.0f);
    //    bubblePath.quadraticTo (96.0f, 136.0f, 136.0f, 80.0f);
    //    bubblePath.closeSubPath();
    float mostRight = getWidth() - 10.0f;
    float width = getWidth() - 30.0f;
    bubblePath.startNewSubPath (mostRight - width, 80.0f);
    bubblePath.quadraticTo (mostRight - 0.881f * width, 24.0f, mostRight - 0.429f * width, 32.0f);
    bubblePath.quadraticTo (mostRight, 40.0f, mostRight, 104.0f);
    bubblePath.quadraticTo (mostRight, 192.0f, mostRight - 0.69f * width, 176.0f);
    bubblePath.lineTo (mostRight - 0.635f * width, 216.0f); // the tip of the bubble
    bubblePath.lineTo (mostRight - 0.810f * width, 168.0f);
    bubblePath.quadraticTo (mostRight - 1.119f * width, 136.0f, mostRight - width, 80.0f);
    bubblePath.closeSubPath();
}

void SamWithBubble::referToFrequencyTextValue (const Value & valueToReferTo)
{
    pitchLabel.getTextValue().referTo(valueToReferTo);
}