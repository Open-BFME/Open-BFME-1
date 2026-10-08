// cl: /O2 /GR- /EHsc- /DNDEBUG /DWIN32 /D_WINDOWS /MD /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// Open-BFME5: DefaultModuleTemplate<2>::parse -> INI::initFromINI(this, FieldParse).

// The ZH Common/INI.h declares initFromINI with the retail signature
// (void *, const FieldParse *) and the INI::parse* statics the table below
// names; BFME's Common/INI/INI.h declares none of those parsers.
#include "PreRTS.h"
#include "Common/INI.h"

// Retail .rdata 0x01114958, 112 bytes: SizeRate, SizeRateDamping, AngleZ,
// AngularRateZ and AngularDamping through ILT 0x00036615 (-> 0x004B8F60,
// parseGameClientRandomVariable) and Rotation (INI::parseIndexList over
// FXParticleSystem::RotationTypeNames, 0x48), plus the zero terminator;
// tokens, parsers, userData and offsets read from the image.
// Exported retail table at VA 0x01110258 (exports.csv names it
// ?RotationTypeNames@FXParticleSystem@@3QBQBDB): six keywords and the null
// parseIndexList stops at, read from the image.
extern "C" const char *const __identifier("?RotationTypeNames@FXParticleSystem@@3QBQBDB")[7] =
{
	"NONE", "ROTATION_OFF", "ROTATE_X", "ROTATE_Y", "ROTATE_Z", "ROTATE_V", 0
};

namespace FXParticleSystem
{
extern const char *const RotationTypeNames[7];
}

void j_00036615();
extern "C" const FieldParse DefaultModuleTemplate01FieldParse[] =
{
	{ "SizeRate",	(INIFieldParseProc)j_00036615,	0,	0xC },
	{ "SizeRateDamping",	(INIFieldParseProc)j_00036615,	0,	0x18 },
	{ "AngleZ",	(INIFieldParseProc)j_00036615,	0,	0x24 },
	{ "AngularRateZ",	(INIFieldParseProc)j_00036615,	0,	0x30 },
	{ "AngularDamping",	(INIFieldParseProc)j_00036615,	0,	0x3C },
	{ "Rotation",	INI::parseIndexList,	FXParticleSystem::RotationTypeNames,	0x48 },
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
	ini->initFromINI(this, DefaultModuleTemplate01FieldParse);
}

template void DefaultModuleTemplate<2>::parse(INI *);
}
