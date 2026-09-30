// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DefaultModuleTemplate<7> empty dual-vtbl dtor (50B Sphere pattern).
extern "C" const void *bfmeVftSnapshot[];
#pragma comment(linker, "/alternatename:_bfmeVftSnapshot=??_7Snapshot@@6B@")
extern "C" const void *bfmeVftCategoryModuleInfo7[];
#pragma comment(linker, "/alternatename:_bfmeVftCategoryModuleInfo7=??_7?$CategoryModuleInfo@$06@FXParticleSystem@@6B@")
extern "C" const void *bfmeVftModuleTemplate[];
#pragma comment(linker, "/alternatename:_bfmeVftModuleTemplate=??_7ModuleTemplate@FXParticleSystem@@6B@")

namespace FXParticleSystem
{

template <int Category>
class DefaultModuleTemplate
{
};

template <>
class __declspec(novtable) DefaultModuleTemplate<7>
{
public:
	virtual ~DefaultModuleTemplate();
};

DefaultModuleTemplate<7>::~DefaultModuleTemplate()
{
	unsigned char *info = this ? (unsigned char *)this + 8 : 0;
	*(volatile unsigned int *)info = (unsigned int)bfmeVftSnapshot;

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)bfmeVftCategoryModuleInfo7;
	*(volatile unsigned int *)this = (unsigned int)bfmeVftModuleTemplate;
}

}
