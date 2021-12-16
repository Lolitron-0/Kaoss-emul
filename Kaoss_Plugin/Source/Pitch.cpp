/*
  ==============================================================================

    Pitch.cpp
    Created: 15 Dec 2021 8:55:31pm
    Author:  ClarVik

  ==============================================================================
*/

#include "Pitch.h"

void Pitch::updateParams(int x, int y)
{
    if (y == 0)
        processor->setPitchSemiTones( 0);
    else
        processor->setPitchSemiTones((float)(-12+(x/100.)*24));
}

void Pitch::prepare(const ProcessSpec& s)
{
    AudioEffectBase::prepare(s);
    processor = new SoundTouch();
    processor->setChannels(1);
    processor->setSampleRate(s.sampleRate);
}

void Pitch::process(AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++) {
        float* bufferData = buffer.getWritePointer(channel);
        processor->putSamples(bufferData, buffer.getNumSamples());
        processor->receiveSamples(bufferData, buffer.getNumSamples());
        buffer.copyFrom(channel, 0, bufferData, buffer.getNumSamples());
    }
}
