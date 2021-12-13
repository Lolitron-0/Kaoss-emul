/*
  ==============================================================================

    Looper.cpp
    Created: 13 Dec 2021 1:46:28pm
    Author:  ClarVik

  ==============================================================================
*/

#include "Looper.h"

Looper::Looper() : AudioEffectBase()
{
}

void Looper::updateParams(int x, int y)
{
    if (y == 0)
    {
        mWritePosition = 0;
        mReadPosition = 0;
        mBufferFilled = false;
    }
}

void Looper::fillDelayBuffer(int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData)
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
    }
}

void Looper::getFromDelayBuffer(juce::AudioBuffer<float>& buffer, int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData)
{
    if (delayBufferLength > mReadPosition + bufferLength) 
    {
        buffer.copyFrom(channel, 0, delayBufferData + mReadPosition, bufferLength); //insert segment in main buffer
    }
    else
    {
        const int bufferRemaining = delayBufferLength - mReadPosition;
        buffer.copyFrom(channel, 0, delayBufferData + mReadPosition, bufferRemaining);   //insert a piece
        buffer.copyFrom(channel, bufferRemaining, delayBufferData, bufferLength - bufferRemaining);  //wrap and add remaining from the segment start
    }
}

void Looper::prepare(const ProcessSpec& s)
{
    AudioEffectBase::prepare(s);
    const int delayBufferSize = (s.sampleRate + s.maximumBlockSize) * 0.2;
    mDelayBuffer.setSize(s.numChannels, delayBufferSize);
}

void Looper::process(AudioBuffer<float>& buffer)
{
    const int bufferLength = buffer.getNumSamples();
    const int delayBufferLength = mDelayBuffer.getNumSamples();


    for (int channel = 0; channel < mNumInputChannels; channel++)
    {
        const float* bufferData = buffer.getReadPointer(channel);
        const float* delayBufferData = mDelayBuffer.getReadPointer(channel);

        if (!mBufferFilled)
            fillDelayBuffer(channel, bufferLength, delayBufferLength, bufferData, delayBufferData);
        else
            getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData);
    }
    if(!mBufferFilled)
        mWritePosition += bufferLength;
    else {
        mReadPosition += bufferLength;
        mReadPosition %= delayBufferLength;
    }
}

void Looper::reset()
{
    mWritePosition = 0;
    mReadPosition = 0;
}