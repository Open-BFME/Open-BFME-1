// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplate<0> empty dual-vtbl dtor.

// Retail dual-vtable layout: CategoryModuleInfo<0> table sits at this+4,
// ModuleTemplate's at +0.  Bound directly by the decorated name.
extern "C" void *__identifier("??_7?$CategoryModuleInfo@$0A@@FXParticleSystem@@6B@")[];
extern "C" void *__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")[];

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplate
{
};

template <>
class __declspec(novtable) CategoryModuleTemplate<0>
{
public:
	virtual ~CategoryModuleTemplate();
};

// ??1?$CategoryModuleTemplate@$0A@@FXParticleSystem@@UAE@XZ
CategoryModuleTemplate<0>::~CategoryModuleTemplate()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)__identifier("??_7?$CategoryModuleInfo@$0A@@FXParticleSystem@@6B@");
	*(volatile unsigned int *)this = (unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");
}

}
