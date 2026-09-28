// cl: /DNDEBUG /MD /EHsc
// HemisphericalEmissionVelocityModuleTemplate empty triple-vtbl dtor at 0x005D7520.
// Retail 50B: this+8 / this+4 / this vtbl stores (DIR32-masked). The scalar
// deleting destructor routes directly to 0x005D7520 and the vector deleting
// destructor at 0x005D7600 calls through the same ILT; landed neighbours
// (ctor 0x005D74F0, copy ctor 0x005D7560, operator= 0x005D7590) sit either side.

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
	*(volatile unsigned int *)info = 0x01073744;

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110f9cc;
	*(volatile unsigned int *)this = 0x01073758;
}

}
