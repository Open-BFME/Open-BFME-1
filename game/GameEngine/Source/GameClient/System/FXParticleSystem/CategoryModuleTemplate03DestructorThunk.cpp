// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplate<4> empty dual-vtbl dtor.

extern "C" int __identifier("??_7?$CategoryModuleInfo@$03@FXParticleSystem@@6B@");
extern "C" int __identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplate
{
};

template <>
class __declspec(novtable) CategoryModuleTemplate<4>
{
public:
	virtual ~CategoryModuleTemplate();
};

// ??1?$CategoryModuleTemplate@$03@FXParticleSystem@@UAE@XZ
CategoryModuleTemplate<4>::~CategoryModuleTemplate()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)&__identifier("??_7?$CategoryModuleInfo@$03@FXParticleSystem@@6B@");
	*(volatile unsigned int *)this = (unsigned int)&__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");
}

}
