// cl: /EHs-c-

// The public FX particle header intentionally keeps ConcreteModuleClass
// specializations empty: fx_particle_system.cpp builds a second FXPS_V mode
// with a virtual view.  This TU owns the actual DefaultModuleTag3 singleton ABI only.
// Its four data words are the retail object at 0x012F6A7C: table, the two
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

typedef DefaultModuleTag<3> DefaultModuleTag3Tag;

// Retail globals: +4 reads [0x012F6CF0], +8 reads [0x012F6CF4], and the
// chain head is [0x012F64F4].  The current-instance slot is
// [0x012F64D0].  These names are TU-local ABI
// declarations; their DIR32 relocations are checked against those operands.
extern void **defaultModuleTag3SourceAt4;
extern void **defaultModuleTag3SourceAt8;
extern ConcreteModuleClass<DefaultModuleTag3Tag> *defaultModuleTag3RegistryHead;
extern ConcreteModuleClass<DefaultModuleTag3Tag> *defaultModuleTag3CurrentInstance;
extern void *defaultModuleTag3Vtable[];

template <>
class ConcreteModuleClass<DefaultModuleTag3Tag>
{
public:
	ConcreteModuleClass()
	{
		void *sourceAt8 = *defaultModuleTag3SourceAt8;
		void *sourceAt4 = *defaultModuleTag3SourceAt4;
		defaultModuleTag3CurrentInstance = this;
		m_sourceAt8 = sourceAt8;
		m_sourceAt4 = sourceAt4;
		m_next = defaultModuleTag3RegistryHead;
		defaultModuleTag3RegistryHead = this;
		m_table = defaultModuleTag3Vtable;
	}

	~ConcreteModuleClass();
	static const ConcreteModuleClass<DefaultModuleTag3Tag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<DefaultModuleTag3Tag> &
ConcreteModuleClass<DefaultModuleTag3Tag>::getInstance()
{
	static ConcreteModuleClass<DefaultModuleTag3Tag> instance;
	return instance;
}

}
