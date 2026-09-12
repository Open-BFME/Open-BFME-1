// cl: /O2
// Retail RVA 0x005D9F80. Scalar destructor ILT 0x0000CAB8 routes to the
// matched ConcreteModuleTemplate<StreakDraw ModuleTag> destructor at 0x005D9ED0.
void operator delete[](void *block);

namespace FXParticleSystem
{
extern const char STREAK_DRAW_MODULE_KEY[1];
extern const char STREAK_DRAW_MODULE_NAME[1];

class StreakDrawModule;
class StreakDrawModuleTemplate;
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

typedef ConcreteModuleTemplate<ModuleTag<6, STREAK_DRAW_MODULE_KEY,
    STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate,
    DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > StreakTemplate;

StreakTemplate *MakeStreakTemplateArray()
{
    return new StreakTemplate[2];
}

void DeleteStreakTemplateArray(StreakTemplate *array)
{
    delete[] array;
}
}
