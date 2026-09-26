// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

// Open-BFME5: LifeEvent ConcreteModuleTemplate::clone

namespace FXParticleSystem
{
class LifeEventModule {};
class LifeEventModuleTemplate {};
class ParticleLifeEventModule {};
class ParticleLifeEventModuleTemplate {};
extern const char LIFE_EVENT_MODULE_KEY[1];
extern const char LIFE_EVENT_MODULE_NAME[1];
template <int Category, const char (&Key)[1], const char (&Name)[1], class Module,
    class ModuleTemplate, class ParticleModule, class ParticleModuleTemplate>
class ModuleTag {};
typedef ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME,
    LifeEventModule, LifeEventModuleTemplate,
    ParticleLifeEventModule, ParticleLifeEventModuleTemplate> LifeEventModuleTag;
void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);
class LifeEventTemplateCopyCtorShim
{
public:
    void construct(const void *source);
};
extern "C" char LifeEventConcrete_vtbl0;
extern "C" char LifeEventConcrete_vtbl4;
extern "C" char LifeEventConcrete_vtbl12;
class LifeEventTemplateAllocation
{
public:
    __forceinline LifeEventTemplateAllocation(const void *source)
    {
        ((LifeEventTemplateCopyCtorShim *)this)->construct(source);
        *(void **)((char *)this + 0) = &LifeEventConcrete_vtbl0;
        *(void **)((char *)this + 4) = &LifeEventConcrete_vtbl4;
        *(void **)((char *)this + 12) = &LifeEventConcrete_vtbl12;
    }
private:
    unsigned char m_bytes[0x24];
};
template <class Tag> class ConcreteModuleTemplate;
template <>
class ConcreteModuleTemplate<LifeEventModuleTag>
{
public:
    virtual LifeEventModuleTemplate *clone() const;
};
LifeEventModuleTemplate *ConcreteModuleTemplate<LifeEventModuleTag>::clone() const
{
    return (LifeEventModuleTemplate *)new LifeEventTemplateAllocation(this);
}
}
