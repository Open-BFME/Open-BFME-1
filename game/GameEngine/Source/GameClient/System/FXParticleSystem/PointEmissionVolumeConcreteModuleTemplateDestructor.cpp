// cl: /DNDEBUG /MD /EHsc

extern "C" const void *bfmeVftSnapshot[];
#pragma comment(linker, "/alternatename:_bfmeVftSnapshot=??_7Snapshot@@6B@")
extern "C" const void *bfmeVftCategoryModuleInfo5[];
#pragma comment(linker, "/alternatename:_bfmeVftCategoryModuleInfo5=??_7?$CategoryModuleInfo@$04@FXParticleSystem@@6B@")
extern "C" const void *bfmeVftModuleTemplate[];
#pragma comment(linker, "/alternatename:_bfmeVftModuleTemplate=??_7ModuleTemplate@FXParticleSystem@@6B@")

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
	*(volatile unsigned int *)info = (unsigned int)bfmeVftSnapshot;

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)bfmeVftCategoryModuleInfo5;
	*(volatile unsigned int *)this = (unsigned int)bfmeVftModuleTemplate;
}

}
