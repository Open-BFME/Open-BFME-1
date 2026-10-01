// cl: /DNDEBUG /MD /GX- /O2 /Ob2 /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: DefaultModuleTemplate<2>::parse -> INI::initFromINI(this, FieldParse).

// BFME's own Common/INI/INI.h already declares initFromINI with the retail
// signature (void *, const FieldParse *); the stand-in spelled the second
// parameter `const void *` and so mangled to PAXPBX, which nothing defines.
#include "Common/INI/INI.h"

namespace FXParticleSystem
{
template <int Category>
class DefaultModuleTemplate
{
public:
	void parse(INI *ini);
};

extern "C" char DefaultModuleTemplate01FieldParse;

template <int Category>
void DefaultModuleTemplate<Category>::parse(INI *ini)
{
	ini->initFromINI(this, (const FieldParse *)&DefaultModuleTemplate01FieldParse);
}

template void DefaultModuleTemplate<2>::parse(INI *);
}
