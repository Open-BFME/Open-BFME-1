// cl: /EHs-c-

// The public FX particle header intentionally keeps ConcreteModuleClass
// specializations empty: fx_particle_system.cpp builds a second FXPS_V mode
// with a virtual view.  This TU owns the actual DefaultModuleTag1 singleton ABI only.
// Its four data words are the retail object at 0x012F6A1C: table, the two
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

typedef DefaultModuleTag<1> DefaultModuleTag1Tag;

// Retail globals: +4 reads [0x012F6CD0], +8 reads [0x012F6CD4], and the
// chain head is [0x012F64EC].  The current-instance slot is
// [0x012F64C8].  These names are TU-local ABI
// declarations; their DIR32 relocations are checked against those operands.
extern void **defaultModuleTag1SourceAt4;
extern void **defaultModuleTag1SourceAt8;
extern ConcreteModuleClass<DefaultModuleTag1Tag> *defaultModuleTag1RegistryHead;
extern ConcreteModuleClass<DefaultModuleTag1Tag> *defaultModuleTag1CurrentInstance;
extern void *defaultModuleTag1Vtable[];

template <>
class ConcreteModuleClass<DefaultModuleTag1Tag>
{
public:
	ConcreteModuleClass()
	{
		void *sourceAt8 = *defaultModuleTag1SourceAt8;
		void *sourceAt4 = *defaultModuleTag1SourceAt4;
		defaultModuleTag1CurrentInstance = this;
		m_sourceAt8 = sourceAt8;
		m_sourceAt4 = sourceAt4;
		m_next = defaultModuleTag1RegistryHead;
		defaultModuleTag1RegistryHead = this;
		m_table = defaultModuleTag1Vtable;
	}

	~ConcreteModuleClass();
	static const ConcreteModuleClass<DefaultModuleTag1Tag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<DefaultModuleTag1Tag> &
ConcreteModuleClass<DefaultModuleTag1Tag>::getInstance()
{
	static ConcreteModuleClass<DefaultModuleTag1Tag> instance;
	return instance;
}

}
