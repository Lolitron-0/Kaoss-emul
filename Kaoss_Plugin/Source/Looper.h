/*
  ==============================================================================

    Looper.h
    Created: 13 Dec 2021 1:46:28pm
    Author:  ClarVik

  ==============================================================================
*/

#pragma once
#include "AudioEffectBase.h"
class Looper :
	public AudioEffectBase
{

public:

	Looper();

	virtual void updateParams(int x, int y) override;

	void fillDelayBuffer(int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData);

	void getFromDelayBuffer(juce::AudioBuffer<float>& buffer, int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData);

	//inherited
	void prepare(const ProcessSpec& s) override;
	void process(AudioBuffer<float>& buffer);
	void reset() override;

private:
	AudioBuffer <float> mDelayBuffer;
	int mWritePosition{ 0 };
	int mReadPosition{ 0 };
	bool mBufferFilled{ false };
};
