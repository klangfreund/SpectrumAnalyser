/*
  ==============================================================================

    SpectrumAnalyserAudioProcessorEditor.cpp
    Created: 10 Jun 2014 8:19:00pm
    Author:  Samuel Gaehwiler

  ==============================================================================
*/

#include "SpectrumAnalyserAudioProcessor.h"
#include "SpectrumAnalyserAudioProcessorEditor.h"


//==============================================================================
SpectrumAnalyserAudioProcessorEditor::SpectrumAnalyserAudioProcessorEditor (SpectrumAnalyserAudioProcessor* ownerFilter,
                                                                            Value& repaintSpectrumViewer,
                                                                            drow::Buffer& spectrumMagnitudeBuffer,
                                                                            Value& detectedFrequency)
    : AudioProcessorEditor (ownerFilter),
      spectrumViewer (repaintSpectrumViewer, spectrumMagnitudeBuffer, detectedFrequency)
{
    // The plugin's initial editor size.
    setSize (1000, 500);
    
    sampleRate.addListener (this);
    // The sampleRate has already been set in the SpectrumAnalyserAudioProcessor
    // before the creation of the SpectrumAnalyserAudioProcessorEditor.
    // Because of this it is important to have the referTo call after the
    // addListener. Only in this order the valueChanged member function
    // will be called implicitly.
    sampleRate.referTo (getProcessor()->sampleRate);
    
    header.setText("High Resolution Spectrum Analyse Meter", dontSendNotification);
    Font headerFont = Font (18.0f);
    header.setFont (headerFont);
    header.setJustificationType(Justification::centred);
    header.setColour (Label::textColourId, Colours::lightgoldenrodyellow);
    header.setColour (Label::backgroundColourId, Colours::black);
    
    samWithBubble.referToFrequencyValue (spectrumViewer.getFrequencyToDisplay());
    
    addAndMakeVisible (&header);
    addAndMakeVisible (&spectrumViewer);
    addAndMakeVisible (&samWithBubble);
}

SpectrumAnalyserAudioProcessorEditor::~SpectrumAnalyserAudioProcessorEditor()
{
}

//==============================================================================
void SpectrumAnalyserAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);
}

void SpectrumAnalyserAudioProcessorEditor::resized()
{
// TODO: Move this into a resizer component.
    const int minWidth = 360;
    const int minHeight = 320;
    if (getWidth() < minWidth || getHeight() < minHeight)
    {
        setSize (jmax (minWidth, getWidth()), jmax (minHeight, getHeight()));
    }
// END TODO
    
    header.setBounds(0, 0, getWidth(), 24);
    
    spectrumViewer.setBounds (0, header.getHeight(), getWidth(), getHeight() - header.getHeight());

    const int widthForSamWithBubble = 280; //= jmin (320, getWidth() - minimalWithForSpectroscope);
    const int maxHeight = getHeight() - header.getHeight();
    const int height = jmin (310, maxHeight);
    samWithBubble.setBounds(getWidth() - widthForSamWithBubble, header.getHeight(), widthForSamWithBubble, height);
}

void SpectrumAnalyserAudioProcessorEditor::valueChanged (Value & value)
{
    if (value.refersToSameSourceAs (sampleRate))
    {
        spectrumViewer.setSampleRate (sampleRate.getValue());
    }
}

SpectrumAnalyserAudioProcessor* SpectrumAnalyserAudioProcessorEditor::getProcessor() const
{
    return static_cast <SpectrumAnalyserAudioProcessor*> (getAudioProcessor());
}
