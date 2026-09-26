// cl: /EHs-c-

// The public FX particle header intentionally keeps ConcreteModuleClass
// specializations empty: fx_particle_system.cpp builds a second FXPS_V mode
// with a virtual view.  This TU owns the actual DefaultModuleTag2 singleton ABI only.
// Its four data words are the retail object at 0x012F6AAC: table, the two
// source-pointer values, and the registry link.  The constructor and
// destructor symbols remain the independently matched definitions in
// fx_particle_system_bulk.cpp; this inline semantic view is needed only so
// MSVC7.1 materializes their body inside the guarded function-local static.
// Retail also publishes the object as the current instance of its category
// (the store lands between the source loads and the member stores).

namespace FXParticleSystem
{

template <int N> class DefaultModuleTag
{
};

template <class Tag>
class ConcreteModuleClass;

typedef DefaultModuleTag<2> DefaultModuleTag2Tag;

// Retail globals: +4 reads [0x012F6D00], +8 reads [0x012F6D04], and the
// chain head is [0x012F64F0].  The current-instance slot is
// [0x012F64CC].  These names are TU-local ABI
// declarations; their DIR32 relocations are checked against those operands.
extern void **defaultModuleTag2SourceAt4;
extern void **defaultModuleTag2SourceAt8;
extern ConcreteModuleClass<DefaultModuleTag2Tag> *defaultModuleTag2RegistryHead;
extern ConcreteModuleClass<DefaultModuleTag2Tag> *defaultModuleTag2CurrentInstance;
extern void *defaultModuleTag2Vtable[];

template <>
class ConcreteModuleClass<DefaultModuleTag2Tag>
{
public:
	ConcreteModuleClass()
	{
		void *sourceAt8 = *defaultModuleTag2SourceAt8;
		void *sourceAt4 = *defaultModuleTag2SourceAt4;
		defaultModuleTag2CurrentInstance = this;
		m_sourceAt8 = sourceAt8;
		m_sourceAt4 = sourceAt4;
		m_next = defaultModuleTag2RegistryHead;
		defaultModuleTag2RegistryHead = this;
		m_table = defaultModuleTag2Vtable;
	}

	~ConcreteModuleClass();
	static const ConcreteModuleClass<DefaultModuleTag2Tag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<DefaultModuleTag2Tag> &
ConcreteModuleClass<DefaultModuleTag2Tag>::getInstance()
{
	static ConcreteModuleClass<DefaultModuleTag2Tag> instance;
	return instance;
}

}
