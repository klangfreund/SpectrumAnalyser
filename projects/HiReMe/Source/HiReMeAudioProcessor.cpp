/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "HiReMeAudioProcessor.h"
#include "HiReMeAudioProcessorEditor.h"


//==============================================================================
HiReMeAudioProcessor::HiReMeAudioProcessor()
    : hiReMeAudioProcessorEditor {nullptr}
{
}

HiReMeAudioProcessor::~HiReMeAudioProcessor()
{
}

//==============================================================================
const String HiReMeAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int HiReMeAudioProcessor::getNumParameters()
{
    return 0;
}

float HiReMeAudioProcessor::getParameter (int index)
{
    return 0.0f;
}

void HiReMeAudioProcessor::setParameter (int index, float newValue)
{
}

const String HiReMeAudioProcessor::getParameterName (int index)
{
    return String::empty;
}

const String HiReMeAudioProcessor::getParameterText (int index)
{
    return String::empty;
}

const String HiReMeAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String HiReMeAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool HiReMeAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool HiReMeAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool HiReMeAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HiReMeAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HiReMeAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double HiReMeAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HiReMeAudioProcessor::getNumPrograms()
{
    return 0;
}

int HiReMeAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HiReMeAudioProcessor::setCurrentProgram (int index)
{
}

const String HiReMeAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void HiReMeAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void HiReMeAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void HiReMeAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void HiReMeAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);

        if (channel == 0 && hiReMeAudioProcessorEditor != nullptr)
        {
            hiReMeAudioProcessorEditor->spectroscope.copySamples(channelData, buffer.getNumSamples());
        }
    }

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

//==============================================================================
bool HiReMeAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* HiReMeAudioProcessor::createEditor()
{
    hiReMeAudioProcessorEditor = new HiReMeAudioProcessorEditor (this);
    return hiReMeAudioProcessorEditor;
}

//==============================================================================
void HiReMeAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HiReMeAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HiReMeAudioProcessor();
}
