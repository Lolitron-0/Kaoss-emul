/*
  ==============================================================================

    SoundTouchEffectBase.h
    Created: 16 Dec 2021 11:19:15am
    Author:  ClarVik

  ==============================================================================
*/

#pragma once
#include "AudioEffectBase.h"
#include "soundtouch/SoundTouch.h"

using namespace std;
using namespace juce;
using namespace juce::dsp;
using namespace soundtouch;

class SoundTouchEffectBase : public AudioEffectBase
{
public:

    //inherited
    virtual void prepare(const ProcessSpec& s);
    virtual void process(AudioBuffer<float>& buffer);

protected:
    soundtouch::SoundTouch* mpProcessor1;
    soundtouch::SoundTouch* mpProcessor2;
};