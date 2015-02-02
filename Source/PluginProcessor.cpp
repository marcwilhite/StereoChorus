/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
StereoChorusAudioProcessor::StereoChorusAudioProcessor()
{
    setParameterNotifyingHost(delayParam, 0.5);
    setParameterNotifyingHost(feedbackParam, 0.5);
    setParameterNotifyingHost(modParam, 0.5);
    setParameterNotifyingHost(mixParam, 0.5);
    
}

StereoChorusAudioProcessor::~StereoChorusAudioProcessor()
{
}

//==============================================================================
const String StereoChorusAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int StereoChorusAudioProcessor::getNumParameters()
{
    return totalNumParams;
}

float StereoChorusAudioProcessor::getParameter (int index)
{
    switch (index) {
        case delayParam:                return parameters[0];
        case feedbackParam:             return parameters[1];
        case modParam:                  return parameters[2];
        case mixParam:                  return parameters[3];
        default:
            return 0.0f;
    }
    }

void StereoChorusAudioProcessor::setParameter (int index, float newValue)
{
    switch (index) {
        case delayParam:        parameters[0] = newValue; break;
        case feedbackParam:     parameters[1] = newValue; break;
        case modParam:          parameters[2] = newValue; break;
        case mixParam:          parameters[3] = newValue; break;
            
        default:
            break;
    }
}

const String StereoChorusAudioProcessor::getParameterName (int index)
{
    switch (index) {
        case delayParam:            return "Delay";
        case feedbackParam:         return "Feedback";
        case modParam:              return "Modulation";
        case mixParam:              return "MIx";
            
        default:
            return String::empty;
    }
    
    
}

const String StereoChorusAudioProcessor::getParameterText (int index)
{
    return String::empty;
}

const String StereoChorusAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String StereoChorusAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool StereoChorusAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool StereoChorusAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool StereoChorusAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool StereoChorusAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool StereoChorusAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double StereoChorusAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int StereoChorusAudioProcessor::getNumPrograms()
{
    return 0;
}

int StereoChorusAudioProcessor::getCurrentProgram()
{
    return 0;
}

void StereoChorusAudioProcessor::setCurrentProgram (int index)
{
}

const String StereoChorusAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void StereoChorusAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void StereoChorusAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    

    leftBuffer.setBufferSize((int)4410);
    rightBuffer.setBufferSize((int)4410);
    leftDelayTime = getParameter(((delayParam*0.004)+0.005) * sampleRate);
    rightDelayTime = getParameter(((delayParam*0.003)+0.005) * sampleRate);
    leftOsc.setFrequency(0.5);
    leftOsc.setSampleRate(sampleRate);
    rightOsc.setFrequency(0.6);
    rightOsc.setSampleRate(sampleRate);
    
}

void StereoChorusAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void StereoChorusAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    
    if (getNumInputChannels() == 1) buffer.copyFrom(1, 0, buffer, 0, 0, buffer.getNumSamples());
    
    //float* channelData = buffer.getSampleData (0);
    for (int i = 0; i < buffer.getNumSamples(); i++) {
        
        
        float leftMod = (leftOsc.nextSample()+1.01) * getParameter(modParam) * 100;
        float rightMod = (leftOsc.nextSample()+1.01) * getParameter(modParam) * 100;
        
        leftDelayTime = (getParameter(delayParam) * 200) + leftMod + .002;
        rightDelayTime = (getParameter(delayParam) * 220) + rightMod + .0015;
        
        float l_xn = buffer.getReadPointer(0)[i];
        float r_xn = buffer.getReadPointer(1)[i];
        
        float l_combined;
        float r_combined;
        float l_yn;
        float r_yn;
        

        l_yn = leftBuffer.getSample(leftDelayTime);
        r_yn = rightBuffer.getSample(rightDelayTime);
            
        l_combined = l_xn + r_yn * getParameter(feedbackParam);
        r_combined = r_xn + l_yn * getParameter(feedbackParam);
      
        
        leftBuffer.addSample(l_combined);
        rightBuffer.addSample(r_combined);
        
        buffer.getWritePointer(0)[i] = (l_xn * (1-getParameter(mixParam)) + l_yn * getParameter(mixParam));
        buffer.getWritePointer(1)[i] = (r_xn * (1-getParameter(mixParam)) + r_yn * getParameter(mixParam));
        
    }
}

//==============================================================================
bool StereoChorusAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* StereoChorusAudioProcessor::createEditor()
{
    return new StereoChorusAudioProcessorEditor (this);
}

//==============================================================================
void StereoChorusAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void StereoChorusAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StereoChorusAudioProcessor();
}
