// cl: /DNDEBUG /MD /EHsc
// OutwardEmissionVelocityModuleTemplate empty triple-vtbl dtor at 0x005D7D00.
// Retail 50B: this+8 / this+4 / this vtbl stores (DIR32-masked). The scalar
// deleting destructor routes directly to 0x005D7D00 and the vector deleting
// destructor at 0x005D7E20 calls through the same ILT; landed neighbours
// (ctor 0x005D7C70, copy ctor 0x005D7D40, operator= 0x005D7D90) sit either side.

extern "C" const void *bfmeVftSnapshot[];
#pragma comment(linker, "/alternatename:_bfmeVftSnapshot=??_7Snapshot@@6B@")
extern "C" const void *bfmeVftCategoryModuleInfo4[];
#pragma comment(linker, "/alternatename:_bfmeVftCategoryModuleInfo4=??_7?$CategoryModuleInfo@$03@FXParticleSystem@@6B@")
extern "C" const void *bfmeVftModuleTemplate[];
#pragma comment(linker, "/alternatename:_bfmeVftModuleTemplate=??_7ModuleTemplate@FXParticleSystem@@6B@")

namespace FXParticleSystem
{

class __declspec(novtable) OutwardEmissionVelocityModuleTemplate
{
public:
	virtual ~OutwardEmissionVelocityModuleTemplate();
};

// ??1OutwardEmissionVelocityModuleTemplate@FXParticleSystem@@UAE@XZ
OutwardEmissionVelocityModuleTemplate::~OutwardEmissionVelocityModuleTemplate()
{
	unsigned char *info = this ? (unsigned char *)this + 8 : 0;
	*(volatile unsigned int *)info = (unsigned int)bfmeVftSnapshot;

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)bfmeVftCategoryModuleInfo4;
	*(volatile unsigned int *)this = (unsigned int)bfmeVftModuleTemplate;
}

}
