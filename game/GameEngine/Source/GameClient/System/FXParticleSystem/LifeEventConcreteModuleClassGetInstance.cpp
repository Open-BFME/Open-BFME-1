// cl: /EHs-c-

// The public FX particle header intentionally keeps ConcreteModuleClass
// specializations empty: fx_particle_system.cpp builds a second FXPS_V mode
// with a virtual view.  This TU owns the actual LifeEvent singleton ABI only.
// Its four data words are the retail object at 0x012F6AF4: table, the two
// source-pointer values, and the category-8 registry link.  The constructor
// and destructor symbols remain the independently matched definitions in
// fx_particle_system_bulk.cpp; this inline semantic view is needed only so
// MSVC7.1 materializes their body inside the guarded function-local static.

namespace FXParticleSystem
{

class LifeEventModule;
class LifeEventModuleTemplate;
class ParticleLifeEventModule;
class ParticleLifeEventModuleTemplate;

extern const char LIFE_EVENT_MODULE_KEY[1];
extern const char LIFE_EVENT_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1],
	class Module, class ModuleTemplate, class ParticleModule,
	class ParticleModuleTemplate>
class ModuleTag;

template <class Tag>
class ConcreteModuleClass;

typedef ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME,
	LifeEventModule, LifeEventModuleTemplate,
	ParticleLifeEventModule, ParticleLifeEventModuleTemplate> LifeEventTag;

// Retail globals: +4 reads [0x012F6D18], +8 reads [0x012F6D1C], and the
// category-8 chain head is [0x012F6508].  These names are TU-local ABI
// declarations; their DIR32 relocations are checked against those operands.
extern void **lifeEventSourceAt4;
extern void **lifeEventSourceAt8;
extern ConcreteModuleClass<LifeEventTag> *lifeEventRegistryHead;
extern void *lifeEventVtable[];

template <>
class ConcreteModuleClass<LifeEventTag>
{
public:
	ConcreteModuleClass()
	{
		void *sourceAt8 = *lifeEventSourceAt8;
		void *sourceAt4 = *lifeEventSourceAt4;
		m_sourceAt8 = sourceAt8;
		m_sourceAt4 = sourceAt4;
		m_next = lifeEventRegistryHead;
		lifeEventRegistryHead = this;
		m_table = lifeEventVtable;
	}

	~ConcreteModuleClass();
	static const ConcreteModuleClass<LifeEventTag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<LifeEventTag> &
ConcreteModuleClass<LifeEventTag>::getInstance()
{
	static ConcreteModuleClass<LifeEventTag> instance;
	return instance;
}

}
