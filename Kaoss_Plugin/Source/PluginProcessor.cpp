/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


using namespace juce;
using namespace juce::dsp;

//==============================================================================
HandlerProcessor::HandlerProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    )
#endif
{
    looper.setOn(true);
    mEffectRack.push_back(&looper);

}

HandlerProcessor::~HandlerProcessor()
{
}

//==============================================================================
const juce::String HandlerProcessor::getName() const
{
    return JucePlugin_Name;
}

bool HandlerProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool HandlerProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool HandlerProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double HandlerProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HandlerProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int HandlerProcessor::getCurrentProgram()
{
    return 0;
}

void HandlerProcessor::setCurrentProgram(int index)
{
}

const juce::String HandlerProcessor::getProgramName(int index)
{
    return {};
}

void HandlerProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================
void HandlerProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    ProcessSpec spec = { sampleRate, static_cast<juce::uint32> (samplesPerBlock), getTotalNumInputChannels() };

    for (int i=0;i<mEffectRack.size();i++)
        mEffectRack[i]->prepare(spec);

    //const int delayBufferSize = (sampleRate + samplesPerBlock) * 1.;
    //mDelayBuffer.setSize(getTotalNumInputChannels(), delayBufferSize);

    //this->mSampleRate = sampleRate;
}

void HandlerProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HandlerProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void HandlerProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    AudioBlock<float> block(buffer);
    ProcessContextReplacing<float> context(block);

    for (int i = 0; i < mEffectRack.size(); i++)
    {
        if (!mEffectRack[i]->isOn()) continue;

        if (!mEffectRack[i]->isFrozen())
            mEffectRack[i]->updateParams(x, y);

        mEffectRack[i]->process(buffer);
    }

    for (int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); i++)
        buffer.clear(i, 0, buffer.getNumSamples());
}

//put samples from main buffer to delayBuffer (wrapping around zero if refill)
void HandlerProcessor::fillDelayBuffer(int channel, const int bufferLength, const int delayBufferLength,
    const float* bufferData, const float* delayBufferData)
{
    if (delayBufferLength > mWritePosition + bufferLength) //we have enough space in delayBuffer to add next block to it 
    {
        mDelayBuffer.copyFromWithRamp(channel, mWritePosition, bufferData, bufferLength, 0.8f, 0.8f);
    }
    else
    {
        const int bufferRemaining = delayBufferLength - mWritePosition;

        mDelayBuffer.copyFromWithRamp(channel, mWritePosition, bufferData, bufferRemaining, 0.8f, 0.8f);  //add piece of block that fits
        mDelayBuffer.copyFromWithRamp(channel, 0, bufferData, bufferLength - bufferRemaining, 0.8f, 0.8f);  //wrap around zero and add the rest
    }
}

void HandlerProcessor::getFromDelayBuffer(juce::AudioBuffer<float>& buffer, int channel, const int bufferLength, const int delayBufferLength,
    const float* bufferData, const float* delayBufferData)
{
    int delayOffset = 200;
    const int readPosition = static_cast<int>(delayBufferLength + mWritePosition - (mSampleRate * delayOffset / 1000.)) % delayBufferLength;  //position where we are writing but back in time to delayOffset

    if (delayBufferLength > readPosition + bufferLength)  //if our back in time segment is less than delayBufferLength
    {
        buffer.copyFrom(channel, 0, delayBufferData + readPosition, bufferLength); //insert back in time segment in main buffer
    }
    else
    {
        const int bufferRemaining = delayBufferLength - readPosition;
        buffer.copyFrom(channel, 0, delayBufferData + readPosition, bufferRemaining);   //insert a piece
        buffer.copyFrom(channel, bufferRemaining, delayBufferData, bufferLength - bufferRemaining);  //wrap and add remaining from the segment start
    }
}

void HandlerProcessor::feedbackDelay(int channel, const int bufferLength, const int delayBufferLength, float* dryBuffer)
{
    const float feedback = 1;
    if (delayBufferLength > bufferLength + mWritePosition)
    {
        mDelayBuffer.addFromWithRamp(channel, mWritePosition, dryBuffer, bufferLength, feedback, feedback);
    }
    else
    {
        const int bufferRemaining = delayBufferLength - mWritePosition;

        mDelayBuffer.addFromWithRamp(channel, bufferRemaining, dryBuffer, bufferRemaining, feedback, feedback);
        mDelayBuffer.addFromWithRamp(channel, 0, dryBuffer, bufferLength - bufferRemaining, feedback, feedback);
    }
}

//==============================================================================
bool HandlerProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* HandlerProcessor::createEditor()
{
    return new HandleProcessorEditor(*this);
    //return new GenericAudioProcessorEditor(*this);
}

//==============================================================================
void HandlerProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HandlerProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HandlerProcessor();
}
