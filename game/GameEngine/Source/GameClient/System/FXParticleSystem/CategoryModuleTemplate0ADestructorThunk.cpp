// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplate<0> empty dual-vtbl dtor.

extern "C" const void *bfmeVftCategoryModuleInfo0[];
#pragma comment(linker, "/alternatename:_bfmeVftCategoryModuleInfo0=??_7?$CategoryModuleInfo@$0A@@FXParticleSystem@@6B@")
extern "C" const void *bfmeVftModuleTemplate[];
#pragma comment(linker, "/alternatename:_bfmeVftModuleTemplate=??_7ModuleTemplate@FXParticleSystem@@6B@")

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
	*(volatile unsigned int *)base = (unsigned int)bfmeVftCategoryModuleInfo0;
	*(volatile unsigned int *)this = (unsigned int)bfmeVftModuleTemplate;
}

}
