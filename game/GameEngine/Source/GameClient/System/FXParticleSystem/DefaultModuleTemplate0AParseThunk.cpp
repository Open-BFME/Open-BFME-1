// cl: /DNDEBUG /MD /GX- /O2 /Ob2 /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: DefaultModuleTemplate<0>::parse -> INI::initFromINI(this, FieldParse).

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
#include "Common/INI/INI.h"

// Retail .rdata 0x01113460, 160 bytes: Color1..Color8 through the
// parseRGBColorKeyframe ILT and ColorScale through the ILT to
// parseGameClientRandomVariable (0x004B8F60), plus the zero terminator.
// Parsers are named by their incremental-link thunk rows.
void j_0000fabf();
void j_00036615();
extern "C" const FieldParse DefaultModuleTemplate0AFieldParse[] =
{
	{ "Color1",	(INIFieldParseProc)j_0000fabf,	0,	0xC },
	{ "Color2",	(INIFieldParseProc)j_0000fabf,	0,	0x1C },
	{ "Color3",	(INIFieldParseProc)j_0000fabf,	0,	0x2C },
	{ "Color4",	(INIFieldParseProc)j_0000fabf,	0,	0x3C },
	{ "Color5",	(INIFieldParseProc)j_0000fabf,	0,	0x4C },
	{ "Color6",	(INIFieldParseProc)j_0000fabf,	0,	0x5C },
	{ "Color7",	(INIFieldParseProc)j_0000fabf,	0,	0x6C },
	{ "Color8",	(INIFieldParseProc)j_0000fabf,	0,	0x7C },
	{ "ColorScale",	(INIFieldParseProc)j_00036615,	0,	0x8C },
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
	ini->initFromINI(this, DefaultModuleTemplate0AFieldParse);
}

template void DefaultModuleTemplate<0>::parse(INI *);
}
