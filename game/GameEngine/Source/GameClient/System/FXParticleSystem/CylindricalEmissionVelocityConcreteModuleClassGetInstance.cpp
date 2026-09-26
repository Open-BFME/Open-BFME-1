// cl: /EHs-c-

// The public FX particle header intentionally keeps ConcreteModuleClass
// specializations empty: fx_particle_system.cpp builds a second FXPS_V mode
// with a virtual view.  This TU owns the actual CylindricalEmissionVelocity
// singleton ABI only.  Its four data words are the retail object at
// 0x012F6B84: table, the two source-pointer values, and the category-4
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

class CylindricalEmissionVelocityModule;
class CylindricalEmissionVelocityModuleTemplate;

extern const char CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY[1];
extern const char CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1],
	class Module, class ModuleTemplate, class ParticleModule,
	class ParticleModuleTemplate>
class ModuleTag;

template <class Tag>
class ConcreteModuleClass;

typedef ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY,
	CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME,
	CylindricalEmissionVelocityModule,
	CylindricalEmissionVelocityModuleTemplate,
	DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> >
	CylindricalEmissionVelocityTag;

// Retail globals: +4 reads [0x012F6D48], +8 reads [0x012F6D4C], and the
// category-4 chain head is [0x012F64F8].  These names are TU-local ABI
// declarations; their DIR32 relocations are checked against those operands.
extern void **cylindricalEmissionVelocitySourceAt4;
extern void **cylindricalEmissionVelocitySourceAt8;
extern ConcreteModuleClass<CylindricalEmissionVelocityTag> *
	cylindricalEmissionVelocityRegistryHead;
extern void *cylindricalEmissionVelocityVtable[];

template <>
class ConcreteModuleClass<CylindricalEmissionVelocityTag>
{
public:
	ConcreteModuleClass()
	{
		void *sourceAt8 = *cylindricalEmissionVelocitySourceAt8;
		void *sourceAt4 = *cylindricalEmissionVelocitySourceAt4;
		m_sourceAt8 = sourceAt8;
		m_sourceAt4 = sourceAt4;
		m_next = cylindricalEmissionVelocityRegistryHead;
		cylindricalEmissionVelocityRegistryHead = this;
		m_table = cylindricalEmissionVelocityVtable;
	}

	~ConcreteModuleClass();
	static const ConcreteModuleClass<CylindricalEmissionVelocityTag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<CylindricalEmissionVelocityTag> &
ConcreteModuleClass<CylindricalEmissionVelocityTag>::getInstance()
{
	static ConcreteModuleClass<CylindricalEmissionVelocityTag> instance;
	return instance;
}

}
