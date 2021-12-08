/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Kaoss_PluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Kaoss_PluginAudioProcessorEditor (Kaoss_PluginAudioProcessor&);
    ~Kaoss_PluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Kaoss_PluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Kaoss_PluginAudioProcessorEditor)
};
