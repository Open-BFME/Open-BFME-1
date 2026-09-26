// cl: /EHs-c-

// The public FX particle header intentionally keeps ConcreteModuleClass
// specializations empty: fx_particle_system.cpp builds a second FXPS_V mode
// with a virtual view.  This TU owns the actual ButterflyDraw singleton ABI
// only.  Its four data words are the retail object at 0x012F69BC: table, the
// two source-pointer values, and the category-6 registry link.  The
// constructor and destructor symbols remain the independently matched
// definitions in fx_particle_system_bulk.cpp; this inline semantic view is
// needed only so MSVC7.1 materializes their body inside the guarded
// function-local static.

namespace FXParticleSystem
{

template <int N>
class DefaultParticleModule;

template <int N>
class DefaultParticleModuleTemplate;

class ButterflyDrawModule;
class ButterflyDrawModuleTemplate;

extern const char BUTTERFLY_DRAW_MODULE_KEY[1];
extern const char BUTTERFLY_DRAW_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1],
	class Module, class ModuleTemplate, class ParticleModule,
	class ParticleModuleTemplate>
class ModuleTag;

template <class Tag>
class ConcreteModuleClass;

typedef ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME,
	ButterflyDrawModule, ButterflyDrawModuleTemplate,
	DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > ButterflyDrawTag;

// Retail globals: +4 reads [0x012F6CB0], +8 reads [0x012F6CB4], and the
// category-6 chain head is [0x012F6500].  These names are TU-local ABI
// declarations; their DIR32 relocations are checked against those operands.
extern void **butterflyDrawSourceAt4;
extern void **butterflyDrawSourceAt8;
extern ConcreteModuleClass<ButterflyDrawTag> *butterflyDrawRegistryHead;
extern void *butterflyDrawVtable[];

template <>
class ConcreteModuleClass<ButterflyDrawTag>
{
public:
	ConcreteModuleClass()
	{
		void *sourceAt8 = *butterflyDrawSourceAt8;
		void *sourceAt4 = *butterflyDrawSourceAt4;
		m_sourceAt8 = sourceAt8;
		m_sourceAt4 = sourceAt4;
		m_next = butterflyDrawRegistryHead;
		butterflyDrawRegistryHead = this;
		m_table = butterflyDrawVtable;
	}

	~ConcreteModuleClass();
	static const ConcreteModuleClass<ButterflyDrawTag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<ButterflyDrawTag> &
ConcreteModuleClass<ButterflyDrawTag>::getInstance()
{
	static ConcreteModuleClass<ButterflyDrawTag> instance;
	return instance;
}

}
