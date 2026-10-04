// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DefaultModuleTemplate<1> empty dual-vtbl dtor (50B Sphere pattern).

// The three vftables are named by their retail symbols in
// targets/game/reverse/dir32_addresses.csv (Snapshot 0x01073744, V3Vt0110F978
// 0x0110F978, FXParticleSystem::ModuleTemplate 0x01073758).  __identifier
// spells the defining name exactly, so the stores below reference it directly
// and no linker alias stand-in is needed.
extern "C" const char __identifier("??_7Snapshot@@6B@")[];
extern "C" const char __identifier("??_7V3Vt0110F978@@6B@")[];
extern "C" const char __identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")[];

namespace FXParticleSystem
{

template <int Category>
class DefaultModuleTemplate
{
};

template <>
class __declspec(novtable) DefaultModuleTemplate<1>
{
public:
	virtual ~DefaultModuleTemplate();
};

DefaultModuleTemplate<1>::~DefaultModuleTemplate()
{
	unsigned char *info = this ? (unsigned char *)this + 8 : 0;
	*(volatile unsigned int *)info = (unsigned int)__identifier("??_7Snapshot@@6B@");

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)__identifier("??_7V3Vt0110F978@@6B@");
	*(volatile unsigned int *)this = (unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");
}

}
