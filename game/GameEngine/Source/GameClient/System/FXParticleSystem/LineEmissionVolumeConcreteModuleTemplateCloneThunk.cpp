// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: LineEmissionVolume ConcreteModuleTemplate::clone

namespace FXParticleSystem
{
template <int N> class DefaultParticleModule {};
template <int N> class DefaultParticleModuleTemplate {};
class LineEmissionVolumeModule {};
class LineEmissionVolumeModuleTemplate {};
extern const char LINE_EMISSION_VOLUME_MODULE_KEY[1];
extern const char LINE_EMISSION_VOLUME_MODULE_NAME[1];
template <int Category, const char (&Key)[1], const char (&Name)[1], class Module,
    class ModuleTemplate, class ParticleModule, class ParticleModuleTemplate>
class ModuleTag {};
typedef ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME,
    LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate,
    DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > LineEmissionVolumeTag;
void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);
class LineEmissionVolumeTemplateCopyCtorShim
{
public:
    void construct(const void *source);
};
extern "C" char LineEmissionVolumeConcrete_vtbl0;
extern "C" char LineEmissionVolumeConcrete_vtbl4;
extern "C" char LineEmissionVolumeConcrete_vtbl8;
class LineEmissionVolumeTemplateAllocation
{
public:
    __forceinline LineEmissionVolumeTemplateAllocation(const void *source)
    {
        ((LineEmissionVolumeTemplateCopyCtorShim *)this)->construct(source);
        *(void **)((char *)this + 0) = &LineEmissionVolumeConcrete_vtbl0;
        *(void **)((char *)this + 4) = &LineEmissionVolumeConcrete_vtbl4;
        *(void **)((char *)this + 8) = &LineEmissionVolumeConcrete_vtbl8;
    }
private:
    unsigned char m_bytes[0x28];
};
template <class Tag> class ConcreteModuleTemplate;
template <>
class ConcreteModuleTemplate<LineEmissionVolumeTag>
{
public:
    virtual LineEmissionVolumeModuleTemplate *clone() const;
};
LineEmissionVolumeModuleTemplate *ConcreteModuleTemplate<LineEmissionVolumeTag>::clone() const
{
    return (LineEmissionVolumeModuleTemplate *)new LineEmissionVolumeTemplateAllocation(this);
}
}
