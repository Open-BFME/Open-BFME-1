// cl: /DNDEBUG /MD /EHsc
// LightningEmissionModuleTemplate empty triple-vtbl dtor at 0x005D6B60.
// Retail 50B: this+8 / this+4 / this vtbl stores (DIR32-masked). The scalar
// destructor ILT 0x0003612E routes directly to 0x005D6B60; the vector-deleting
// destructor family neighbour and landed ctor/copy/assign (0x005D6AD0,
// 0x005D6BA0, 0x005D6C00) sit either side in the same TU family.

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
	*(volatile unsigned int *)info = 0x01073744;

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110f9ac;
	*(volatile unsigned int *)this = 0x01073758;
}

}
