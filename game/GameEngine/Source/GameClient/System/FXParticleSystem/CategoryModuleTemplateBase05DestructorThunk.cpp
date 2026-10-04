// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplateBase (ledger $05 / N=6) empty dual-vtbl dtor.

// These are the existing vftable definitions at the two retail addresses:
// ModuleTemplate is declared in fx_particle_system.h (upstream ModuleFactory.h
// layout) and CategoryModuleInfo<5> is explicitly instantiated in
// fx_particle_system.cpp. Both are named here by their own decorated spelling
// via __identifier, the same way BfmeConv651.cpp names the sibling
// ??_7?$CategoryModuleInfo@$03@FXParticleSystem@@6B@, so no linker alias is
// needed to bind them.
extern "C" void *__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")[ ];
extern "C" void *__identifier("??_7?$CategoryModuleInfo@$05@FXParticleSystem@@6B@")[ ];

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplateBase
{
};

template <>
class __declspec(novtable) CategoryModuleTemplateBase<6>
{
public:
	virtual ~CategoryModuleTemplateBase();
};

// ??1?$CategoryModuleTemplateBase@$05@FXParticleSystem@@UAE@XZ
CategoryModuleTemplateBase<6>::~CategoryModuleTemplateBase()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)(size_t)__identifier("??_7?$CategoryModuleInfo@$05@FXParticleSystem@@6B@");
	*(volatile unsigned int *)this = (unsigned int)(size_t)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");
}

}
