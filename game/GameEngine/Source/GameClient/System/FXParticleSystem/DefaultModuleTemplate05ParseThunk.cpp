// cl: /DNDEBUG /MD /GX- /O2 /Ob2 /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: DefaultModuleTemplate<6>::parse -> INI::initFromINI(this, FieldParse).

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
#include "Common/INI/INI.h"

// Retail .rdata VA 0x01113594 (16 B): no fields, only the zero terminator.
extern "C" const FieldParse DefaultModuleTemplate05FieldParse[] =
{
	{ 0, 0, 0, 0 }
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
	ini->initFromINI(this, DefaultModuleTemplate05FieldParse);
}

template void DefaultModuleTemplate<6>::parse(INI *);
}
