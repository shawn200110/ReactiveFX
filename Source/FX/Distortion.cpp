#include "Distortion.h"

void Distortion::prepare(const juce::dsp::ProcessSpec& spec) {
};

void Distortion::process(juce::AudioBuffer<float>& buffer,
                              const int numInputChannels,
                              const int numOutputChannels) {
    juce::ScopedNoDenormals noDenormals;

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = numInputChannels; i < numOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // THESE ARE HARDCODED, NEED TO CONNECT TO PARAMETER
    const float driveAmt = drive->get();
    const float rangeAmt = range->get();
    const float blendAmt = blend->get();
    const float volumeAmt = volume->get();


    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    if (!(bypass->get()))
    {
        for (int channel = 0; channel < numInputChannels; ++channel)
        {
            auto* channelData = buffer.getWritePointer(channel);

            for (int sample = 0; sample < buffer.getNumSamples(); sample++) {

                float cleanData = *channelData;

                *channelData *= driveAmt * rangeAmt;

                *channelData = (((((2.f / juce::float_Pi) * atan(*channelData)) * blendAmt) + (cleanData * (1.f - blendAmt))) / 2.f) * volumeAmt;

                channelData++;
            }
        }
    }
};

