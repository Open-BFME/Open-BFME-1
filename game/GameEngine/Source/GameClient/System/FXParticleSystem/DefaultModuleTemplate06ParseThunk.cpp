// cl: /DNDEBUG /MD /GX- /O2 /Ob2 /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: DefaultModuleTemplate<7>::parse -> INI::initFromINI(this, FieldParse).

#include "Common/INI/INI.h"

namespace FXParticleSystem
{

template <int Category>
class DefaultModuleTemplate
{
public:
	void parse(INI *ini);
};

extern "C" char DefaultModuleTemplate06FieldParse;

template <int Category>
void DefaultModuleTemplate<Category>::parse(INI *ini)
{
	ini->initFromINI(this, (const FieldParse *)&DefaultModuleTemplate06FieldParse);
}

template void DefaultModuleTemplate<7>::parse(INI *);

}
