/*
  ==============================================================================

    AudioEffectBase.h
    Created: 13 Dec 2021 1:46:11pm
    Author:  ClarVik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "vector"
#include "algorithm"
using namespace juce;
using namespace juce::dsp;
using namespace std;

class AudioEffectBase
{
public:

	AudioEffectBase();

	virtual void updateParams(int x, int y);

	//get
	bool isOn();
	bool isFrozen();

	//set
	void setOn(bool on);
	void setFrozen(bool frozen);

	//inherited
	virtual void prepare(const ProcessSpec& s);
	virtual void process(AudioBuffer<float>& buffer);
	virtual void reset();
protected:

	bool mOn{false};
	bool mFrozen{false};
	int mSampleRate{44100};
	int mNumInputChannels{1};
};
