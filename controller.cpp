#include "controller.h"
#include "ids.h"

using namespace Steinberg;
using Steinberg::Vst::ParameterInfo;

tresult PLUGIN_API controller::initialize(FUnknown* context)
{
	tresult result = EditController::initialize(context);
	
	if (result == kResultTrue)
	{
		//---Create Parameters------------
		parameters.addParameter(STR16("gain"), NULL, 0, .25, ParameterInfo::kCanAutomate, params::Volume, 0, STR16("gain"));
		parameters.addParameter(STR16("shape"), STR16("sin/tri"),1,1.,ParameterInfo::kCanAutomate, params::Shape, 0, STR16("shape"));
	}

	return result;
}

FUnknown* controller::createInstance(void*)
{
	return (Vst::IEditController*)new controller();
}