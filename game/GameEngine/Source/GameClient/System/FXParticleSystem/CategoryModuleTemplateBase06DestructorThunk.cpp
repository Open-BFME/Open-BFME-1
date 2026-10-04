// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplateBase<7> empty dual-vtbl dtor (ledger $06).

// fx_particle_system.h declares both classes; the retail vtables are named
// directly (same __identifier idiom as ServiceHubImpl_dtor.cpp) so no linker
// alias stand-in is needed.
extern "C" const void *__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")[];
extern "C" const void *__identifier("??_7?$CategoryModuleInfo@$06@FXParticleSystem@@6B@")[];

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplateBase
{
};

template <>
class __declspec(novtable) CategoryModuleTemplateBase<7>
{
public:
	virtual ~CategoryModuleTemplateBase();
};

// ??1?$CategoryModuleTemplateBase@$06@FXParticleSystem@@UAE@XZ
CategoryModuleTemplateBase<7>::~CategoryModuleTemplateBase()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)__identifier("??_7?$CategoryModuleInfo@$06@FXParticleSystem@@6B@");
	*(volatile unsigned int *)this = (unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");
}

}
