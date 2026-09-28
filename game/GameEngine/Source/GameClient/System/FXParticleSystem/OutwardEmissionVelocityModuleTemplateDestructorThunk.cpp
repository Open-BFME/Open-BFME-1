// cl: /DNDEBUG /MD /EHsc
// OutwardEmissionVelocityModuleTemplate empty triple-vtbl dtor at 0x005D7D00.
// Retail 50B: this+8 / this+4 / this vtbl stores (DIR32-masked). The scalar
// deleting destructor routes directly to 0x005D7D00 and the vector deleting
// destructor at 0x005D7E20 calls through the same ILT; landed neighbours
// (ctor 0x005D7C70, copy ctor 0x005D7D40, operator= 0x005D7D90) sit either side.

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
	*(volatile unsigned int *)info = 0x01073744;

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110f9cc;
	*(volatile unsigned int *)this = 0x01073758;
}

}
