// cl: /EHs-c-

// The public FX particle header intentionally keeps ConcreteModuleClass
// specializations empty: fx_particle_system.cpp builds a second FXPS_V mode
// with a virtual view.  This TU owns the actual DefaultModuleTag7 singleton ABI only.
// Its four data words are the retail object at 0x012F6ADC: table, the two
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

typedef DefaultModuleTag<7> DefaultModuleTag7Tag;

// Retail globals: +4 reads [0x012F6D10], +8 reads [0x012F6D14], and the
// chain head is [0x012F6504].  The current-instance slot is
// [0x012F64E0].  These names are TU-local ABI
// declarations; their DIR32 relocations are checked against those operands.
extern void **defaultModuleTag7SourceAt4;
extern void **defaultModuleTag7SourceAt8;
extern ConcreteModuleClass<DefaultModuleTag7Tag> *defaultModuleTag7RegistryHead;
extern ConcreteModuleClass<DefaultModuleTag7Tag> *defaultModuleTag7CurrentInstance;
extern void *defaultModuleTag7Vtable[];

template <>
class ConcreteModuleClass<DefaultModuleTag7Tag>
{
public:
	ConcreteModuleClass()
	{
		void *sourceAt8 = *defaultModuleTag7SourceAt8;
		void *sourceAt4 = *defaultModuleTag7SourceAt4;
		defaultModuleTag7CurrentInstance = this;
		m_sourceAt8 = sourceAt8;
		m_sourceAt4 = sourceAt4;
		m_next = defaultModuleTag7RegistryHead;
		defaultModuleTag7RegistryHead = this;
		m_table = defaultModuleTag7Vtable;
	}

	~ConcreteModuleClass();
	static const ConcreteModuleClass<DefaultModuleTag7Tag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<DefaultModuleTag7Tag> &
ConcreteModuleClass<DefaultModuleTag7Tag>::getInstance()
{
	static ConcreteModuleClass<DefaultModuleTag7Tag> instance;
	return instance;
}

}
