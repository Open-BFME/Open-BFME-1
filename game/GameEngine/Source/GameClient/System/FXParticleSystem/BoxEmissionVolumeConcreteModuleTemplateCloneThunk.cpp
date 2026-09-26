// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: BoxEmissionVolume ConcreteModuleTemplate::clone

namespace FXParticleSystem
{
template <int N> class DefaultParticleModule {};
template <int N> class DefaultParticleModuleTemplate {};
class BoxEmissionVolumeModule {};
class BoxEmissionVolumeModuleTemplate {};

extern const char BOX_EMISSION_VOLUME_MODULE_KEY[1];
extern const char BOX_EMISSION_VOLUME_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1], class Module,
    class ModuleTemplate, class ParticleModule, class ParticleModuleTemplate>
class ModuleTag {};

typedef ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME,
    BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate,
    DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > BoxEmissionVolumeTag;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class BoxEmissionVolumeTemplateCopyCtorShim
{
public:
    void construct(const void *source);
};

extern "C" char BoxEmissionVolumeConcrete_vtbl0;
extern "C" char BoxEmissionVolumeConcrete_vtbl4;
extern "C" char BoxEmissionVolumeConcrete_vtbl8;

template <class Tag> class ConcreteModuleTemplate;

class BoxEmissionVolumeTemplateAllocation
{
public:
    __forceinline BoxEmissionVolumeTemplateAllocation(const void *source)
    {
        ((BoxEmissionVolumeTemplateCopyCtorShim *)this)->construct(source);
        *(void **)((char *)this + 0) = &BoxEmissionVolumeConcrete_vtbl0;
        *(void **)((char *)this + 4) = &BoxEmissionVolumeConcrete_vtbl4;
        *(void **)((char *)this + 8) = &BoxEmissionVolumeConcrete_vtbl8;
    }

private:
    unsigned char m_bytes[0x1c];
};

template <>
class ConcreteModuleTemplate<BoxEmissionVolumeTag>
{
public:
    virtual BoxEmissionVolumeModuleTemplate *clone() const;
};

BoxEmissionVolumeModuleTemplate *ConcreteModuleTemplate<BoxEmissionVolumeTag>::clone() const
{
    return (BoxEmissionVolumeModuleTemplate *)new BoxEmissionVolumeTemplateAllocation(this);
}

}
