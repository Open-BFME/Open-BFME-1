// cl: /O2
// Retail RVA 0x005DA0D0. Scalar destructor ILT 0x0000CD74 routes to the
// matched ConcreteModuleTemplate<QuadDraw ModuleTag> destructor at 0x005DA020.
void operator delete[](void *block);

namespace FXParticleSystem
{
extern const char QUAD_DRAW_MODULE_KEY[1];
extern const char QUAD_DRAW_MODULE_NAME[1];

class QuadDrawModule;
class QuadDrawModuleTemplate;
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

typedef ConcreteModuleTemplate<ModuleTag<6, QUAD_DRAW_MODULE_KEY,
    QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate,
    DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > QuadTemplate;

QuadTemplate *MakeQuadTemplateArray()
{
    return new QuadTemplate[2];
}

void DeleteQuadTemplateArray(QuadTemplate *array)
{
    delete[] array;
}
}
