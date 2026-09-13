// cl: /O2
// Retail RVA 0x005DA220. Scalar destructor ILT 0x00032E2F routes to the
// matched ConcreteModuleTemplate<ButterflyDraw ModuleTag> destructor at 0x005DA170.
void operator delete[](void *block);

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

ButterflyTemplate *MakeButterflyTemplateArray()
{
    return new ButterflyTemplate[2];
}

void DeleteButterflyTemplateArray(ButterflyTemplate *array)
{
    delete[] array;
}
}
