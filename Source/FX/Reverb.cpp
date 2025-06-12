#include "Reverb.h"


void Reverb::prepare(const juce::dsp::ProcessSpec& spec) {
    reverb.prepare(spec);
};
void Reverb::process(juce::AudioBuffer<float>& buffer) {

    if (!(bypass->get()))
    {
        juce::ScopedNoDenormals noDenormals;

        updateReverbParams();

        juce::dsp::AudioBlock<float> block(buffer);
        juce::dsp::ProcessContextReplacing ctx(block);
        reverb.process(ctx);
    }
};


void Reverb::updateReverbParams()
{
    params.roomSize = size->get();
    params.damping = damp->get();
    params.width = width->get();
    params.wetLevel = mix->get();
    params.freezeMode = freeze->get();
    reverb.setParameters(params);
}

