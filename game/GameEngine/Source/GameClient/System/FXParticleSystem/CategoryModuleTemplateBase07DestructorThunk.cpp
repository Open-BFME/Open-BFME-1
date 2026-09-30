// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplateBase (ledger $07 / N=8) empty dual-vtbl dtor.

extern "C" const void *bfmeVftCategoryModuleInfo8[];
#pragma comment(linker, "/alternatename:_bfmeVftCategoryModuleInfo8=??_7?$CategoryModuleInfo@$07@FXParticleSystem@@6B@")
extern "C" const void *bfmeVftModuleTemplate[];
#pragma comment(linker, "/alternatename:_bfmeVftModuleTemplate=??_7ModuleTemplate@FXParticleSystem@@6B@")

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplateBase
{
};

template <>
class __declspec(novtable) CategoryModuleTemplateBase<8>
{
public:
	virtual ~CategoryModuleTemplateBase();
};

// ??1?$CategoryModuleTemplateBase@$07@FXParticleSystem@@UAE@XZ
CategoryModuleTemplateBase<8>::~CategoryModuleTemplateBase()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)bfmeVftCategoryModuleInfo8;
	*(volatile unsigned int *)this = (unsigned int)bfmeVftModuleTemplate;
}

}
