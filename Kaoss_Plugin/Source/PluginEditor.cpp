/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace juce;

//==============================================================================
HandleProcessorEditor::HandleProcessorEditor(HandlerProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(400, 300);

    xTest.setSliderStyle(juce::Slider::LinearBarVertical);
    xTest.setRange(0., 100., 1.0);
    xTest.setValue(0.0);
    xTest.addListener(this);
    xTest.setName("xTest");

    addAndMakeVisible(&xTest);

    yTest.setSliderStyle(juce::Slider::LinearBarVertical);
    yTest.setRange(0., 100., 1.0);
    yTest.setValue(0.0);
    yTest.addListener(this);
    yTest.setName("yTest");


    addAndMakeVisible(&yTest);
}



HandleProcessorEditor::~HandleProcessorEditor()
{
}

//==============================================================================
void HandleProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void HandleProcessorEditor::resized()
{
    xTest.setBounds(40, 30, 20, getHeight() - 60);
    yTest.setBounds(80, 30, 20, getHeight() - 60);
}

void HandleProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider->getName().equalsIgnoreCase("xTest"))
        audioProcessor.x = slider->getValue();
    else if (slider->getName().equalsIgnoreCase("yTest")) {
        audioProcessor.y = slider->getValue();
    }

    audioProcessor.updateFx();
}
