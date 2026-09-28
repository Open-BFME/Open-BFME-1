// cl: /DNDEBUG /MD /EHsc
// OrthoEmissionVelocityModuleTemplate empty triple-vtbl dtor at 0x005D6FC0.
// Retail 50B: this+8 / this+4 / this vtbl stores (DIR32-masked). The scalar
// destructor ILT 0x00046E11 routes directly to 0x005D6FC0 and the vector
// deleting destructor at 0x005D70F0 calls through the same ILT; landed
// neighbours (ctor 0x005D6F30, copy ctor 0x005D7000, operator= 0x005D7050)
// sit either side in the same TU family.

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
	*(volatile unsigned int *)info = 0x01073744;

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110f9cc;
	*(volatile unsigned int *)this = 0x01073758;
}

}
