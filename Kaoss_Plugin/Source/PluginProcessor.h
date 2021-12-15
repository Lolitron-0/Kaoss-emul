/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "vector"
#include "algorithm"
#include "AudioEffectBase.h"
#include "Looper.h"
#include "RevLooper.h"



using namespace juce;
using namespace juce::dsp;
using namespace std;

//==============================================================================


class HandlerProcessor : public juce::AudioProcessor
{
public:
    //==============================================================================
    HandlerProcessor();
    ~HandlerProcessor() override;

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    void fillDelayBuffer(int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData);

    void getFromDelayBuffer(juce::AudioBuffer<float>& buffer, int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData);

    void feedbackDelay(int channel, const int bufferLength, const int delayBufferLength, float* dryBuffer);


    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    //==============================================================================

    int mSampleRate;
    int x = 0, y = 0;
    

private:

    vector<AudioEffectBase*> mEffectRack;
    RevLooper looper;

    AudioBuffer <float> mDelayBuffer;
    AudioBuffer <float> mLooperBuffer;
    bool mLooperBufferFilled=false;
    int mWritePosition{ 0 };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HandlerProcessor)
};

template<class Type> bool contains(vector<Type> v, Type val)
{
    return std::find(v.begin(), v.end(), val) != v.end();
}