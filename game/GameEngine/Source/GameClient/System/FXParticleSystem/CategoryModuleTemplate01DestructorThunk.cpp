// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplate<2> empty dual-vtbl dtor.

// Retail writes the CategoryModuleInfo<1> and ModuleTemplate vtable pointers
// into the object; both symbols are the compiler's own vftables, so they are
// named by their decorated symbol rather than through a linker alias pragma.
extern "C" const void *__identifier("??_7?$CategoryModuleInfo@$01@FXParticleSystem@@6B@")[];
extern "C" const void *__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")[];

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplate
{
};

template <>
class __declspec(novtable) CategoryModuleTemplate<2>
{
public:
	virtual ~CategoryModuleTemplate();
};

// ??1?$CategoryModuleTemplate@$01@FXParticleSystem@@UAE@XZ
CategoryModuleTemplate<2>::~CategoryModuleTemplate()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)__identifier("??_7?$CategoryModuleInfo@$01@FXParticleSystem@@6B@");
	*(volatile unsigned int *)this = (unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");
}

}
