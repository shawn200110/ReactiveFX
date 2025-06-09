/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ReactiveFXAudioProcessor::ReactiveFXAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
                     #endif
                     apvts(*this, nullptr, "Parameters", createParameterLayout())
                       
#endif
{
    reverbSize = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("ReverbSize"));
    reverbDamping = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("ReverbDamping"));
    reverbWidth = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("ReverbWidth"));
    reverbMix = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("ReverbMix"));
    reverbFreeze = dynamic_cast<juce::AudioParameterBool*> (apvts.getParameter("ReverbFreeze"));

    distDrive = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("DistDrive"));
    distRange = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("DistRange"));
    distBlend = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("DistBlend"));
    distVolume = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("DistVolume"));

    delayLength = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("DelayLength"));
    delayDryMix = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("DelayDryMix"));
    delayWetMix = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("DelayWetMix"));
    delayFeedback = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("DelayFeedback"));
}

ReactiveFXAudioProcessor::~ReactiveFXAudioProcessor()
{
}

//==============================================================================
const juce::String ReactiveFXAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ReactiveFXAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ReactiveFXAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ReactiveFXAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ReactiveFXAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ReactiveFXAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ReactiveFXAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ReactiveFXAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ReactiveFXAudioProcessor::getProgramName (int index)
{
    return {};
}

void ReactiveFXAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ReactiveFXAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void ReactiveFXAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ReactiveFXAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ReactiveFXAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool ReactiveFXAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ReactiveFXAudioProcessor::createEditor()
{
    return new ReactiveFXAudioProcessorEditor (*this);
}

//==============================================================================
void ReactiveFXAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ReactiveFXAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ReactiveFXAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout ReactiveFXAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Reverb parameters
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ReverbSize", "Size", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ReverbDamping", "Damping", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ReverbWidth", "Width", 0.0f, 1.0f, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ReverbMix", "Mix", 0.0f, 1.0f, 0.33f));
    params.push_back(std::make_unique<juce::AudioParameterBool>("ReverbFreeze", "Freeze", false));

    // Distortion parameters
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DistDrive", "Drive", 0.0f, 10.0f, 5.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DistRange", "Range", 0.0f, 10.0f, 5.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DistBlend", "Blend", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DistVolume", "Volume", 0.0f, 1.0f, 0.8f));

    // Delay parameters
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DelayLength", "Delay Length", 1.0f, 2000.0f, 500.0f)); // in ms
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DelayDryMix", "Dry Mix", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DelayWetMix", "Wet Mix", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DelayFeedback", "Feedback", 0.0f, 0.95f, 0.5f));

    return { params.begin(), params.end() };
}