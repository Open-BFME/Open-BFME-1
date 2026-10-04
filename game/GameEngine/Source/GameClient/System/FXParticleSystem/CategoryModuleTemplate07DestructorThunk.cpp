// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplate<8> empty dual-vtbl dtor.

// Retail vftables: FXParticleSystem::CategoryModuleInfo<8>::unusedVirtual and
// FXParticleSystem::ModuleTemplate::~ModuleTemplate, defined by
// fx_particle_system.cpp (explicit template instantiation / inline dtor).
extern "C" const char __identifier("??_7?$CategoryModuleInfo@$07@FXParticleSystem@@6B@")[];
extern "C" const char __identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")[];

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplate
{
};

template <>
class __declspec(novtable) CategoryModuleTemplate<8>
{
public:
	virtual ~CategoryModuleTemplate();
};

// ??1?$CategoryModuleTemplate@$07@FXParticleSystem@@UAE@XZ
CategoryModuleTemplate<8>::~CategoryModuleTemplate()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)__identifier("??_7?$CategoryModuleInfo@$07@FXParticleSystem@@6B@");
	*(volatile unsigned int *)this = (unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");
}

}
