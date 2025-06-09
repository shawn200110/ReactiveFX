#include "FeatureExtractor.h"

void FeatureExtractor::computeRMSLevel(const juce::AudioBuffer<float>& buffer)
{
    double sumSquares = 0.0;
    int numSamples = buffer.getNumSamples();
    int numChannels = buffer.getNumChannels();

    for (int channel = 0; channel < numChannels; ++channel)
    {
        const float* channelData = buffer.getReadPointer(channel);

        for (int i = 0; i < numSamples; ++i)
        {
            sumSquares += channelData[i] * channelData[i];
        }
    }

    double meanSquare = sumSquares / (numSamples * numChannels);
    rmsLevel = static_cast<float>(std::sqrt(meanSquare));
}

void FeatureExtractor::computePeakLevel(const juce::AudioBuffer<float>& buffer)
{
    int numSamples = buffer.getNumSamples();
    int numChannels = buffer.getNumChannels();

    for (int channel = 0; channel < numChannels; ++channel)
    {
        const float* channelData = buffer.getReadPointer(channel);

        for (int i = 0; i < numSamples; ++i)
        {
            float absSample = std::abs(channelData[i]);
            if (absSample > peakLevel)
                peakLevel = absSample;
        }
    }
}


void FeatureExtractor::computeSpectralCentroid(float sampleRate)
{
    juce::HeapBlock<juce::dsp::Complex<float>> fftDataBlock(fftSize * 2, true);
    auto* fftData = reinterpret_cast<float*>(fftDataBlock.getData());

    // Copy fftBuffer into fftData, zero pad
    const float* bufferData = fftBuffer.getReadPointer(0);

    int fftReadPos = fftBufferWritePos; // circular read
    for (int i = 0; i < fftSize; ++i)
    {
        fftData[2 * i] = bufferData[fftReadPos];
        fftData[2 * i + 1] = 0.0f;

        if (++fftReadPos >= fftSize)
            fftReadPos = 0;
    }

    // Perform FFT
    fft.performRealOnlyForwardTransform(fftData);
    //fft.perform(fftData, fftData, false);

    double weightedSum = 0.0;
    double totalSum = 0.0;

    // Bin 0 (DC)
    float magnitude = std::abs(fftData[0]);
    float frequency = 0.0f; // DC
    weightedSum += frequency * magnitude;
    totalSum += magnitude;

    // Bins 1 to N/2 - 1
    for (int bin = 1; bin < fftSize / 2; ++bin)
    {
        float real = fftData[2 * bin];
        float imag = fftData[2 * bin + 1];

        float magnitude = std::sqrt(real * real + imag * imag);

        float frequency = (sampleRate * bin) / fftSize;

        weightedSum += frequency * magnitude;
        totalSum += magnitude;
    }

    // Bin N/2 (Nyquist)
    magnitude = std::abs(fftData[1]);
    frequency = (sampleRate / 2.0f);
    weightedSum += frequency * magnitude;
    totalSum += magnitude;

    // Final centroid
    if (totalSum > 0.0)
        spectralCentroid = static_cast<float>(weightedSum / totalSum);
    else
        spectralCentroid = 0.0f;
}

void FeatureExtractor::updateFFTBuffer(const juce::AudioBuffer<float>& inputBuffer)
{
    const int numSamples = inputBuffer.getNumSamples();
    const float* channelData = inputBuffer.getReadPointer(0); // Use mono sum later if you want

    for (int i = 0; i < numSamples; ++i)
    {
        fftBuffer.setSample(0, fftBufferWritePos, channelData[i]);

        if (++fftBufferWritePos >= fftSize)
            fftBufferWritePos = 0;
    }
}
