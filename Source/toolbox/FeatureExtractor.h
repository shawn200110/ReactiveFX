#include <JuceHeader.h>
class FeatureExtractor
{
public:

    static constexpr int fftOrder = 10;

    FeatureExtractor() : fft(fftOrder) { }

    void update(const juce::AudioBuffer<float>& buffer)
    {
        computeRMSLevel(buffer);
        computePeakLevel(buffer);
        // add more features later
    }

    float getRMSLevel() const { return rmsLevel; }
    float getPeakLevel() const { return peakLevel; }
    float getSpectralCentroid() const { return spectralCentroid; }

private:
    float rmsLevel = 0.0f;
    float peakLevel = 0.0f;
    float spectralCentroid = 0.0f;

    int fftSize;
    juce::AudioBuffer<float> fftBuffer;
    int fftBufferWritePos;
    juce::dsp::FFT fft;

    

    void computeRMSLevel(const juce::AudioBuffer<float>& buffer);
    void computePeakLevel(const juce::AudioBuffer<float>& buffer);
    void computeSpectralCentroid(float sampleRate);

    void updateFFTBuffer(const juce::AudioBuffer<float>& inputBuffer);
    void prepareFFT(int sampleRate)
    {
        fftSize = 1024; 
        fftBuffer.setSize(1, fftSize);
        fftBuffer.clear();
        fftBufferWritePos = 0;
    }
};