// cl: /O2
// Retail RVA 0x005DBC20. Destructor ILT 0x00044E2C routes directly to the
// matched CylindricalEmissionVelocity specialization destructor at 0x005DBB50.
namespace FXParticleSystem
{
extern const char CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY[1];
extern const char CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME[1];
class CylindricalEmissionVelocityModule;
class CylindricalEmissionVelocityModuleTemplate;
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
    unsigned char m_data[0x20];
};
typedef ConcreteModuleTemplate<ModuleTag<4,
    CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY,
    CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME,
    CylindricalEmissionVelocityModule,
    CylindricalEmissionVelocityModuleTemplate,
    DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > CylindricalTemplate;
CylindricalTemplate *MakeCylindricalTemplate() { return new CylindricalTemplate; }
void DeleteCylindricalTemplate(CylindricalTemplate *object) { delete object; }
}
