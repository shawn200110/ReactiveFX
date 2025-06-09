#include <JuceHeader.h>
class Distortion {
public:
    void prepare(const juce::dsp::ProcessSpec& spec);
    void process(juce::AudioBuffer<float>& buffer,
                      const int numInputChannels,
                      const int numOutputChannels);
    void setParameters(
        juce::AudioParameterFloat* driveIn,
        juce::AudioParameterFloat* rangeIn,
        juce::AudioParameterFloat* blendIn,
        juce::AudioParameterFloat* volumeIn)
    {
        drive = driveIn;
        range = rangeIn;
        blend = blendIn;
        volume = volumeIn;
    };

private:
    juce::AudioParameterFloat* drive;
    juce::AudioParameterFloat* range;
    juce::AudioParameterFloat* blend;
    juce::AudioParameterFloat* volume;
};