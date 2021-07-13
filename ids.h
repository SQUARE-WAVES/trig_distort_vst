#ifndef CLASS_IDS_DOT_H
#define CLASS_IDS_DOT_H

using namespace Steinberg;

enum params : Vst::ParamID
{
	Volume = 102,
	Shape = 1000
};

static const FUID processor_id (0x2D941C31,0x4B4D436F,0xBB66C804,0xAB359750);
static const FUID controller_id (0x78C8B27A,0xFD1849A1,0xA185AE5E,0x2392E753);

#endif