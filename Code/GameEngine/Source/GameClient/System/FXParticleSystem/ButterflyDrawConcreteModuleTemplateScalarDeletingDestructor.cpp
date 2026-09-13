// cl: /O2
// Retail RVA 0x005DA1F0. Destructor ILT 0x00032E2F routes directly to the
// matched ButterflyDraw specialization destructor at 0x005DA170.
namespace FXParticleSystem
{
extern const char BUTTERFLY_DRAW_MODULE_KEY[1];
extern const char BUTTERFLY_DRAW_MODULE_NAME[1];
class ButterflyDrawModule;
class ButterflyDrawModuleTemplate;
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
    unsigned char m_data[8];
};
typedef ConcreteModuleTemplate<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY,
    BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate,
    DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > ButterflyTemplate;
ButterflyTemplate *MakeButterflyTemplate() { return new ButterflyTemplate; }
void DeleteButterflyTemplate(ButterflyTemplate *object) { delete object; }
}
