// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SphereEmissionVolumeModuleTemplate empty dual-vtbl dtor.
// Retail 50B: this+8 / this+4 / this vtbl stores (DIR32-masked).

// Retail vftables the dual-vtbl dtor stores. Referenced by their real
// decorated names so no linker alias is needed.
extern "C" void *__identifier("??_7BfmeBaseVUQ@@6B@")[];
extern "C" void *__identifier("??_7?$CategoryModuleInfo@$04@FXParticleSystem@@6B@")[];
extern "C" void *__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")[];

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
	*(volatile unsigned int *)info = (unsigned int)__identifier("??_7BfmeBaseVUQ@@6B@");

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)__identifier("??_7?$CategoryModuleInfo@$04@FXParticleSystem@@6B@");
	*(volatile unsigned int *)this = (unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");
}

}
