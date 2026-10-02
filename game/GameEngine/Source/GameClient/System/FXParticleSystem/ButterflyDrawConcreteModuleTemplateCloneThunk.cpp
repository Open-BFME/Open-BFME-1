// cl: /DNDEBUG /MD /GX- /O2 /Ob2 /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: ButterflyDraw ConcreteModuleTemplate::clone
// Retail: new(0x0c); copy-ctor; return.

#include "fx_particle_system.h"
#include <new>

namespace FXParticleSystem
{

struct ButterflyDrawModuleTag
{
};

typedef ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME,
	ButterflyDrawModule, ButterflyDrawModuleTemplate,
	DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > ButterflyDrawTag;
typedef ConcreteModuleTemplate<ButterflyDrawTag> ButterflyDrawConcreteModuleTemplate;

template <>
class ConcreteModuleTemplate<ButterflyDrawModuleTag>
{
public:
	virtual ButterflyDrawModuleTemplate *clone() const;

private:
	unsigned char m_pad[0x8];
};

// Mangled name matched via functions.csv claim for this source.
ButterflyDrawModuleTemplate *ConcreteModuleTemplate<ButterflyDrawModuleTag>::clone() const
{
	void *storage = ::operator new(sizeof(ConcreteModuleTemplate<ButterflyDrawModuleTag>));
	return (ButterflyDrawModuleTemplate *)::new (storage)
		ButterflyDrawConcreteModuleTemplate(*(const ButterflyDrawConcreteModuleTemplate *)this);
}

}
