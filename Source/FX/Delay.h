#include <JuceHeader.h>
class Delay {
public:
    void prepare(const juce::dsp::ProcessSpec& spec);
    void process(juce::AudioBuffer<float>& buffer,
                      const int numInputChannels,
                      const int numOutputChannels);
    void setParameters(
        juce::AudioParameterFloat* lengthIn,
        juce::AudioParameterFloat* dryMixIn,
        juce::AudioParameterFloat* wetMixIn,
        juce::AudioParameterFloat* feedbackIn)
    {
        length = lengthIn;
        dryMix = dryMixIn;
        wetMix = wetMixIn;
        feedback = feedbackIn;
    };
    int lastUIWidth, lastUIHeight;

    juce::AudioParameterFloat* length;
    juce::AudioParameterFloat* dryMix;
    juce::AudioParameterFloat* wetMix;
    juce::AudioParameterFloat* feedback;

private:
    // circular buffer variables
    juce::AudioSampleBuffer delayBuffer;
    int delayBufferLength;
    int delayReadPosition;
    int delayWritePosition;
};