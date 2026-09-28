// cl: /DNDEBUG /MD /EHsc
// PointEmissionVolumeModuleTemplate empty dual-vtbl dtor at 0x005D58F0.
// Retail 50B: this+8 / this+4 / this vtbl stores (DIR32-masked). Identity is
// proven by the two matched deleting-destructor callers: scalar ILT 0x00041F56
// routes to 0x005D58F0 and the vector deleting destructor at 0x005D59E0 calls
// through the same ILT; landed neighbours (ctor 0x005D58B0, copy ctor
// 0x005D5930, operator= 0x005D5980) sit either side in the same TU family.

namespace FXParticleSystem
{

class __declspec(novtable) PointEmissionVolumeModuleTemplate
{
public:
	virtual ~PointEmissionVolumeModuleTemplate();
};

// ??1PointEmissionVolumeModuleTemplate@FXParticleSystem@@UAE@XZ
PointEmissionVolumeModuleTemplate::~PointEmissionVolumeModuleTemplate()
{
	unsigned char *info = this ? (unsigned char *)this + 8 : 0;
	*(volatile unsigned int *)info = 0x01073744;

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110f9ac;
	*(volatile unsigned int *)this = 0x01073758;
}

}
