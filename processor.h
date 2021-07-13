#ifndef PROCESSOR_DOT_H
#define PROCESSOR_DOT_H

#include "public.sdk/source/vst/vstaudioeffect.h"

using namespace Steinberg;

class processor : public Vst::AudioEffect
{
	public:
	processor ();

	//these are all overrides of AudioEffect methods
	tresult PLUGIN_API initialize(FUnknown* context);

	tresult PLUGIN_API setBusArrangements (Vst::SpeakerArrangement* inputs, int32 numIns,Vst::SpeakerArrangement* outputs, int32 numOuts);

	tresult PLUGIN_API setupProcessing (Vst::ProcessSetup& setup);
	tresult PLUGIN_API setActive (TBool state);
	tresult PLUGIN_API process (Vst::ProcessData& data);

	tresult PLUGIN_API canProcessSampleSize(int32 symbolicSampleSize);

	static FUnknown* createInstance (void*);

	protected:
	Vst::ParamValue gain = 0;
	int16 shape = 0;

	//this isn't from the VST class
	void handle_param_changes(Vst::ProcessData& data);
};

#endif