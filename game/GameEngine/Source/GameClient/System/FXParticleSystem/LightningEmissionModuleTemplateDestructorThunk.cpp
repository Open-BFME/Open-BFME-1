// cl: /DNDEBUG /MD /EHsc
// LightningEmissionModuleTemplate empty triple-vtbl dtor at 0x005D6B60.
// Retail 50B: this+8 / this+4 / this vtbl stores (DIR32-masked). The scalar
// destructor ILT 0x0003612E routes directly to 0x005D6B60; the vector-deleting
// destructor family neighbour and landed ctor/copy/assign (0x005D6AD0,
// 0x005D6BA0, 0x005D6C00) sit either side in the same TU family.

extern "C" void *bfmeVftSnapshotBase[4];
#pragma comment(linker, "/alternatename:_bfmeVftSnapshotBase=??_7BfmeBaseVUQ@@6B@")
extern "C" const void *bfmeVftModuleTemplate[];
#pragma comment(linker, "/alternatename:_bfmeVftModuleTemplate=??_7ModuleTemplate@FXParticleSystem@@6B@")
extern "C" const void *bfmeVftCategoryModuleInfo5[];
#pragma comment(linker, "/alternatename:_bfmeVftCategoryModuleInfo5=??_7?$CategoryModuleInfo@$04@FXParticleSystem@@6B@")

namespace FXParticleSystem
{

class __declspec(novtable) LightningEmissionModuleTemplate
{
public:
	virtual ~LightningEmissionModuleTemplate();
};

// ??1LightningEmissionModuleTemplate@FXParticleSystem@@UAE@XZ
LightningEmissionModuleTemplate::~LightningEmissionModuleTemplate()
{
	unsigned char *info = this ? (unsigned char *)this + 8 : 0;
	*(volatile unsigned int *)info = (unsigned int)bfmeVftSnapshotBase;

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)bfmeVftCategoryModuleInfo5;
	*(volatile unsigned int *)this = (unsigned int)bfmeVftModuleTemplate;
}

}
