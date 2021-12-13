/*
  ==============================================================================

    AudioEffectBase.cpp
    Created: 13 Dec 2021 1:46:11pm
    Author:  ClarVik

  ==============================================================================
*/

#include "AudioEffectBase.h"

AudioEffectBase::AudioEffectBase()
{
}

void AudioEffectBase::updateParams(int x, int y)
{
}

//get
bool AudioEffectBase::isOn()
{
	return this->mOn;
}

bool AudioEffectBase::isFrozen()
{
	return this->mFrozen;
}

//set
void AudioEffectBase::setOn(bool on)
{
	this->mOn = on;
}

void AudioEffectBase::setFrozen(bool frozen)
{
	this->mFrozen = frozen;
}


void AudioEffectBase::prepare(const ProcessSpec& s)
{
	this->mSampleRate = s.sampleRate;
	this->mNumInputChannels = s.numChannels;
}

void AudioEffectBase::process(AudioBuffer<float>& buffer)
{
}

void AudioEffectBase::reset()
{
}
