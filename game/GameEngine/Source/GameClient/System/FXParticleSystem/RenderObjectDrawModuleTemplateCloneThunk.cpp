// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

// Open-BFME5: RenderObjectDraw ConcreteModuleTemplate::clone

namespace FXParticleSystem
{
template <int N> class DefaultParticleModule {};
template <int N> class DefaultParticleModuleTemplate {};
class RenderObjectDrawModule {};
class RenderObjectDrawModuleTemplate {};
extern const char RENDEROBJECT_DRAW_MODULE_KEY[1];
extern const char RENDEROBJECT_DRAW_MODULE_NAME[1];
template <int Category, const char (&Key)[1], const char (&Name)[1], class Module,
    class ModuleTemplate, class ParticleModule, class ParticleModuleTemplate>
class ModuleTag {};
typedef ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME,
    RenderObjectDrawModule, RenderObjectDrawModuleTemplate,
    DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > RenderObjectDrawModuleTag;
void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);
class RenderObjectDrawTemplateCopyCtorShim
{
public:
    void construct(const void *source);
};
extern "C" char RenderObjectDrawConcrete_vtbl0;
extern "C" char RenderObjectDrawConcrete_vtbl4;
extern "C" char RenderObjectDrawConcrete_vtbl8;
class RenderObjectDrawTemplateAllocation
{
public:
    __forceinline RenderObjectDrawTemplateAllocation(const void *source)
    {
        ((RenderObjectDrawTemplateCopyCtorShim *)this)->construct(source);
        *(void **)((char *)this + 0) = &RenderObjectDrawConcrete_vtbl0;
        *(void **)((char *)this + 4) = &RenderObjectDrawConcrete_vtbl4;
        *(void **)((char *)this + 8) = &RenderObjectDrawConcrete_vtbl8;
    }
private:
    unsigned char m_bytes[0x48];
};
template <class Tag> class ConcreteModuleTemplate;
template <>
class ConcreteModuleTemplate<RenderObjectDrawModuleTag>
{
public:
    virtual RenderObjectDrawModuleTemplate *clone() const;
};
RenderObjectDrawModuleTemplate *ConcreteModuleTemplate<RenderObjectDrawModuleTag>::clone() const
{
    return (RenderObjectDrawModuleTemplate *)new RenderObjectDrawTemplateAllocation(this);
}
}
