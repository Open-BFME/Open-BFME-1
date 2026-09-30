// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplateBase (ledger $03 / N=4) empty dual-vtbl dtor.

extern "C" const void *bfmeVftModuleTemplate[];
#pragma comment(linker, "/alternatename:_bfmeVftModuleTemplate=??_7ModuleTemplate@FXParticleSystem@@6B@")
extern "C" const void *bfmeVftCategoryModuleInfo4[];
#pragma comment(linker, "/alternatename:_bfmeVftCategoryModuleInfo4=??_7?$CategoryModuleInfo@$03@FXParticleSystem@@6B@")

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplateBase
{
};

// MSVC mangles CategoryModuleTemplateBase<4> as @$03
template <>
class __declspec(novtable) CategoryModuleTemplateBase<4>
{
public:
	virtual ~CategoryModuleTemplateBase();
};

// ??1?$CategoryModuleTemplateBase@$03@FXParticleSystem@@UAE@XZ
CategoryModuleTemplateBase<4>::~CategoryModuleTemplateBase()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)bfmeVftCategoryModuleInfo4;
	*(volatile unsigned int *)this = (unsigned int)bfmeVftModuleTemplate;
}

}
