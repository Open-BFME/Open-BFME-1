// cl: /DNDEBUG /MD /EHsc

// Retail's own vftable symbols are referenced directly under their decorated
// names, so no linker stand-in alias is needed (see WideSlotSetup.cpp).
extern "C" const void *__identifier("??_7Snapshot@@6B@")[];
extern "C" const void *__identifier("??_7?$CategoryModuleInfo@$04@FXParticleSystem@@6B@")[];
extern "C" const void *__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")[];

namespace FXParticleSystem
{

// The matched scalar and vector deleting destructors identify this instance.
// Retail's destructor restores its three subobject vfptrs at +0, +4 and +8.
struct PointEmissionVolumeModuleTag;

template <class ModuleTag>
class __declspec(novtable) ConcreteModuleTemplate
{
public:
	virtual ~ConcreteModuleTemplate();
};

template <>
ConcreteModuleTemplate<PointEmissionVolumeModuleTag>::~ConcreteModuleTemplate()
{
	// Keep these as explicit ABI stores; __declspec(novtable) preserves the
	// retail null-adjustment shape without introducing a local vftable.
	unsigned char *info = this ? (unsigned char *)this + 8 : 0;
	*(volatile unsigned int *)info = (unsigned int)__identifier("??_7Snapshot@@6B@");

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base =
		(unsigned int)__identifier("??_7?$CategoryModuleInfo@$04@FXParticleSystem@@6B@");
	*(volatile unsigned int *)this = (unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");
}

}
