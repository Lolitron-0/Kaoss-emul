/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
using namespace juce;
using namespace juce::dsp;

//==============================================================================
/**
*/
class HandleProcessorEditor : public juce::AudioProcessorEditor,
    private juce::Slider::Listener
{
public:
    HandleProcessorEditor(HandlerProcessor&);
    ~HandleProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    HandlerProcessor& audioProcessor;


    juce::Slider xTest;
    juce::Slider yTest;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HandleProcessorEditor)
};

