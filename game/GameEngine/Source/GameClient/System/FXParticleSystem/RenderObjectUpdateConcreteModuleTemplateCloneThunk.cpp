// cl: /DNDEBUG /MD /GX- /O2 /Ob2 /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib

#include <new>
#include "fx_particle_system.h"

void *__cdecl operator new(unsigned int);

// Open-BFME5: RenderObjectUpdate ConcreteModuleTemplate::clone
// Retail: new(0xa0); copy-ctor; return.

namespace FXParticleSystem
{

struct RenderObjectUpdateModuleTag
{
};

template <>
class ConcreteModuleTemplate<RenderObjectUpdateModuleTag> : public RenderObjectUpdateModuleTemplate
{
public:
	ConcreteModuleTemplate(const ConcreteModuleTemplate &);
	virtual RenderObjectUpdateModuleTemplate *clone() const;

private:
	unsigned char m_pad[0x9c];
};

RenderObjectUpdateModuleTemplate *ConcreteModuleTemplate<RenderObjectUpdateModuleTag>::clone() const
{
	typedef ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY,
		RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule,
		RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule,
		RenderObjectParticleUpdateModuleTemplate> > RetailTemplate;
	return reinterpret_cast<RenderObjectUpdateModuleTemplate *>(
		new (::operator new(0xa0)) RetailTemplate(*reinterpret_cast<const RetailTemplate *>(this)));
}

}
