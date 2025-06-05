#include <JuceHeader.h>
class FormantShift {
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void processBlock(juce::AudioBuffer<float>& buffer);
    void setParameters(int test);
private:
    // Internal state and processing variables
};