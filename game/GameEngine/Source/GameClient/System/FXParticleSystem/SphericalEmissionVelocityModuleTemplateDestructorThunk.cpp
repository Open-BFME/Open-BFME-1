// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SphericalEmissionVelocityModuleTemplate empty dual-vtbl dtor.
// Retail 50B: this+8 / this+4 / this vtbl stores (DIR32-masked).

namespace FXParticleSystem
{

class __declspec(novtable) SphericalEmissionVelocityModuleTemplate
{
public:
	virtual ~SphericalEmissionVelocityModuleTemplate();
};

// ??1SphericalEmissionVelocityModuleTemplate@FXParticleSystem@@UAE@XZ
SphericalEmissionVelocityModuleTemplate::~SphericalEmissionVelocityModuleTemplate()
{
	unsigned char *info = this ? (unsigned char *)this + 8 : 0;
	*(volatile unsigned int *)info = 0x01073744;

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110f9cc;
	*(volatile unsigned int *)this = 0x01073758;
}

}
