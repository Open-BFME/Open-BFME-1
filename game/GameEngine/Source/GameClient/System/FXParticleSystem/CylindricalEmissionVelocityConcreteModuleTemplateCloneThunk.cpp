// cl: /DNDEBUG /MD /GX- /O2 /Ob2 /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib

#include "fx_particle_system.h"
#include <new>

// Open-BFME5: CylindricalEmissionVelocity ConcreteModuleTemplate::clone

namespace FXParticleSystem
{

struct CylindricalEmissionVelocityModuleTag {};

template <>
class ConcreteModuleTemplate<CylindricalEmissionVelocityModuleTag>
{
public:
	virtual CylindricalEmissionVelocityModuleTemplate *clone() const;

private:
	unsigned char m_pad[0x20];
};

// ?clone@?$ConcreteModuleTemplate@UCylindricalEmissionVelocityModuleTag@FXParticleSystem@@@FXParticleSystem@@UBEPAVCylindricalEmissionVelocityModuleTemplate@2@XZ
CylindricalEmissionVelocityModuleTemplate *ConcreteModuleTemplate<CylindricalEmissionVelocityModuleTag>::clone() const
{
	typedef ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME,
		CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate,
		DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > RealTag;
	typedef ConcreteModuleTemplate<RealTag> RealTemplate;
	void *storage = ::operator new(sizeof(ConcreteModuleTemplate<CylindricalEmissionVelocityModuleTag>));
	if (storage)
		return (CylindricalEmissionVelocityModuleTemplate *)::new (storage) RealTemplate(*(const RealTemplate *)this);
	return 0;
}

}
