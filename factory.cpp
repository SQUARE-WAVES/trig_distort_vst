#include "public.sdk/source/main/pluginfactory.h"

#include "controller.h"	
#include "processor.h"	
#include "ids.h"	

#define PLUGIN_CATEGORY	"Fx"
#define PLUGIN_NAME "trig_distort"
#define CONTROLLER_NAME "controller"
#define PLUGIN_VERSION "1.0.0"

BEGIN_FACTORY_DEF("example_plugins", "www.example.com",	"nobody@example.com")

	//this is a big ol macro call
	DEF_CLASS2
	(
		INLINE_UID_FROM_FUID(processor_id),
		PClassInfo::kManyInstances,	// this says you can make more than one instant  
		kVstAudioEffectClass,	// this says it's a processor (I think it also means it's not an instrument)
		PLUGIN_NAME,
		Vst::kDistributable,	//this means you could put the controller on a different computer (not sure about this stuff yet)
		PLUGIN_CATEGORY,		
		PLUGIN_VERSION,	
		kVstVersionString, //this is from the SDK, it's the version of VST you are using
		processor::createInstance //the function to intialize the thing
	)	

	DEF_CLASS2 
	(
		INLINE_UID_FROM_FUID(controller_id),
		PClassInfo::kManyInstances,
		kVstComponentControllerClass, //this says it's a controller
		CONTROLLER_NAME,
		0,						// apparently controllers don't care about these params
		"",						
		PLUGIN_VERSION,	
		kVstVersionString,		// vst version
		controller::createInstance
	)

END_FACTORY
