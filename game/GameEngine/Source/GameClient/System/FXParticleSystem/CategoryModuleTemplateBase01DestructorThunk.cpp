// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplateBase<2> empty dual-vtbl dtor.

// retail 0x01073758: ModuleTemplate's own vftable, this body restores it at +0.
// Spelled as its defining object spells it (fx_particle_system.h:559), so the
// linker needs no stand-in alias at all.
extern "C" const void *__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")[];
// retail 0x0110F9E8: CategoryModuleInfo<2>'s own vftable, restored at +4.
// $01 is the mangled form of the template argument 2 (fx_particle_system.h:568).
extern "C" const void *__identifier("??_7?$CategoryModuleInfo@$01@FXParticleSystem@@6B@")[];

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplateBase
{
};

template <>
class __declspec(novtable) CategoryModuleTemplateBase<2>
{
public:
	virtual ~CategoryModuleTemplateBase();
};

// ??1?$CategoryModuleTemplateBase@$01@FXParticleSystem@@UAE@XZ
CategoryModuleTemplateBase<2>::~CategoryModuleTemplateBase()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)__identifier("??_7?$CategoryModuleInfo@$01@FXParticleSystem@@6B@");
	*(volatile unsigned int *)this = (unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");
}

}