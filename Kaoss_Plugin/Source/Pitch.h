/*
  ==============================================================================

    Pitch.h
    Created: 15 Dec 2021 8:55:30pm
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

class Pitch : public AudioEffectBase
{
public:

    //inherited
    virtual void updateParams(int x, int y);
    virtual void prepare(const ProcessSpec& s);
    virtual void process(AudioBuffer<float>& buffer);

private:
    soundtouch::SoundTouch* processor;
};