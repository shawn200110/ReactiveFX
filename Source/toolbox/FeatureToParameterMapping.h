#pragma once
#include <JuceHeader.h>

struct FeatureToParameterMapping
{
    enum class Feature { RMS, Peak, SpectralCentroid };
    enum class Parameter { ReverbSize, DelayFeedback, DistDrive };

    Feature feature;
    Parameter parameter;

    float scaling = 1.0f;
    float offset = 0.0f;
    float minValue = 0.0f;
    float maxValue = 1.0f;

    float computeMappedValue(float featureValue) const
    {
        return juce::jlimit(minValue, maxValue, featureValue * scaling + offset);
    }
};

