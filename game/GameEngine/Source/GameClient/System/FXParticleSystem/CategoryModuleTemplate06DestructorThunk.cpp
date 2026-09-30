// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplate (ledger $05 / N=6) empty dual-vtbl dtor.

extern "C" const void *bfmeVftCategoryModuleInfo6[];
#pragma comment(linker, "/alternatename:_bfmeVftCategoryModuleInfo6=??_7?$CategoryModuleInfo@$05@FXParticleSystem@@6B@")
extern "C" const void *bfmeVftModuleTemplate[];
#pragma comment(linker, "/alternatename:_bfmeVftModuleTemplate=??_7ModuleTemplate@FXParticleSystem@@6B@")

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplate
{
};

template <>
class __declspec(novtable) CategoryModuleTemplate<6>
{
public:
	virtual ~CategoryModuleTemplate();
};

// ??1?$CategoryModuleTemplate@$05@FXParticleSystem@@UAE@XZ
CategoryModuleTemplate<6>::~CategoryModuleTemplate()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)bfmeVftCategoryModuleInfo6;
	*(volatile unsigned int *)this = (unsigned int)bfmeVftModuleTemplate;
}

}
