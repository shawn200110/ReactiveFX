#include "Delay.h"
#include "Distortion.h"
#include "Reverb.h"

class Controller {
public:
    void analyzeInput(const juce::AudioBuffer<float>& buffer);
    void updateEffectParameters(Delay& delay,
        Reverb& reverb,
        Distortion& distortion);
private:
};