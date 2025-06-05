#include <JuceHeader.h>
class Distortion {
public:
    void prepare(const juce::dsp::ProcessSpec& spec);
    void processBlock(juce::AudioBuffer<float>& buffer,
                      const int numInputChannels,
                      const int numOutputChannels);
    void setParameters(int test);

private:

    juce::AudioProcessorValueTreeState state;

};