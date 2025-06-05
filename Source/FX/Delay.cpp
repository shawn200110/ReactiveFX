#include "Delay.h"


void Delay::prepare(const juce::dsp::ProcessSpec& spec) {
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    delayBufferLength = (int)2.0 * spec.sampleRate;
    if (delayBufferLength < 1)
        delayBufferLength = 1;

    delayBuffer.setSize(2, delayBufferLength);
    delayBuffer.clear();

    delayReadPosition = (int)(delayWritePosition - (delayLength * spec.sampleRate) + delayBufferLength) % delayBufferLength;
};
void Delay::processBlock(juce::AudioBuffer<float>& buffer, 
                         const int numInputChannels,
                         const int numOutputChannels) {
    const int numSamples = buffer.getNumSamples();

    int dpr, dpw;

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < numInputChannels; ++channel) {
        float* channelData = buffer.getWritePointer(channel);
        float* delayData = delayBuffer.getWritePointer(juce::jmin(channel, delayBuffer.getNumChannels() - 1));

        dpr = delayReadPosition;
        dpw = delayWritePosition;

        for (int i = 0; i < numSamples; ++i) {
            const float in = channelData[i];
            float out = 0.0;

            out = (dryMix * in + wetMix * delayData[dpr]);

            delayData[dpw] = in + (delayData[dpr] * feedback);

            if (++dpr >= delayBufferLength)
                dpr = 0;
            if (++dpw >= delayBufferLength)
                dpw = 0;

            channelData[i] = out;
        }
    }

    delayReadPosition = dpr;
    delayWritePosition = dpw;

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // I've added this to avoid people getting screaming feedback
    // when they first compile the plugin, but obviously you don't need to
    // this code if your algorithm already fills all the output channels.
    for (int i = numInputChannels; i < numOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());
};

void Delay::setParameters(int test) {
};

