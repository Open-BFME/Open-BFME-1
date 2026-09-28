// cl: /DNDEBUG /MD /EHsc
// CylindricalEmissionVelocityModuleTemplate empty triple-vtbl dtor at 0x005D78F0.
// Retail 50B: this+8 / this+4 / this vtbl stores (DIR32-masked). The scalar
// destructor ILT 0x0004099E routes directly to 0x005D78F0 and the vector
// deleting destructor at 0x005D7A10 calls through the same ILT; landed
// neighbours (ctor 0x005D7860, copy ctor 0x005D7930, operator= 0x005D7980)
// sit either side in the same TU family.

namespace FXParticleSystem
{

class __declspec(novtable) CylindricalEmissionVelocityModuleTemplate
{
public:
	virtual ~CylindricalEmissionVelocityModuleTemplate();
};

// ??1CylindricalEmissionVelocityModuleTemplate@FXParticleSystem@@UAE@XZ
CylindricalEmissionVelocityModuleTemplate::~CylindricalEmissionVelocityModuleTemplate()
{
	unsigned char *info = this ? (unsigned char *)this + 8 : 0;
	*(volatile unsigned int *)info = 0x01073744;

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110f9cc;
	*(volatile unsigned int *)this = 0x01073758;
}

}
