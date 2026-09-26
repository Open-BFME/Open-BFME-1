// cl: /EHs-c-

// The public FX particle header intentionally keeps ConcreteModuleClass
// specializations empty: fx_particle_system.cpp builds a second FXPS_V mode
// with a virtual view.  This TU owns the actual SphericalEmissionVelocity
// singleton ABI only.  Its four data words are the retail object at
// 0x012F6B54: table, the two source-pointer values, and the category-4
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

class SphericalEmissionVelocityModule;
class SphericalEmissionVelocityModuleTemplate;

extern const char SPHERICAL_EMISSION_VELOCITY_MODULE_KEY[1];
extern const char SPHERICAL_EMISSION_VELOCITY_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1],
	class Module, class ModuleTemplate, class ParticleModule,
	class ParticleModuleTemplate>
class ModuleTag;

template <class Tag>
class ConcreteModuleClass;

typedef ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY,
	SPHERICAL_EMISSION_VELOCITY_MODULE_NAME,
	SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate,
	DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> >
	SphericalEmissionVelocityTag;

// Retail globals: +4 reads [0x012F6D38], +8 reads [0x012F6D3C], and the
// category-4 chain head is [0x012F64F8].  These names are TU-local ABI
// declarations; their DIR32 relocations are checked against those operands.
extern void **sphericalEmissionVelocitySourceAt4;
extern void **sphericalEmissionVelocitySourceAt8;
extern ConcreteModuleClass<SphericalEmissionVelocityTag> *
	sphericalEmissionVelocityRegistryHead;
extern void *sphericalEmissionVelocityVtable[];

template <>
class ConcreteModuleClass<SphericalEmissionVelocityTag>
{
public:
	ConcreteModuleClass()
	{
		void *sourceAt8 = *sphericalEmissionVelocitySourceAt8;
		void *sourceAt4 = *sphericalEmissionVelocitySourceAt4;
		m_sourceAt8 = sourceAt8;
		m_sourceAt4 = sourceAt4;
		m_next = sphericalEmissionVelocityRegistryHead;
		sphericalEmissionVelocityRegistryHead = this;
		m_table = sphericalEmissionVelocityVtable;
	}

	~ConcreteModuleClass();
	static const ConcreteModuleClass<SphericalEmissionVelocityTag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<SphericalEmissionVelocityTag> &
ConcreteModuleClass<SphericalEmissionVelocityTag>::getInstance()
{
	static ConcreteModuleClass<SphericalEmissionVelocityTag> instance;
	return instance;
}

}
