// cl: /O2
// Retail RVA 0x005DB9D0. The scalar and vector deleting destructors both route
// to this specialization; its category vtable is installed at +0x04.
namespace FXParticleSystem
{
extern const char HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY[1];
extern const char HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME[1];
class HemisphericalEmissionVelocityModule;
class HemisphericalEmissionVelocityModuleTemplate;
template<int Category> class DefaultParticleModule;
template<int Category> class DefaultParticleModuleTemplate;
template<int Category, const char (&Key)[1], const char (&Name)[1], class Module,
    class ModuleTemplate, class DefaultModule, class DefaultModuleTemplate>
class ModuleTag;
template<class Tag>
class __declspec(novtable) ConcreteModuleTemplate
{
public:
    virtual ~ConcreteModuleTemplate();
private:
    unsigned char m_data[0x14];
};

// ??1?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVHemisphericalEmissionVelocityModule@2@VHemisphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UAE@XZ
// The matched scalar and vector deleting destructors route to this body.
ConcreteModuleTemplate<ModuleTag<4,
    HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY,
    HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME,
    HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate,
    DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::~ConcreteModuleTemplate()
{
	unsigned char *info = this ? (unsigned char *)this + 8 : 0;
	*(volatile unsigned int *)info = 0x01073744;

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110f9cc;
	*(volatile unsigned int *)this = 0x01073758;
}
}
