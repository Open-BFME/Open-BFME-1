// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplate<3> empty dual-vtbl dtor.

extern "C" const void *bfmeVftCategoryModuleInfo3[];
#pragma comment(linker, "/alternatename:_bfmeVftCategoryModuleInfo3=??_7?$CategoryModuleInfo@$02@FXParticleSystem@@6B@")
extern "C" const void *bfmeVftModuleTemplate[];
#pragma comment(linker, "/alternatename:_bfmeVftModuleTemplate=??_7ModuleTemplate@FXParticleSystem@@6B@")

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplate
{
};

template <>
class __declspec(novtable) CategoryModuleTemplate<3>
{
public:
	virtual ~CategoryModuleTemplate();
};

// ??1?$CategoryModuleTemplate@$02@FXParticleSystem@@UAE@XZ
CategoryModuleTemplate<3>::~CategoryModuleTemplate()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)bfmeVftCategoryModuleInfo3;
	*(volatile unsigned int *)this = (unsigned int)bfmeVftModuleTemplate;
}

}
