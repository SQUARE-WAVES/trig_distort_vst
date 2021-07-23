#include "processor.h"
#include "ids.h"

#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "public.sdk/source/vst/vstaudioprocessoralgo.h"

#include <math.h>
#define PI 3.141595 //estimd

using namespace Steinberg;
using namespace Steinberg::Vst;

template<typename sample_type> void sin_distort(sample_type** in, sample_type** out, int32 channels,int32 frames, float gain)
{
	for (int32 i = 0; i < channels; i++)
	{
		sample_type* input = in[i];
		sample_type* output = out[i];

		for(int32 frame=0;frame<frames;++frame)
		{
			(output)[frame] = sin((input)[frame] * gain * PI);
		}
	}	
}

template<typename sample_type> void arctan_distort(sample_type** in, sample_type** out, int32 channels,int32 frames, float gain)
{
	for (int32 i = 0; i < channels; i++)
	{
		sample_type* input = in[i];
		sample_type* output = out[i];

		for(int32 frame=0;frame<frames;++frame)
		{
			(output)[frame] = atan((input)[frame] * gain * PI);
		}
	}	
}

processor::processor()
{
	//you have to tell a plugin what's gonna control it
	setControllerClass(controller_id);
}


FUnknown* processor::createInstance (void*)
{
	return (Vst::IAudioProcessor*)new processor();
}

tresult PLUGIN_API processor::initialize(FUnknown* context)
{
	//VST hates RAII so you gotta do this call
	tresult result = AudioEffect::initialize(context);
	
	//if the parent fail, you ought ta bail
	if(result != kResultTrue)
	{
		return kResultFalse;
	}

	//VST3 has this bus concept where you can have 5.1 and stuff like that
	//in your plug-in, this one is just gonna do stereo
	addAudioInput(STR16("AudioInput"), Vst::SpeakerArr::kStereo);
	addAudioOutput(STR16("AudioOutput"), Vst::SpeakerArr::kStereo);

	return kResultTrue;
}

tresult PLUGIN_API processor::setupProcessing (Vst::ProcessSetup& setup)
{
	// this is where you learn your samplerate and stuff like that, not important for this guy
	// but other things will probably want to know a lot of this stuff

	//like many things you have to pass this up the chain
	return AudioEffect::setupProcessing(setup);
}

tresult PLUGIN_API processor::setActive (TBool state)
{
	//this is handy for doing things like allocating resources for a running process
	//so like if you have a delay you can alloc a buffer here and trash it when
	//you go inactive

	//like many things you have to pass this up the chain
	return AudioEffect::setActive(state);
}

tresult PLUGIN_API processor::canProcessSampleSize(int32 sample_size)
{
	if(sample_size == kSample32)
	{
		return kResultTrue;
	}

	// we support double processing
	if(sample_size == kSample64)
	{
		return kResultTrue;
	}

	return kResultFalse;
}

void processor::handle_param_changes(Vst::ProcessData& data)
{
	int32 numParamsChanged = data.inputParameterChanges->getParameterCount();
	
	for(int32 index = 0; index < numParamsChanged; index++)
	{
		Vst::IParamValueQueue* paramQueue = data.inputParameterChanges->getParameterData(index);
		
		if (paramQueue)
		{
			Vst::ParamValue value;
			int32 sampleOffset;
			int32 numPoints = paramQueue->getPointCount();

			switch (paramQueue->getParameterId())
			{
				case params::Volume:
				{
					if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue)
					{
						gain = 4 * value;
					}
				}
				break;

				case params::Shape:
				{
					if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue)
					{
						shape = value > 0.5 ? 1 : 0;
					}
				}
				break;
			}
		}
	}
}

tresult PLUGIN_API processor::process (Vst::ProcessData& data)
{

	//this is the actual process, but this function has to do 3 things before the actual process
	//first it checks param changes
	if(data.inputParameterChanges)
	{
		handle_param_changes(data);
	}

	//you also need to handle "events" like note-on / note-off kinda stuff
	//this thing doesn't do any events but this would be where to handle them

	//finally you need to check that there are inputs in things,
	//and also silence flags (a new VST3 thing)
	if (data.numInputs == 0 || data.numOutputs == 0)
	{
		// nothing to do
		return kResultOk;
	}

	//the way we setup the system the number of channels is the same for 
	//ins and outs
	int32 numChannels = data.inputs[0].numChannels;

	uint32 frame_size = getSampleFramesSizeInBytes (processSetup, data.numSamples);
	void** in = getChannelBuffersPointer (processSetup, data.inputs[0]);
	void** out = getChannelBuffersPointer (processSetup, data.outputs[0]);

	//finally do your actual process
	if (data.numSamples > 0)
	{
		if (data.symbolicSampleSize == kSample32)
		{
			switch(shape)
			{
				case 0:
				{
					sin_distort<Sample32>((Sample32**)in, (Sample32**)out, numChannels,data.numSamples, gain);
				}
				break;

				case 1:
				{
					arctan_distort<Sample32>((Sample32**)in, (Sample32**)out, numChannels,data.numSamples, gain);
				}
			}
		}
		else
		{
			switch(shape)
			{
				case 0:
				{
					sin_distort<Sample64>((Sample64**)in, (Sample64**)out, numChannels,data.numSamples, gain);
				}
				break;

				case 1:
				{
					arctan_distort<Sample64>((Sample64**)in, (Sample64**)out, numChannels,data.numSamples, gain);
				}
			}
		}
		
	}
	return kResultOk;
}