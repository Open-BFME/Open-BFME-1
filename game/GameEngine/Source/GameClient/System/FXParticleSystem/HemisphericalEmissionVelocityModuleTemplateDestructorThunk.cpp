// cl: /DNDEBUG /MD /EHsc
// HemisphericalEmissionVelocityModuleTemplate empty triple-vtbl dtor at 0x005D7520.
// Retail 50B: this+8 / this+4 / this vtbl stores (DIR32-masked). The scalar
// deleting destructor routes directly to 0x005D7520 and the vector deleting
// destructor at 0x005D7600 calls through the same ILT; landed neighbours
// (ctor 0x005D74F0, copy ctor 0x005D7560, operator= 0x005D7590) sit either side.

// The three stamped vptrs are retail vftables. MSVC's __identifier lets us name
// the decorated symbols directly, so no linker stand-in alias is needed.
// They stay arrays: the decay to an address is what lets cl fold each store
// down to the `mov dword ptr [reg], imm32` form retail used.
extern "C" const void *__identifier("??_7BfmeBaseVUQ@@6B@")[];
#define bfmeVftSnapshotBase __identifier("??_7BfmeBaseVUQ@@6B@")
extern "C" const void *__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")[];
#define bfmeVftModuleTemplate __identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")
extern "C" const void *__identifier("??_7?$CategoryModuleInfo@$03@FXParticleSystem@@6B@")[];
#define bfmeVftCategoryModuleInfo4 __identifier("??_7?$CategoryModuleInfo@$03@FXParticleSystem@@6B@")

namespace FXParticleSystem
{

class __declspec(novtable) HemisphericalEmissionVelocityModuleTemplate
{
public:
	virtual ~HemisphericalEmissionVelocityModuleTemplate();
};

// ??1HemisphericalEmissionVelocityModuleTemplate@FXParticleSystem@@UAE@XZ
HemisphericalEmissionVelocityModuleTemplate::~HemisphericalEmissionVelocityModuleTemplate()
{
	unsigned char *info = this ? (unsigned char *)this + 8 : 0;
	*(volatile unsigned int *)info = (unsigned int)bfmeVftSnapshotBase;

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)bfmeVftCategoryModuleInfo4;
	*(volatile unsigned int *)this = (unsigned int)bfmeVftModuleTemplate;
}

}
