// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplateBase<3> empty dual-vtbl dtor.

extern "C" const void *bfmeVftModuleTemplate[];
#pragma comment(linker, "/alternatename:_bfmeVftModuleTemplate=??_7ModuleTemplate@FXParticleSystem@@6B@")
extern "C" const void *bfmeVftCategoryModuleInfo3[];
#pragma comment(linker, "/alternatename:_bfmeVftCategoryModuleInfo3=??_7?$CategoryModuleInfo@$02@FXParticleSystem@@6B@")

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplateBase
{
};

template <>
class __declspec(novtable) CategoryModuleTemplateBase<3>
{
public:
	virtual ~CategoryModuleTemplateBase();
};

// ??1?$CategoryModuleTemplateBase@$02@FXParticleSystem@@UAE@XZ
CategoryModuleTemplateBase<3>::~CategoryModuleTemplateBase()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)bfmeVftCategoryModuleInfo3;
	*(volatile unsigned int *)this = (unsigned int)bfmeVftModuleTemplate;
}

}
