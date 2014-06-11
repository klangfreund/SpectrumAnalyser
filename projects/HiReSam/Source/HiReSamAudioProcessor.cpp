/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "HiReSamAudioProcessor.h"
#include "HiReSamAudioProcessorEditor.h"


//==============================================================================
HiReSamAudioProcessor::HiReSamAudioProcessor()
    : hiReSamAudioProcessorEditor {nullptr}
{
}

HiReSamAudioProcessor::~HiReSamAudioProcessor()
{
}

//==============================================================================
const String HiReSamAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int HiReSamAudioProcessor::getNumParameters()
{
    return 0;
}

float HiReSamAudioProcessor::getParameter (int index)
{
    return 0.0f;
}

void HiReSamAudioProcessor::setParameter (int index, float newValue)
{
}

const String HiReSamAudioProcessor::getParameterName (int index)
{
    return String::empty;
}

const String HiReSamAudioProcessor::getParameterText (int index)
{
    return String::empty;
}

const String HiReSamAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String HiReSamAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool HiReSamAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool HiReSamAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool HiReSamAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HiReSamAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HiReSamAudioProcessor::silenceInProducesSilenceOut() const
{
    return true;
}

double HiReSamAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HiReSamAudioProcessor::getNumPrograms()
{
    return 0;
}

int HiReSamAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HiReSamAudioProcessor::setCurrentProgram (int index)
{
}

const String HiReSamAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void HiReSamAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void HiReSamAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void HiReSamAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void HiReSamAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);

        if (channel == 0 && hiReSamAudioProcessorEditor != nullptr)
        {
            hiReSamAudioProcessorEditor->spectroscope.copySamples(channelData, buffer.getNumSamples());
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
bool HiReSamAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* HiReSamAudioProcessor::createEditor()
{
    hiReSamAudioProcessorEditor = new HiReSamAudioProcessorEditor (this);
    return hiReSamAudioProcessorEditor;
}

//==============================================================================
void HiReSamAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HiReSamAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HiReSamAudioProcessor();
}
