/*
  ==============================================================================

    FaustProcessor.cpp
    Created: 22 Sep 2024 7:50:32pm
    Author:  Stephane Letz

  ==============================================================================
*/

#include "FaustProcessor.h"

FaustExample::FaustExample()
: ProcessorHarness (FAUST_ACTIVES)
{
    fDSP = std::make_unique<mydsp>();
    fDSP->buildUserInterface(&fUI);
}
void FaustExample::prepare (const juce::dsp::ProcessSpec& spec)
{
    fDSP->init(spec.sampleRate);
}
void FaustExample::process (const juce::dsp::ProcessContextReplacing<float>& context)
{
    // Update controllers
    for (int ctrl = 0; ctrl < fUI.getParamsCount(); ctrl++) {
        fUI.setParamRatio(ctrl, getControlValue(ctrl));
    }
    
    FAUSTFLOAT* inputs[fDSP->getNumInputs()];
    for (int chan = 0; chan < fDSP->getNumInputs(); chan++) {
        inputs[chan] = (FAUSTFLOAT*)context.getInputBlock().getChannelPointer(chan);
    }
    
    FAUSTFLOAT* outputs[fDSP->getNumOutputs()];
    for (int chan = 0; chan < fDSP->getNumOutputs(); chan++) {
        outputs[chan] = context.getOutputBlock().getChannelPointer(chan);
    }
    
    // Compute samples
    fDSP->compute(context.getOutputBlock().getNumSamples(), inputs, outputs);
}
void FaustExample::reset()
{
    fDSP->init(fDSP->getSampleRate());
}
String FaustExample::getProcessorName()
{
    return String ("Faust");
}
String FaustExample::getControlName (const int index)
{
    return fUI.getParamAddress(index);
}
double FaustExample::getDefaultControlValue (const int index)
{
    return fUI.getParamInit(index);
}
