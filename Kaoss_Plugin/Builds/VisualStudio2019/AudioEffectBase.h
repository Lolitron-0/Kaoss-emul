#pragma once
#include <JuceHeader.h>
#include "vector"
#include "algorithm"
using namespace juce;
using namespace juce::dsp;
using namespace std;

class AudioEffectBase : public ProcessorBase
{
public:

	AudioEffectBase();

	virtual void updateParams(int x, int y);

	// Унаследовано через ProcessorBase
	virtual void prepare(const ProcessSpec&) override;
	virtual void process(const ProcessContextReplacing<float>&) override;
	virtual void reset() override;
private: 

	bool mOn;
	bool mFrozen;
};

