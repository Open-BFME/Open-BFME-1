// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplate<5> empty dual-vtbl dtor.

extern "C" const void *bfmeVftCategoryModuleInfo5[];
#pragma comment(linker, "/alternatename:_bfmeVftCategoryModuleInfo5=??_7?$CategoryModuleInfo@$04@FXParticleSystem@@6B@")
extern "C" const void *bfmeVftModuleTemplate[];
#pragma comment(linker, "/alternatename:_bfmeVftModuleTemplate=??_7ModuleTemplate@FXParticleSystem@@6B@")

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplate
{
};

template <>
class __declspec(novtable) CategoryModuleTemplate<5>
{
public:
	virtual ~CategoryModuleTemplate();
};

// ??1?$CategoryModuleTemplate@$04@FXParticleSystem@@UAE@XZ
CategoryModuleTemplate<5>::~CategoryModuleTemplate()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)bfmeVftCategoryModuleInfo5;
	*(volatile unsigned int *)this = (unsigned int)bfmeVftModuleTemplate;
}

}
