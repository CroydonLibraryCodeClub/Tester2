#include "Tester.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

Tester::Tester(const InstanceInfo& info)
: Plugin(info, MakeConfig(kNumParams, kNumPresets))
{
  GetParam(kGain)->InitDouble("Gain", 0., 0., 100.0, 0.01, "%");

#if IPLUG_EDITOR // http://bit.ly/2S64BDd
  mMakeGraphicsFunc = [&]() {
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, GetScaleForScreen(PLUG_WIDTH, PLUG_HEIGHT));
  };
  
  mLayoutFunc = [&](IGraphics* pGraphics) {
    pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
    pGraphics->AttachBackground(BOTH11);
    pGraphics->AttachBackground(DIAL);
    pGraphics->LoadFont("Roboto-Regular", ROBOTO_FN);
    const IRECT b = pGraphics->GetBounds();
   
    pGraphics->AttachControl(newITextControl(b.GetMidVPadded(450).GetVShifted(165).GetHShifted(0), "R",
    IText(40,COLOR_WHITE)));
      
    pGraphics->AttachControl(new IVKnobControl(b.GetCentredInside(170).GetVShifted(-15), kGain));
  
  
        
 
  };
#endif
}

#if IPLUG_DSP
void Tester::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  const double gain = GetParam(kGain)->Value() / 100.;
  const int nChans = NOutChansConnected();
  
  for (int s = 0; s < nFrames; s++) {
    for (int c = 0; c < nChans; c++) {
      outputs[c][s] = inputs[c][s] * gain;
    }
  }
}
#endif
