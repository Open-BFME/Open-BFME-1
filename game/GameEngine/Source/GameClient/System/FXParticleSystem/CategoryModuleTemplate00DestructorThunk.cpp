// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplate<1> empty dual-vtbl dtor.

extern "C" const void *bfmeVftV3Vt0110F978[];
#pragma comment(linker, "/alternatename:_bfmeVftV3Vt0110F978=??_7V3Vt0110F978@@6B@")
extern "C" const void *bfmeVftModuleTemplate[];
#pragma comment(linker, "/alternatename:_bfmeVftModuleTemplate=??_7ModuleTemplate@FXParticleSystem@@6B@")

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplate
{
};

template <>
class __declspec(novtable) CategoryModuleTemplate<1>
{
public:
	virtual ~CategoryModuleTemplate();
};

// ??1?$CategoryModuleTemplate@$00@FXParticleSystem@@UAE@XZ
CategoryModuleTemplate<1>::~CategoryModuleTemplate()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)bfmeVftV3Vt0110F978;
	*(volatile unsigned int *)this = (unsigned int)bfmeVftModuleTemplate;
}

}
