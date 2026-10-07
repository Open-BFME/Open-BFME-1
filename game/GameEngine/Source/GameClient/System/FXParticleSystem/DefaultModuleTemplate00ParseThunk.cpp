// cl: /DNDEBUG /MD /GX- /O2 /Ob2 /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: DefaultModuleTemplate<1>::parse -> INI::initFromINI(this, FieldParse).

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

}

class ParticleSystemTemplate
{
public:
	static void parseRandomKeyframe(INI *ini, void *instance, void *store, const void *userData);
};

// Retail .rdata VA 0x01113360 (144 B): Alpha1..Alpha8 through the
// parseRandomKeyframe ILT (0x00028CC2 -> matched body 0x005EE370) at offsets
// 0xC + 0x10*i, then a zero terminator.
extern "C" const FieldParse DefaultModuleTemplate00FieldParse[] =
{
	{ "Alpha1", ParticleSystemTemplate::parseRandomKeyframe, 0, 0xC },
	{ "Alpha2", ParticleSystemTemplate::parseRandomKeyframe, 0, 0x1C },
	{ "Alpha3", ParticleSystemTemplate::parseRandomKeyframe, 0, 0x2C },
	{ "Alpha4", ParticleSystemTemplate::parseRandomKeyframe, 0, 0x3C },
	{ "Alpha5", ParticleSystemTemplate::parseRandomKeyframe, 0, 0x4C },
	{ "Alpha6", ParticleSystemTemplate::parseRandomKeyframe, 0, 0x5C },
	{ "Alpha7", ParticleSystemTemplate::parseRandomKeyframe, 0, 0x6C },
	{ "Alpha8", ParticleSystemTemplate::parseRandomKeyframe, 0, 0x7C },
	{ 0, 0, 0, 0 }
};

namespace FXParticleSystem
{

template <int Category>
void DefaultModuleTemplate<Category>::parse(INI *ini)
{
	ini->initFromINI(this, DefaultModuleTemplate00FieldParse);
}

template void DefaultModuleTemplate<1>::parse(INI *);
}
