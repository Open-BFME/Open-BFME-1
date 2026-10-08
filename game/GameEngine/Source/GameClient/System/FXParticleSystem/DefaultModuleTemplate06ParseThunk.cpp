// cl: /O2 /GR- /EHsc- /DNDEBUG /DWIN32 /D_WINDOWS /MD /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// Open-BFME5: DefaultModuleTemplate<7>::parse -> INI::initFromINI(this, FieldParse).

// The ZH Common/INI.h declares initFromINI with the retail signature
// (void *, const FieldParse *) and the INI::parse* statics the table below
// names; BFME's Common/INI/INI.h declares none of those parsers.
#include "PreRTS.h"
#include "Common/INI.h"

// Retail .rdata 0x01114768, 208 bytes: WindMotion (INI::parseIndexList over
// the exported FXParticleSystem::WindMotionNames, 0xC) and eleven
// INI::parseReal wind/turbulence fields, plus the zero terminator; tokens,
// parsers, userData and offsets read from the image.
namespace FXParticleSystem
{
extern const char *const WindMotionNames[];
}

extern "C" const FieldParse DefaultModuleTemplate06FieldParse[] =
{
	{ "WindMotion",	INI::parseIndexList,	FXParticleSystem::WindMotionNames,	0xC },
	{ "WindStrength",	INI::parseReal,	0,	0x10 },
	{ "WindFullStrengthDist",	INI::parseReal,	0,	0x14 },
	{ "WindZeroStrengthDist",	INI::parseReal,	0,	0x18 },
	{ "WindAngleChangeMin",	INI::parseReal,	0,	0x24 },
	{ "WindAngleChangeMax",	INI::parseReal,	0,	0x28 },
	{ "WindPingPongStartAngleMin",	INI::parseReal,	0,	0x30 },
	{ "WindPingPongStartAngleMax",	INI::parseReal,	0,	0x34 },
	{ "WindPingPongEndAngleMin",	INI::parseReal,	0,	0x3C },
	{ "WindPingPongEndAngleMax",	INI::parseReal,	0,	0x40 },
	{ "TurbulenceAmplitude",	INI::parseReal,	0,	0x48 },
	{ "TurbulenceFrequency",	INI::parseReal,	0,	0x4C },
	{ 0,	0,	0,	0 }
};

namespace FXParticleSystem
{

template <int Category>
class DefaultModuleTemplate
{
public:
	void parse(INI *ini);
};

template <int Category>
void DefaultModuleTemplate<Category>::parse(INI *ini)
{
	ini->initFromINI(this, DefaultModuleTemplate06FieldParse);
}

template void DefaultModuleTemplate<7>::parse(INI *);

}
