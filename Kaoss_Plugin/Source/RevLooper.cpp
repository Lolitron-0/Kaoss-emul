/*
  ==============================================================================

    RevLooper.cpp
    Created: 15 Dec 2021 8:48:43pm
    Author:  ClarVik

  ==============================================================================
*/

#include "RevLooper.h"

void RevLooper::fillDelayBuffer(int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData)
{
    if (delayBufferLength > mWritePosition + bufferLength) //we have enough space in delayBuffer to add next block to it 
    {
        mDelayBuffer.copyFromWithRamp(channel, mWritePosition, bufferData, bufferLength, 0.8f, 0.8f);
    }
    else
    {
        const int bufferRemaining = delayBufferLength - mWritePosition;
        mDelayBuffer.copyFromWithRamp(channel, mWritePosition, bufferData, bufferRemaining, 0.8f, 0.8f);  //add piece of block that fits
        mBufferFilled = true;
        mDelayBuffer.reverse(0,mDelayBuffer.getNumSamples());
    }
}
