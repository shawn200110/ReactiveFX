/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "FX/Controller.h"
#include "toolbox/FeatureExtractor.h"



//==============================================================================
/**
*/
class ReactiveFXAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    ReactiveFXAudioProcessor();
    ~ReactiveFXAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    juce::AudioProcessorValueTreeState apvts;
    juce::AudioParameterFloat* reverbSize = nullptr;
    juce::AudioParameterFloat* reverbDamping = nullptr;
    juce::AudioParameterFloat* reverbWidth = nullptr;
    juce::AudioParameterFloat* reverbMix = nullptr;
    juce::AudioParameterBool* reverbFreeze = nullptr;
    
    juce::AudioParameterFloat* distDrive = nullptr;
    juce::AudioParameterFloat* distRange = nullptr;
    juce::AudioParameterFloat* distBlend = nullptr;
    juce::AudioParameterFloat* distVolume = nullptr;

    juce::AudioParameterFloat* delayLength = nullptr;
    juce::AudioParameterFloat* delayDryMix = nullptr;
    juce::AudioParameterFloat* delayWetMix = nullptr;
    juce::AudioParameterFloat* delayFeedback = nullptr;
    
    

    Delay delay;
    Reverb reverb;
    Distortion distortion;

    FeatureExtractor featureExtractor;

    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ReactiveFXAudioProcessor);
};
