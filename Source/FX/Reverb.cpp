#include "Reverb.h"


void Reverb::prepare(const juce::dsp::ProcessSpec& spec) {
    reverb.prepare(spec);
};
void Reverb::process(juce::AudioBuffer<float>& buffer) {
    
    juce::ScopedNoDenormals noDenormals;

    updateReverbParams();

    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing ctx(block);
    reverb.process(ctx);
};
void Reverb::setParameters(int test) {
};

void Reverb::updateReverbParams()
{
    params.roomSize = size->get() * 0.01f;
    params.damping = damp->get() * 0.01f;
    params.width = width->get() * 0.01f;
    params.wetLevel = mix->get() * 0.01f;
    params.dryLevel = 1.0f - mix->get() * 0.01f;
    params.freezeMode = freeze->get();

    reverb.setParameters(params);
}

