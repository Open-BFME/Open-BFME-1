// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SphereEmissionVolumeModuleTemplate empty dual-vtbl dtor.
// Retail 50B: this+8 / this+4 / this vtbl stores (DIR32-masked).

extern "C" void *bfmeVftSnapshotBase[4];
#pragma comment(linker, "/alternatename:_bfmeVftSnapshotBase=??_7BfmeBaseVUQ@@6B@")
extern "C" const void *bfmeVftCategoryModuleInfo5[];
#pragma comment(linker, "/alternatename:_bfmeVftCategoryModuleInfo5=??_7?$CategoryModuleInfo@$04@FXParticleSystem@@6B@")
extern "C" const void *bfmeVftModuleTemplate[];
#pragma comment(linker, "/alternatename:_bfmeVftModuleTemplate=??_7ModuleTemplate@FXParticleSystem@@6B@")

namespace FXParticleSystem
{

class __declspec(novtable) SphereEmissionVolumeModuleTemplate
{
public:
	virtual ~SphereEmissionVolumeModuleTemplate();
};

// ??1SphereEmissionVolumeModuleTemplate@FXParticleSystem@@UAE@XZ
SphereEmissionVolumeModuleTemplate::~SphereEmissionVolumeModuleTemplate()
{
	unsigned char *info = this ? (unsigned char *)this + 8 : 0;
	*(volatile unsigned int *)info = (unsigned int)bfmeVftSnapshotBase;

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)bfmeVftCategoryModuleInfo5;
	*(volatile unsigned int *)this = (unsigned int)bfmeVftModuleTemplate;
}

}
