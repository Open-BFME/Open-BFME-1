// cl: /O2
// Retail RVA 0x005DC420. Destructor ILT 0x00048B53 routes directly to the
// matched SphereEmissionVolume specialization destructor at 0x005DC370.
namespace FXParticleSystem
{
extern const char SPHERE_EMISSION_VOLUME_MODULE_KEY[1];
extern const char SPHERE_EMISSION_VOLUME_MODULE_NAME[1];
class SphereEmissionVolumeModule;
class SphereEmissionVolumeModuleTemplate;
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
	unsigned char m_data[0x10];
};
typedef ConcreteModuleTemplate<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY,
	SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule,
	SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>,
	DefaultParticleModuleTemplate<5> > > SphereTemplate;
SphereTemplate *MakeSphereTemplate() { return new SphereTemplate; }
void DeleteSphereTemplate(SphereTemplate *object) { delete object; }
}
