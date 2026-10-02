// cl: /DNDEBUG /MD /GX- /O2 /Ob2 /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib

#include "fx_particle_system.h"
#include <new>

// Open-BFME5: HemisphericalEmissionVelocity ConcreteModuleTemplate::clone

namespace FXParticleSystem
{

struct HemisphericalEmissionVelocityModuleTag {};

template <>
class ConcreteModuleTemplate<HemisphericalEmissionVelocityModuleTag>
{
public:
	virtual HemisphericalEmissionVelocityModuleTemplate *clone() const;

private:
	unsigned char m_pad[0x14];
};

// ?clone@?$ConcreteModuleTemplate@UHemisphericalEmissionVelocityModuleTag@FXParticleSystem@@@FXParticleSystem@@UBEPAVHemisphericalEmissionVelocityModuleTemplate@2@XZ
HemisphericalEmissionVelocityModuleTemplate *ConcreteModuleTemplate<HemisphericalEmissionVelocityModuleTag>::clone() const
{
	typedef ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME,
		HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate,
		DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > RealTag;
	typedef ConcreteModuleTemplate<RealTag> RealTemplate;
	void *storage = ::operator new(sizeof(ConcreteModuleTemplate<HemisphericalEmissionVelocityModuleTag>));
	if (storage)
		return (HemisphericalEmissionVelocityModuleTemplate *)::new (storage) RealTemplate(*(const RealTemplate *)this);
	return 0;
}

}
