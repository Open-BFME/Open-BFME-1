// cl: /EHs-c-

// The public FX particle header intentionally keeps ConcreteModuleClass
// specializations empty: fx_particle_system.cpp builds a second FXPS_V mode
// with a virtual view.  This TU owns the actual OrthoEmissionVelocity singleton ABI only.
// Its four data words are the retail object at 0x012F6B3C: table, the two
// source-pointer values, and the registry link.  The constructor and
// destructor symbols remain the independently matched definitions in
// fx_particle_system_bulk.cpp; this inline semantic view is needed only so
// MSVC7.1 materializes their body inside the guarded function-local static.
// Retail also publishes the object as the current instance of its category
// (the store lands between the source loads and the member stores).

namespace FXParticleSystem
{

struct OrthoEmissionVelocityModuleTag
{
};

template <class Tag>
class ConcreteModuleClass;

typedef OrthoEmissionVelocityModuleTag OrthoEmissionVelocityTag;

// Retail globals: +4 reads [0x012F6D30], +8 reads [0x012F6D34], and the
// chain head is [0x012F64F8].  The current-instance slot is
// [0x012F64D4].  These names are TU-local ABI
// declarations; their DIR32 relocations are checked against those operands.
extern void **orthoEmissionVelocitySourceAt4;
extern void **orthoEmissionVelocitySourceAt8;
extern ConcreteModuleClass<OrthoEmissionVelocityTag> *orthoEmissionVelocityRegistryHead;
extern ConcreteModuleClass<OrthoEmissionVelocityTag> *orthoEmissionVelocityCurrentInstance;
extern void *orthoEmissionVelocityVtable[];

template <>
class ConcreteModuleClass<OrthoEmissionVelocityTag>
{
public:
	ConcreteModuleClass()
	{
		void *sourceAt8 = *orthoEmissionVelocitySourceAt8;
		void *sourceAt4 = *orthoEmissionVelocitySourceAt4;
		orthoEmissionVelocityCurrentInstance = this;
		m_sourceAt8 = sourceAt8;
		m_sourceAt4 = sourceAt4;
		m_next = orthoEmissionVelocityRegistryHead;
		orthoEmissionVelocityRegistryHead = this;
		m_table = orthoEmissionVelocityVtable;
	}

	~ConcreteModuleClass();
	static const ConcreteModuleClass<OrthoEmissionVelocityTag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<OrthoEmissionVelocityTag> &
ConcreteModuleClass<OrthoEmissionVelocityTag>::getInstance()
{
	static ConcreteModuleClass<OrthoEmissionVelocityTag> instance;
	return instance;
}

}
