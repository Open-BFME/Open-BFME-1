// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplateBase<7> empty dual-vtbl dtor (ledger $06).

extern "C" const void *bfmeVftModuleTemplate[];
#pragma comment(linker, "/alternatename:_bfmeVftModuleTemplate=??_7ModuleTemplate@FXParticleSystem@@6B@")
extern "C" const void *bfmeVftCategoryModuleInfo7[];
#pragma comment(linker, "/alternatename:_bfmeVftCategoryModuleInfo7=??_7?$CategoryModuleInfo@$06@FXParticleSystem@@6B@")

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplateBase
{
};

template <>
class __declspec(novtable) CategoryModuleTemplateBase<7>
{
public:
	virtual ~CategoryModuleTemplateBase();
};

// ??1?$CategoryModuleTemplateBase@$06@FXParticleSystem@@UAE@XZ
CategoryModuleTemplateBase<7>::~CategoryModuleTemplateBase()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)bfmeVftCategoryModuleInfo7;
	*(volatile unsigned int *)this = (unsigned int)bfmeVftModuleTemplate;
}

}
