#ifndef CONTROLLER_DOT_H
#define CONTROLLER_DOT_H

#include "public.sdk/source/vst/vsteditcontroller.h"

using namespace Steinberg;

class controller : public Vst::EditController
{
	public:

	static FUnknown* createInstance(void*);

	tresult PLUGIN_API initialize(FUnknown* context);
};

#endif