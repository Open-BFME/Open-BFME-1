// cl: /O2
// Retail RVA 0x005DC780. Destructor ILT 0x0001D9EE routes directly to the
// matched LightningEmission specialization destructor at 0x005DC6A0.
namespace FXParticleSystem
{
extern const char LIGHTNING_EMISSION_MODULE_KEY[1];
extern const char LIGHTNING_EMISSION_MODULE_NAME[1];
class LightningEmissionModule;
class LightningEmissionModuleTemplate;
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
typedef ConcreteModuleTemplate<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY,
	LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule,
	LightningEmissionModuleTemplate, DefaultParticleModule<5>,
	DefaultParticleModuleTemplate<5> > > LightningTemplate;
LightningTemplate *MakeLightningTemplate() { return new LightningTemplate; }
void DeleteLightningTemplate(LightningTemplate *object) { delete object; }
}
