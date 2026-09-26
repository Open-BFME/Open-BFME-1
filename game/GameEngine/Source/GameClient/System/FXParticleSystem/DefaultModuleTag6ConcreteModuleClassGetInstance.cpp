// cl: /EHs-c-

// The public FX particle header intentionally keeps ConcreteModuleClass
// specializations empty: fx_particle_system.cpp builds a second FXPS_V mode
// with a virtual view.  This TU owns the actual DefaultModuleTag6 singleton ABI only.
// Its four data words are the retail object at 0x012F6974: table, the two
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

typedef DefaultModuleTag<6> DefaultModuleTag6Tag;

// Retail globals: +4 reads [0x012F6C98], +8 reads [0x012F6C9C], and the
// chain head is [0x012F6500].  The current-instance slot is
// [0x012F64DC].  These names are TU-local ABI
// declarations; their DIR32 relocations are checked against those operands.
extern void **defaultModuleTag6SourceAt4;
extern void **defaultModuleTag6SourceAt8;
extern ConcreteModuleClass<DefaultModuleTag6Tag> *defaultModuleTag6RegistryHead;
extern ConcreteModuleClass<DefaultModuleTag6Tag> *defaultModuleTag6CurrentInstance;
extern void *defaultModuleTag6Vtable[];

template <>
class ConcreteModuleClass<DefaultModuleTag6Tag>
{
public:
	ConcreteModuleClass()
	{
		void *sourceAt8 = *defaultModuleTag6SourceAt8;
		void *sourceAt4 = *defaultModuleTag6SourceAt4;
		defaultModuleTag6CurrentInstance = this;
		m_sourceAt8 = sourceAt8;
		m_sourceAt4 = sourceAt4;
		m_next = defaultModuleTag6RegistryHead;
		defaultModuleTag6RegistryHead = this;
		m_table = defaultModuleTag6Vtable;
	}

	~ConcreteModuleClass();
	static const ConcreteModuleClass<DefaultModuleTag6Tag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<DefaultModuleTag6Tag> &
ConcreteModuleClass<DefaultModuleTag6Tag>::getInstance()
{
	static ConcreteModuleClass<DefaultModuleTag6Tag> instance;
	return instance;
}

}
