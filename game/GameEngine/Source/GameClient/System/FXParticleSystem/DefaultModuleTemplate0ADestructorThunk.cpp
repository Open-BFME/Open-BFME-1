// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DefaultModuleTemplate<0> empty dual-vtbl dtor (50B Sphere pattern).
extern "C" void *__identifier("??_7Snapshot@@6B@")[];
extern "C" void *__identifier("??_7?$CategoryModuleInfo@$0A@@FXParticleSystem@@6B@")[];
extern "C" void *__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")[];

namespace FXParticleSystem
{

template <int Category>
class DefaultModuleTemplate
{
};

template <>
class __declspec(novtable) DefaultModuleTemplate<0>
{
public:
	virtual ~DefaultModuleTemplate();
};

DefaultModuleTemplate<0>::~DefaultModuleTemplate()
{
	unsigned char *info = this ? (unsigned char *)this + 8 : 0;
	*(volatile unsigned int *)info = (unsigned int)__identifier("??_7Snapshot@@6B@");

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)__identifier("??_7?$CategoryModuleInfo@$0A@@FXParticleSystem@@6B@");
	*(volatile unsigned int *)this = (unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");
}

}
