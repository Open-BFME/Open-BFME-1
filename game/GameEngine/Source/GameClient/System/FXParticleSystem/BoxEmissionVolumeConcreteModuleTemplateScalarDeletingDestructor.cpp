// cl: /O2
// Retail RVA 0x005DC290. Destructor ILT 0x00001F96 routes directly to the
// matched BoxEmissionVolume specialization destructor at 0x005DC1E0.
namespace FXParticleSystem
{
extern const char BOX_EMISSION_VOLUME_MODULE_KEY[1];
extern const char BOX_EMISSION_VOLUME_MODULE_NAME[1];
class BoxEmissionVolumeModule;
class BoxEmissionVolumeModuleTemplate;
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
    unsigned char m_data[0x18];
};

typedef ConcreteModuleTemplate<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY,
    BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule,
    BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>,
    DefaultParticleModuleTemplate<5> > > BoxTemplate;

BoxTemplate *MakeBoxTemplate() { return new BoxTemplate; }
void DeleteBoxTemplate(BoxTemplate *object) { delete object; }
}
