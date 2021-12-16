/*
  ==============================================================================

    SoundTouchEffectBase.cpp
    Created: 16 Dec 2021 11:19:15am
    Author:  ClarVik

  ==============================================================================
*/

#include "SoundTouchEffectBase.h"

void SoundTouchEffectBase::prepare(const ProcessSpec& s)
{
    AudioEffectBase::prepare(s);
    mpProcessor1 = new SoundTouch();
    mpProcessor1->setChannels(1);
    mpProcessor1->setSampleRate(s.sampleRate);
    mpProcessor2 = new SoundTouch();
    mpProcessor2->setChannels(1);
    mpProcessor2->setSampleRate(s.sampleRate);
}

void SoundTouchEffectBase::process(AudioBuffer<float>& buffer)
{
    float* bufferData = buffer.getWritePointer(0);
    mpProcessor1->putSamples(bufferData, buffer.getNumSamples());
    mpProcessor1->receiveSamples(bufferData, buffer.getNumSamples());

    bufferData = buffer.getWritePointer(1);
    mpProcessor2->putSamples(bufferData, buffer.getNumSamples());
    mpProcessor2->receiveSamples(bufferData, buffer.getNumSamples());

}
