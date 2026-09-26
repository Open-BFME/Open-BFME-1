// cl: /O2
// Retail RVA 0x005DA3E0. Scalar destructor ILT 0x00044C15 routes to the
// matched ConcreteModuleTemplate<LightningDraw ModuleTag> destructor at 0x005DA300.
void operator delete[](void *block);

namespace FXParticleSystem
{
extern const char LIGHTNING_DRAW_MODULE_KEY[1];
extern const char LIGHTNING_DRAW_MODULE_NAME[1];

class LightningDrawModule;
class LightningDrawModuleTemplate;
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
    unsigned char m_data[0x34];
};

typedef ConcreteModuleTemplate<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY,
    LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate,
    DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > LightningTemplate;

LightningTemplate *MakeLightningTemplateArray()
{
    return new LightningTemplate[2];
}

void DeleteLightningTemplateArray(LightningTemplate *array)
{
    delete[] array;
}
}
