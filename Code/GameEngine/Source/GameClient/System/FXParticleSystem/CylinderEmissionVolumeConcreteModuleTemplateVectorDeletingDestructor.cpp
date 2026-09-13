// cl: /O2
// Retail RVA 0x005DC600. Scalar destructor ILT 0x00001D16 routes to the
// matched CylinderEmissionVolume specialization destructor at 0x005DC510.
void operator delete[](void *block);

namespace FXParticleSystem
{
extern const char CYLINDER_EMISSION_VOLUME_MODULE_KEY[1];
extern const char CYLINDER_EMISSION_VOLUME_MODULE_NAME[1];
class CylinderEmissionVolumeModule;
class CylinderEmissionVolumeModuleTemplate;
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
    unsigned char m_data[0x20];
};
typedef ConcreteModuleTemplate<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY,
    CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule,
    CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>,
    DefaultParticleModuleTemplate<5> > > CylinderTemplate;
CylinderTemplate *MakeCylinderTemplateArray() { return new CylinderTemplate[2]; }
void DeleteCylinderTemplateArray(CylinderTemplate *array) { delete[] array; }
}
