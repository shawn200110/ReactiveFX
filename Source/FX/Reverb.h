#include <JuceHeader.h>
class Reverb {
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void processBlock(juce::AudioBuffer<float>& buffer);
    void setParameters(int test);
private:
    juce::AudioProcessorValueTreeState apvts;

    juce::AudioParameterFloat* size{ nullptr };
    juce::AudioParameterFloat* damp{ nullptr };
    juce::AudioParameterFloat* width{ nullptr };
    juce::AudioParameterFloat* mix{ nullptr };
    juce::AudioParameterBool* freeze{ nullptr };

    void updateReverbParams();

    juce::dsp::Reverb::Parameters params;
    juce::dsp::Reverb reverb;

    juce::UndoManager undoManager;
    // Internal state and processing variables
};