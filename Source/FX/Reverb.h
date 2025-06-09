#include <JuceHeader.h>
class Reverb {
public:
    void prepare(const juce::dsp::ProcessSpec& spec);
    void process(juce::AudioBuffer<float>& buffer);
    void setParameters(
        juce::AudioParameterFloat* sizeIn,
        juce::AudioParameterFloat* dampingIn,
        juce::AudioParameterFloat* widthIn,
        juce::AudioParameterFloat* mixIn,
        juce::AudioParameterBool* freezeIn)
    {
        size = sizeIn;
        damp = dampingIn;
        width = widthIn;
        mix = mixIn;
        freeze = freezeIn;
    };
private:

    juce::AudioParameterFloat* size{ nullptr };
    juce::AudioParameterFloat* damp{ nullptr };
    juce::AudioParameterFloat* width{ nullptr };
    juce::AudioParameterFloat* mix{ nullptr };
    juce::AudioParameterBool* freeze{ nullptr };

    void updateReverbParams();

    juce::dsp::Reverb::Parameters params;
    juce::dsp::Reverb reverb;

    juce::UndoManager undoManager;
};