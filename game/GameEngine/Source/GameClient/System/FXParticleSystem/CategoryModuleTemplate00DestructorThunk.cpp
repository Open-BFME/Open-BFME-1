// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplate<1> empty dual-vtbl dtor.

// Retail vftables referenced by the two stores below. __identifier names the
// retail-mangled symbol directly, so no linker stand-in alias is needed.
extern "C" void *__identifier("??_7V3Vt0110F978@@6B@")[];
extern "C" void *__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")[];

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplate
{
};

template <>
class __declspec(novtable) CategoryModuleTemplate<1>
{
public:
	virtual ~CategoryModuleTemplate();
};

// ??1?$CategoryModuleTemplate@$00@FXParticleSystem@@UAE@XZ
CategoryModuleTemplate<1>::~CategoryModuleTemplate()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)__identifier("??_7V3Vt0110F978@@6B@");
	*(volatile unsigned int *)this = (unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");
}

}
