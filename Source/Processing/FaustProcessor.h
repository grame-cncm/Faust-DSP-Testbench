/*
  ==============================================================================

 FaustProcessor.h
    Created:  22 Sep 2024 7:50:32pm
    Author:  Stephane Letz

  ==============================================================================
*/

#pragma once
#include "ProcessorHarness.h"

#include <faust/dsp/dsp.h>
#include <faust/gui/APIUI.h>

#define FAUST_UIMACROS

#define FAUST_ADDBUTTON(l,f)
#define FAUST_ADDCHECKBOX(l,f)
#define FAUST_ADDVERTICALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDHORIZONTALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDNUMENTRY(l,f,i,a,b,s)
#define FAUST_ADDVERTICALBARGRAPH(l,f,a,b)
#define FAUST_ADDHORIZONTALBARGRAPH(l,f,a,b)

#include "mydsp.h"

class FaustExample : public ProcessorHarness
{
    
    private:
        
        std::unique_ptr<mydsp> fDSP;
        APIUI fUI;
        
    public:
        FaustExample ();
        ~FaustExample () = default;
        
        void prepare (const juce::dsp::ProcessSpec& spec) override;
        void process (const juce::dsp::ProcessContextReplacing<float>& context) override;
        void reset() override;
        
        String getProcessorName() override;
        String getControlName (const int index) override;
        double getDefaultControlValue (const int index) override;
  
};
