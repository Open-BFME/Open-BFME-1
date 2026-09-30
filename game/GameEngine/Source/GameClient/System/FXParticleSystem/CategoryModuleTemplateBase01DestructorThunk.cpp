// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplateBase<2> empty dual-vtbl dtor.

extern "C" const void *bfmeVftModuleTemplate[];
#pragma comment(linker, "/alternatename:_bfmeVftModuleTemplate=??_7ModuleTemplate@FXParticleSystem@@6B@")
extern "C" const void *bfmeVftCategoryModuleInfo2[];
#pragma comment(linker, "/alternatename:_bfmeVftCategoryModuleInfo2=??_7?$CategoryModuleInfo@$01@FXParticleSystem@@6B@")

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
	*(volatile unsigned int *)base = (unsigned int)bfmeVftCategoryModuleInfo2;
	*(volatile unsigned int *)this = (unsigned int)bfmeVftModuleTemplate;
}

}
