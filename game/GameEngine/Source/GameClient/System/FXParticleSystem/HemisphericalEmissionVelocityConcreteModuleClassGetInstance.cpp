// cl: /EHs-c-

// The public FX particle header intentionally keeps ConcreteModuleClass
// specializations empty: fx_particle_system.cpp builds a second FXPS_V mode
// with a virtual view.  This TU owns the actual HemisphericalEmissionVelocity
// singleton ABI only.  Its four data words are the retail object at
// 0x012F6B6C: table, the two source-pointer values, and the category-4
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

class HemisphericalEmissionVelocityModule;
class HemisphericalEmissionVelocityModuleTemplate;

extern const char HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY[1];
extern const char HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1],
	class Module, class ModuleTemplate, class ParticleModule,
	class ParticleModuleTemplate>
class ModuleTag;

template <class Tag>
class ConcreteModuleClass;

typedef ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY,
	HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME,
	HemisphericalEmissionVelocityModule,
	HemisphericalEmissionVelocityModuleTemplate,
	DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> >
	HemisphericalEmissionVelocityTag;

// Retail globals: +4 reads [0x012F6D40], +8 reads [0x012F6D44], and the
// category-4 chain head is [0x012F64F8].  These names are TU-local ABI
// declarations; their DIR32 relocations are checked against those operands.
extern void **hemisphericalEmissionVelocitySourceAt4;
extern void **hemisphericalEmissionVelocitySourceAt8;
extern ConcreteModuleClass<HemisphericalEmissionVelocityTag> *
	hemisphericalEmissionVelocityRegistryHead;
extern void *hemisphericalEmissionVelocityVtable[];

template <>
class ConcreteModuleClass<HemisphericalEmissionVelocityTag>
{
public:
	ConcreteModuleClass()
	{
		void *sourceAt8 = *hemisphericalEmissionVelocitySourceAt8;
		void *sourceAt4 = *hemisphericalEmissionVelocitySourceAt4;
		m_sourceAt8 = sourceAt8;
		m_sourceAt4 = sourceAt4;
		m_next = hemisphericalEmissionVelocityRegistryHead;
		hemisphericalEmissionVelocityRegistryHead = this;
		m_table = hemisphericalEmissionVelocityVtable;
	}

	~ConcreteModuleClass();
	static const ConcreteModuleClass<HemisphericalEmissionVelocityTag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<HemisphericalEmissionVelocityTag> &
ConcreteModuleClass<HemisphericalEmissionVelocityTag>::getInstance()
{
	static ConcreteModuleClass<HemisphericalEmissionVelocityTag> instance;
	return instance;
}

}
