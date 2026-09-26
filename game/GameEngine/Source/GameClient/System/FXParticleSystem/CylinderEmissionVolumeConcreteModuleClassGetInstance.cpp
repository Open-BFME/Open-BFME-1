// cl: /EHs-c-

// The public FX particle header intentionally keeps ConcreteModuleClass
// specializations empty: fx_particle_system.cpp builds a second FXPS_V mode
// with a virtual view.  This TU owns the actual CylinderEmissionVolume
// singleton ABI only.  Its four data words are the retail object at
// 0x012F6C14: table, the two source-pointer values, and the category-5
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

class CylinderEmissionVolumeModule;
class CylinderEmissionVolumeModuleTemplate;

extern const char CYLINDER_EMISSION_VOLUME_MODULE_KEY[1];
extern const char CYLINDER_EMISSION_VOLUME_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1],
	class Module, class ModuleTemplate, class ParticleModule,
	class ParticleModuleTemplate>
class ModuleTag;

template <class Tag>
class ConcreteModuleClass;

typedef ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY,
	CYLINDER_EMISSION_VOLUME_MODULE_NAME,
	CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate,
	DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> >
	CylinderEmissionVolumeTag;

// Retail globals: +4 reads [0x012F6D78], +8 reads [0x012F6D7C], and the
// category-5 chain head is [0x012F64FC].  These names are TU-local ABI
// declarations; their DIR32 relocations are checked against those operands.
extern void **cylinderEmissionVolumeSourceAt4;
extern void **cylinderEmissionVolumeSourceAt8;
extern ConcreteModuleClass<CylinderEmissionVolumeTag> *
	cylinderEmissionVolumeRegistryHead;
extern void *cylinderEmissionVolumeVtable[];

template <>
class ConcreteModuleClass<CylinderEmissionVolumeTag>
{
public:
	ConcreteModuleClass()
	{
		void *sourceAt8 = *cylinderEmissionVolumeSourceAt8;
		void *sourceAt4 = *cylinderEmissionVolumeSourceAt4;
		m_sourceAt8 = sourceAt8;
		m_sourceAt4 = sourceAt4;
		m_next = cylinderEmissionVolumeRegistryHead;
		cylinderEmissionVolumeRegistryHead = this;
		m_table = cylinderEmissionVolumeVtable;
	}

	~ConcreteModuleClass();
	static const ConcreteModuleClass<CylinderEmissionVolumeTag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<CylinderEmissionVolumeTag> &
ConcreteModuleClass<CylinderEmissionVolumeTag>::getInstance()
{
	static ConcreteModuleClass<CylinderEmissionVolumeTag> instance;
	return instance;
}

}
