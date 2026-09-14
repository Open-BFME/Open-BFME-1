// cl: /O2
// Retail RVA 0x005DBDC0. Destructor ILT 0x000482ED routes directly to the
// matched OutwardEmissionVelocity specialization destructor at 0x005DBCF0.
namespace FXParticleSystem
{
extern const char OUTWARD_EMISSION_VELOCITY_MODULE_KEY[1];
extern const char OUTWARD_EMISSION_VELOCITY_MODULE_NAME[1];
class OutwardEmissionVelocityModule;
class OutwardEmissionVelocityModuleTemplate;
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
    OUTWARD_EMISSION_VELOCITY_MODULE_KEY,
    OUTWARD_EMISSION_VELOCITY_MODULE_NAME,
    OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate,
    DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > OutwardTemplate;
OutwardTemplate *MakeOutwardTemplate() { return new OutwardTemplate; }
void DeleteOutwardTemplate(OutwardTemplate *object) { delete object; }
}
