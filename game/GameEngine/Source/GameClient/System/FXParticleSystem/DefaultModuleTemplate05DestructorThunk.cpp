// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DefaultModuleTemplate<6> empty dual-vtbl dtor (50B Sphere pattern).
// The three tables this dtor installs are the classes' own vftables (global
// Snapshot, FXParticleSystem::CategoryModuleInfo<5> and
// FXParticleSystem::ModuleTemplate), each defined by its own provider TU.
// __identifier names them by their real link name, the mechanism
// CameraPath_dtor.cpp uses, so this object references the real symbols directly
// and no linker alias stands in for them.
extern "C" const void *__identifier("??_7Snapshot@@6B@")[];
extern "C" const void *__identifier("??_7?$CategoryModuleInfo@$05@FXParticleSystem@@6B@")[];
extern "C" const void *__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")[];

namespace FXParticleSystem
{

template <int Category>
class DefaultModuleTemplate
{
};

template <>
class __declspec(novtable) DefaultModuleTemplate<6>
{
public:
	virtual ~DefaultModuleTemplate();
};

DefaultModuleTemplate<6>::~DefaultModuleTemplate()
{
	unsigned char *info = this ? (unsigned char *)this + 8 : 0;
	*(volatile unsigned int *)info = (unsigned int)__identifier("??_7Snapshot@@6B@");

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base =
		(unsigned int)__identifier("??_7?$CategoryModuleInfo@$05@FXParticleSystem@@6B@");
	*(volatile unsigned int *)this =
		(unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");
}

}
