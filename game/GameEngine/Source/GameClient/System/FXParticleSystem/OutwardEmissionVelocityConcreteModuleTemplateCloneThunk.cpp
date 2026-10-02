// cl: /DNDEBUG /MD /GX- /O2 /Ob2 /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib

#include "fx_particle_system.h"
#include <new>

// Open-BFME5: OutwardEmissionVelocity ConcreteModuleTemplate::clone

namespace FXParticleSystem
{

struct OutwardEmissionVelocityModuleTag {};

template <>
class ConcreteModuleTemplate<OutwardEmissionVelocityModuleTag>
{
public:
	virtual OutwardEmissionVelocityModuleTemplate *clone() const;

private:
	unsigned char m_pad[0x20];
};

// ?clone@?$ConcreteModuleTemplate@UOutwardEmissionVelocityModuleTag@FXParticleSystem@@@FXParticleSystem@@UBEPAVOutwardEmissionVelocityModuleTemplate@2@XZ
OutwardEmissionVelocityModuleTemplate *ConcreteModuleTemplate<OutwardEmissionVelocityModuleTag>::clone() const
{
	typedef ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME,
		OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate,
		DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > RealTag;
	typedef ConcreteModuleTemplate<RealTag> RealTemplate;
	void *storage = ::operator new(sizeof(ConcreteModuleTemplate<OutwardEmissionVelocityModuleTag>));
	if (storage)
		return (OutwardEmissionVelocityModuleTemplate *)::new (storage) RealTemplate(*(const RealTemplate *)this);
	return 0;
}

}
