// cl: /DNDEBUG /MD /EHsc

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
	*(volatile unsigned int *)info = 0x01073744;

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110f9ac;
	*(volatile unsigned int *)this = 0x01073758;
}

}
