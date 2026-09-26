// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: CylinderEmissionVolume ConcreteModuleTemplate::clone

namespace FXParticleSystem
{
template <int N> class DefaultParticleModule {};
template <int N> class DefaultParticleModuleTemplate {};
class CylinderEmissionVolumeModule {};
class CylinderEmissionVolumeModuleTemplate {};
extern const char CYLINDER_EMISSION_VOLUME_MODULE_KEY[1];
extern const char CYLINDER_EMISSION_VOLUME_MODULE_NAME[1];
template <int Category, const char (&Key)[1], const char (&Name)[1], class Module,
    class ModuleTemplate, class ParticleModule, class ParticleModuleTemplate>
class ModuleTag {};
typedef ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME,
    CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate,
    DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > CylinderEmissionVolumeTag;
void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);
class CylinderEmissionVolumeTemplateCopyCtorShim
{
public:
    void construct(const void *source);
};
extern "C" char CylinderEmissionVolumeConcrete_vtbl0;
extern "C" char CylinderEmissionVolumeConcrete_vtbl4;
extern "C" char CylinderEmissionVolumeConcrete_vtbl8;
class CylinderEmissionVolumeTemplateAllocation
{
public:
    __forceinline CylinderEmissionVolumeTemplateAllocation(const void *source)
    {
        ((CylinderEmissionVolumeTemplateCopyCtorShim *)this)->construct(source);
        *(void **)((char *)this + 0) = &CylinderEmissionVolumeConcrete_vtbl0;
        *(void **)((char *)this + 4) = &CylinderEmissionVolumeConcrete_vtbl4;
        *(void **)((char *)this + 8) = &CylinderEmissionVolumeConcrete_vtbl8;
    }
private:
    unsigned char m_bytes[0x24];
};
template <class Tag> class ConcreteModuleTemplate;
template <>
class ConcreteModuleTemplate<CylinderEmissionVolumeTag>
{
public:
    virtual CylinderEmissionVolumeModuleTemplate *clone() const;
};
CylinderEmissionVolumeModuleTemplate *ConcreteModuleTemplate<CylinderEmissionVolumeTag>::clone() const
{
    return (CylinderEmissionVolumeModuleTemplate *)new CylinderEmissionVolumeTemplateAllocation(this);
}
}
