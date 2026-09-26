// cl: /EHs-c-

// The public FX particle header intentionally keeps ConcreteModuleClass
// specializations empty: fx_particle_system.cpp builds a second FXPS_V mode
// with a virtual view.  This TU owns the actual OutwardEmissionVelocity
// singleton ABI only.  Its four data words are the retail object at
// 0x012F6B9C: table, the two source-pointer values, and the category-4
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

class OutwardEmissionVelocityModule;
class OutwardEmissionVelocityModuleTemplate;

extern const char OUTWARD_EMISSION_VELOCITY_MODULE_KEY[1];
extern const char OUTWARD_EMISSION_VELOCITY_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1],
	class Module, class ModuleTemplate, class ParticleModule,
	class ParticleModuleTemplate>
class ModuleTag;

template <class Tag>
class ConcreteModuleClass;

typedef ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY,
	OUTWARD_EMISSION_VELOCITY_MODULE_NAME,
	OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate,
	DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> >
	OutwardEmissionVelocityTag;

// Retail globals: +4 reads [0x012F6D50], +8 reads [0x012F6D54], and the
// category-4 chain head is [0x012F64F8].  These names are TU-local ABI
// declarations; their DIR32 relocations are checked against those operands.
extern void **outwardEmissionVelocitySourceAt4;
extern void **outwardEmissionVelocitySourceAt8;
extern ConcreteModuleClass<OutwardEmissionVelocityTag> *
	outwardEmissionVelocityRegistryHead;
extern void *outwardEmissionVelocityVtable[];

template <>
class ConcreteModuleClass<OutwardEmissionVelocityTag>
{
public:
	ConcreteModuleClass()
	{
		void *sourceAt8 = *outwardEmissionVelocitySourceAt8;
		void *sourceAt4 = *outwardEmissionVelocitySourceAt4;
		m_sourceAt8 = sourceAt8;
		m_sourceAt4 = sourceAt4;
		m_next = outwardEmissionVelocityRegistryHead;
		outwardEmissionVelocityRegistryHead = this;
		m_table = outwardEmissionVelocityVtable;
	}

	~ConcreteModuleClass();
	static const ConcreteModuleClass<OutwardEmissionVelocityTag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<OutwardEmissionVelocityTag> &
ConcreteModuleClass<OutwardEmissionVelocityTag>::getInstance()
{
	static ConcreteModuleClass<OutwardEmissionVelocityTag> instance;
	return instance;
}

}
