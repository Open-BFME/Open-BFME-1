// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SphericalEmissionVelocityModuleTemplate empty dual-vtbl dtor.
// Retail 50B: this+8 / this+4 / this vtbl stores (DIR32-masked).

// The three stores below write the vftables themselves, so each declaration
// spells its retail symbol exactly: __identifier emits the decorated name
// verbatim and the store then references the defining name, not a stand-in.
extern "C" void *__identifier("??_7BfmeBaseVUQ@@6B@")[4];
extern "C" const void *__identifier("??_7?$CategoryModuleInfo@$03@FXParticleSystem@@6B@")[];
extern "C" const void *__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")[];

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
	*(volatile unsigned int *)info = (unsigned int)__identifier("??_7BfmeBaseVUQ@@6B@");

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)__identifier("??_7?$CategoryModuleInfo@$03@FXParticleSystem@@6B@");
	*(volatile unsigned int *)this = (unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");
}

}
