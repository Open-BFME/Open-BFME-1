// cl: /DNDEBUG /MD /EHsc
// PointEmissionVolumeModuleTemplate empty dual-vtbl dtor at 0x005D58F0.
// Retail 50B: this+8 / this+4 / this vtbl stores (DIR32-masked). Identity is
// proven by the two matched deleting-destructor callers: scalar ILT 0x00041F56
// routes to 0x005D58F0 and the vector deleting destructor at 0x005D59E0 calls
// through the same ILT; landed neighbours (ctor 0x005D58B0, copy ctor
// 0x005D5930, operator= 0x005D5980) sit either side in the same TU family.

// Retail's own vftable symbols, spelled with __identifier so the object
// references them directly instead of through a linker alternate name.
extern "C" const unsigned char __identifier("??_7Snapshot@@6B@")[];
extern "C" const unsigned char __identifier(
	"??_7?$CategoryModuleInfo@$04@FXParticleSystem@@6B@")[];
extern "C" const unsigned char __identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")[];

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
	*(volatile unsigned int *)info =
		(unsigned int)__identifier("??_7Snapshot@@6B@");

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base =
		(unsigned int)__identifier(
			"??_7?$CategoryModuleInfo@$04@FXParticleSystem@@6B@");
	*(volatile unsigned int *)this =
		(unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");
}

}
