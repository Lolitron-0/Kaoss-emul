#include "AudioEffectBase.h"

AudioEffectBase::AudioEffectBase() : ProcessorBase()
{
	mOn = false;
	mFrozen = false;
}

void AudioEffectBase::prepare(const ProcessSpec&)
{
}

void AudioEffectBase::process(const ProcessContextReplacing<float>&)
{
}

void AudioEffectBase::reset()
{
}
