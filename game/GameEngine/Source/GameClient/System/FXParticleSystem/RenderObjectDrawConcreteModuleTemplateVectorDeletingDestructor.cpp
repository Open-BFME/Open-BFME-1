// cl: /O2
// Retail RVA 0x005DF790. Destructor ILT 0x00016DBA routes directly to the
// matched RenderObjectDraw ConcreteModuleTemplate destructor. Element size 0x48.
void operator delete[](void *block);

namespace FXParticleSystem
{
extern const char RENDEROBJECT_DRAW_MODULE_KEY[1];
extern const char RENDEROBJECT_DRAW_MODULE_NAME[1];
class RenderObjectDrawModule;
class RenderObjectDrawModuleTemplate;
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
    unsigned char m_data[0x44];
};
typedef ConcreteModuleTemplate<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY,
    RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule,
    RenderObjectDrawModuleTemplate, DefaultParticleModule<6>,
    DefaultParticleModuleTemplate<6> > > RenderObjectDrawTemplate;
RenderObjectDrawTemplate *MakeRenderObjectDrawTemplateArray()
{
    return new RenderObjectDrawTemplate[2];
}
void DeleteRenderObjectDrawTemplateArray(RenderObjectDrawTemplate *array)
{
    delete[] array;
}
}
