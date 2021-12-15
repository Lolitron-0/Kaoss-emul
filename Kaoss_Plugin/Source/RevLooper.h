/*
  ==============================================================================

    RevLooper.h
    Created: 15 Dec 2021 8:48:43pm
    Author:  ClarVik

  ==============================================================================
*/

#pragma once
#include "Looper.h"


class RevLooper : public Looper
{
public:
    void fillDelayBuffer(int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData) override;

};