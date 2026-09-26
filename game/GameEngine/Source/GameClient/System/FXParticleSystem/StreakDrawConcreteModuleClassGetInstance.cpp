// cl: /EHs-c-

// The public FX particle header intentionally keeps ConcreteModuleClass
// specializations empty: fx_particle_system.cpp builds a second FXPS_V mode
// with a virtual view.  This TU owns the actual StreakDraw singleton ABI only.
// Its four data words are the retail object at 0x012F698C: table, the two
// source-pointer values, and the category-6 registry link.  The constructor
// and destructor symbols remain the independently matched definitions in
// fx_particle_system_bulk.cpp; this inline semantic view is needed only so
// MSVC7.1 materializes their body inside the guarded function-local static.

namespace FXParticleSystem
{

template <int N>
class DefaultParticleModule
{
};

template <int N>
class DefaultParticleModuleTemplate
{
};

class StreakDrawModule
{
};

class StreakDrawModuleTemplate
{
};

extern const char STREAK_DRAW_MODULE_KEY[1];
extern const char STREAK_DRAW_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1],
	class Module, class ModuleTemplate, class ParticleModule,
	class ParticleModuleTemplate>
class ModuleTag
{
};

template <class Tag>
class ConcreteModuleClass;

typedef ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME,
	StreakDrawModule, StreakDrawModuleTemplate,
	DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > StreakDrawTag;

// Retail globals: +4 reads [0x012F6CA0], +8 reads [0x012F6CA4], and the
// category-6 chain head is [0x012F6500].  These names are TU-local ABI
// declarations; their DIR32 relocations are checked against those operands.
extern void **streakDrawSourceAt4;
extern void **streakDrawSourceAt8;
extern ConcreteModuleClass<StreakDrawTag> *streakDrawRegistryHead;
extern void *streakDrawVtable[];

template <>
class ConcreteModuleClass<StreakDrawTag>
{
public:
	ConcreteModuleClass()
	{
		void *sourceAt8 = *streakDrawSourceAt8;
		void *sourceAt4 = *streakDrawSourceAt4;
		m_sourceAt8 = sourceAt8;
		m_sourceAt4 = sourceAt4;
		m_next = streakDrawRegistryHead;
		streakDrawRegistryHead = this;
		m_table = streakDrawVtable;
	}

	~ConcreteModuleClass();
	static const ConcreteModuleClass<StreakDrawTag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<StreakDrawTag> &
ConcreteModuleClass<StreakDrawTag>::getInstance()
{
	static ConcreteModuleClass<StreakDrawTag> instance;
	return instance;
}

}
