// cl: /O2
// Retail RVA 0x005DB600. Destructor ILT 0x0000D59E routes directly to the
// matched RenderObjectUpdate specialization destructor at 0x005DB550.
namespace FXParticleSystem
{
extern const char RENDEROBJECT_UPDATE_MODULE_KEY[1];
extern const char RENDEROBJECT_UPDATE_MODULE_NAME[1];
class RenderObjectUpdateModule;
class RenderObjectUpdateModuleTemplate;
class RenderObjectParticleUpdateModule;
class RenderObjectParticleUpdateModuleTemplate;
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
typedef ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY,
    RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule,
    RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule,
    RenderObjectParticleUpdateModuleTemplate> > RenderObjectUpdateTemplate;
RenderObjectUpdateTemplate *MakeRenderObjectUpdateTemplate()
{
    return new RenderObjectUpdateTemplate;
}
void DeleteRenderObjectUpdateTemplate(RenderObjectUpdateTemplate *object)
{
    delete object;
}
}
