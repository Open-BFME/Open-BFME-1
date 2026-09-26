// cl: /EHs-c-

// The public FX particle header intentionally keeps ConcreteModuleClass
// specializations empty: fx_particle_system.cpp builds a second FXPS_V mode
// with a virtual view.  This TU owns the actual SphereEmissionVolume
// singleton ABI only.  Its four data words are the retail object at
// 0x012F6BFC: table, the two source-pointer values, and the category-5
// registry link.  The constructor and destructor symbols remain the
// independently matched definitions in fx_particle_system_bulk.cpp; this
// inline semantic view is needed only so MSVC7.1 materializes their body
// inside the guarded function-local static.

namespace FXParticleSystem
{

template <int N>
class DefaultParticleModule;

template <int N>
class DefaultParticleModuleTemplate;

class SphereEmissionVolumeModule;
class SphereEmissionVolumeModuleTemplate;

extern const char SPHERE_EMISSION_VOLUME_MODULE_KEY[1];
extern const char SPHERE_EMISSION_VOLUME_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1],
	class Module, class ModuleTemplate, class ParticleModule,
	class ParticleModuleTemplate>
class ModuleTag;

template <class Tag>
class ConcreteModuleClass;

typedef ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY,
	SPHERE_EMISSION_VOLUME_MODULE_NAME,
	SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate,
	DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> >
	SphereEmissionVolumeTag;

// Retail globals: +4 reads [0x012F6D70], +8 reads [0x012F6D74], and the
// category-5 chain head is [0x012F64FC].  These names are TU-local ABI
// declarations; their DIR32 relocations are checked against those operands.
extern void **sphereEmissionVolumeSourceAt4;
extern void **sphereEmissionVolumeSourceAt8;
extern ConcreteModuleClass<SphereEmissionVolumeTag> *
	sphereEmissionVolumeRegistryHead;
extern void *sphereEmissionVolumeVtable[];

template <>
class ConcreteModuleClass<SphereEmissionVolumeTag>
{
public:
	ConcreteModuleClass()
	{
		void *sourceAt8 = *sphereEmissionVolumeSourceAt8;
		void *sourceAt4 = *sphereEmissionVolumeSourceAt4;
		m_sourceAt8 = sourceAt8;
		m_sourceAt4 = sourceAt4;
		m_next = sphereEmissionVolumeRegistryHead;
		sphereEmissionVolumeRegistryHead = this;
		m_table = sphereEmissionVolumeVtable;
	}

	~ConcreteModuleClass();
	static const ConcreteModuleClass<SphereEmissionVolumeTag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<SphereEmissionVolumeTag> &
ConcreteModuleClass<SphereEmissionVolumeTag>::getInstance()
{
	static ConcreteModuleClass<SphereEmissionVolumeTag> instance;
	return instance;
}

}
