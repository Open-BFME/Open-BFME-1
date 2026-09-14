// cl: /O2
// Retail RVA 0x005DB900. Destructor ILT 0x0003B8DB routes directly to the
// matched SphericalEmissionVelocity specialization destructor at 0x005DB850.
namespace FXParticleSystem
{
extern const char SPHERICAL_EMISSION_VELOCITY_MODULE_KEY[1];
extern const char SPHERICAL_EMISSION_VELOCITY_MODULE_NAME[1];
class SphericalEmissionVelocityModule;
class SphericalEmissionVelocityModuleTemplate;
template<int Category> class DefaultParticleModule;
template<int Category> class DefaultParticleModuleTemplate;
template<int Category, const char (&Key)[1], const char (&Name)[1], class Module,
    class ModuleTemplate, class DefaultModule, class DefaultModuleTemplate>
class ModuleTag;
template<class Tag> class ConcreteModuleTemplate
{
public:
    virtual ~ConcreteModuleTemplate();
private:
    unsigned char m_data[0x14];
};
typedef ConcreteModuleTemplate<ModuleTag<4,
    SPHERICAL_EMISSION_VELOCITY_MODULE_KEY,
    SPHERICAL_EMISSION_VELOCITY_MODULE_NAME,
    SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate,
    DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > SphericalTemplate;
SphericalTemplate *MakeSphericalTemplate() { return new SphericalTemplate; }
void DeleteSphericalTemplate(SphericalTemplate *object) { delete object; }
}
