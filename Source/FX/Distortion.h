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
        juce::AudioParameterFloat* volumeIn,
        juce::AudioParameterBool* bypassIn)
    {
        drive = driveIn;
        range = rangeIn;
        blend = blendIn;
        volume = volumeIn;
        bypass = bypassIn;
    };

private:
    juce::AudioParameterFloat* drive;
    juce::AudioParameterFloat* range;
    juce::AudioParameterFloat* blend;
    juce::AudioParameterFloat* volume;
    juce::AudioParameterBool* bypass;
};