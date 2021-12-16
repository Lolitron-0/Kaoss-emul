/*
  ==============================================================================

    Pitch.h
    Created: 15 Dec 2021 8:55:30pm
    Author:  ClarVik

  ==============================================================================
*/

#pragma once
#include "SoundTouchEffectBase.h"

using namespace std;
using namespace juce;
using namespace juce::dsp;

class Pitch : public SoundTouchEffectBase
{
public:

    //inherited
    virtual void updateParams(int x, int y) override;

};