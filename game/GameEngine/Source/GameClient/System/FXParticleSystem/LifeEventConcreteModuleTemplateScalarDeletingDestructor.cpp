// cl: /O2
// Retail RVA 0x005E1E70. Destructor ILT 0x0003DAAA routes directly to the
// matched LifeEvent ConcreteModuleTemplate destructor.
namespace FXParticleSystem
{
extern const char LIFE_EVENT_MODULE_KEY[1];
extern const char LIFE_EVENT_MODULE_NAME[1];
class LifeEventModule;
class LifeEventModuleTemplate;
class ParticleLifeEventModule;
class ParticleLifeEventModuleTemplate;
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
typedef ConcreteModuleTemplate<ModuleTag<8, LIFE_EVENT_MODULE_KEY,
    LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate,
    ParticleLifeEventModule, ParticleLifeEventModuleTemplate> > LifeEventTemplate;
LifeEventTemplate *MakeLifeEventTemplate()
{
    return new LifeEventTemplate;
}
void DeleteLifeEventTemplate(LifeEventTemplate *object)
{
    delete object;
}
}
