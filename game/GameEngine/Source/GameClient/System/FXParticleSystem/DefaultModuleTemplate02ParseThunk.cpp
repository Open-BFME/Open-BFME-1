// cl: /O2 /GR- /EHsc- /DNDEBUG /DWIN32 /D_WINDOWS /MD /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// Open-BFME5: DefaultModuleTemplate<3>::parse -> INI::initFromINI(this, FieldParse).

// The ZH Common/INI.h declares initFromINI with the retail signature
// (void *, const FieldParse *) and the INI::parseReal/parseCoord3D statics
// the table below names; BFME's Common/INI/INI.h declares neither parser.
#include "PreRTS.h"
#include "Common/INI.h"

// Retail .rdata 0x011145B0, 64 bytes: Gravity (INI::parseReal, 0x18),
// VelocityDamping through ILT 0x00036615 (-> 0x004B8F60,
// parseGameClientRandomVariable, 0x1C) and DriftVelocity
// (INI::parseCoord3D, 0xC), plus the zero terminator.
void j_00036615();
extern "C" const FieldParse DefaultModuleTemplate02FieldParse[] =
{
	{ "Gravity",	INI::parseReal,	0,	0x18 },
	{ "VelocityDamping",	(INIFieldParseProc)j_00036615,	0,	0x1C },
	{ "DriftVelocity",	INI::parseCoord3D,	0,	0xC },
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
	ini->initFromINI(this, DefaultModuleTemplate02FieldParse);
}

template void DefaultModuleTemplate<3>::parse(INI *);
}
