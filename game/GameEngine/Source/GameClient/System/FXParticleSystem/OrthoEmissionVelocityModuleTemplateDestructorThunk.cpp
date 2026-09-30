// cl: /DNDEBUG /MD /EHsc
// OrthoEmissionVelocityModuleTemplate empty triple-vtbl dtor at 0x005D6FC0.
// Retail 50B: this+8 / this+4 / this vtbl stores (DIR32-masked). The scalar
// destructor ILT 0x00046E11 routes directly to 0x005D6FC0 and the vector
// deleting destructor at 0x005D70F0 calls through the same ILT; landed
// neighbours (ctor 0x005D6F30, copy ctor 0x005D7000, operator= 0x005D7050)
// sit either side in the same TU family.

extern "C" void *bfmeVftSnapshotBase[4];
#pragma comment(linker, "/alternatename:_bfmeVftSnapshotBase=??_7BfmeBaseVUQ@@6B@")
extern "C" const void *bfmeVftModuleTemplate[];
#pragma comment(linker, "/alternatename:_bfmeVftModuleTemplate=??_7ModuleTemplate@FXParticleSystem@@6B@")
extern "C" const void *bfmeVftCategoryModuleInfo4[];
#pragma comment(linker, "/alternatename:_bfmeVftCategoryModuleInfo4=??_7?$CategoryModuleInfo@$03@FXParticleSystem@@6B@")

namespace FXParticleSystem
{

class __declspec(novtable) OrthoEmissionVelocityModuleTemplate
{
public:
	virtual ~OrthoEmissionVelocityModuleTemplate();
};

// ??1OrthoEmissionVelocityModuleTemplate@FXParticleSystem@@UAE@XZ
OrthoEmissionVelocityModuleTemplate::~OrthoEmissionVelocityModuleTemplate()
{
	unsigned char *info = this ? (unsigned char *)this + 8 : 0;
	*(volatile unsigned int *)info = (unsigned int)bfmeVftSnapshotBase;

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)bfmeVftCategoryModuleInfo4;
	*(volatile unsigned int *)this = (unsigned int)bfmeVftModuleTemplate;
}

}
