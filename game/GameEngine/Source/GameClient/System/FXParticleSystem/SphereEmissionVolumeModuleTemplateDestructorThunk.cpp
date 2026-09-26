// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SphereEmissionVolumeModuleTemplate empty dual-vtbl dtor.
// Retail 50B: this+8 / this+4 / this vtbl stores (DIR32-masked).

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
	*(volatile unsigned int *)info = 0x01073744;

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110f9ac;
	*(volatile unsigned int *)this = 0x01073758;
}

}
