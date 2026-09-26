// cl: /EHs-c-

// The public FX particle header intentionally keeps ConcreteModuleClass
// specializations empty: fx_particle_system.cpp builds a second FXPS_V mode
// with a virtual view.  This TU owns the actual PointEmissionVolume singleton ABI only.
// Its four data words are the retail object at 0x012F6BB4: table, the two
// source-pointer values, and the registry link.  The constructor and
// destructor symbols remain the independently matched definitions in
// fx_particle_system_bulk.cpp; this inline semantic view is needed only so
// MSVC7.1 materializes their body inside the guarded function-local static.
// Retail also publishes the object as the current instance of its category
// (the store lands between the source loads and the member stores).

namespace FXParticleSystem
{

struct PointEmissionVolumeModuleTag
{
};

template <class Tag>
class ConcreteModuleClass;

typedef PointEmissionVolumeModuleTag PointEmissionVolumeTag;

// Retail globals: +4 reads [0x012F6D58], +8 reads [0x012F6D5C], and the
// chain head is [0x012F64FC].  The current-instance slot is
// [0x012F64D8].  These names are TU-local ABI
// declarations; their DIR32 relocations are checked against those operands.
extern void **pointEmissionVolumeSourceAt4;
extern void **pointEmissionVolumeSourceAt8;
extern ConcreteModuleClass<PointEmissionVolumeTag> *pointEmissionVolumeRegistryHead;
extern ConcreteModuleClass<PointEmissionVolumeTag> *pointEmissionVolumeCurrentInstance;
extern void *pointEmissionVolumeVtable[];

template <>
class ConcreteModuleClass<PointEmissionVolumeTag>
{
public:
	ConcreteModuleClass()
	{
		void *sourceAt8 = *pointEmissionVolumeSourceAt8;
		void *sourceAt4 = *pointEmissionVolumeSourceAt4;
		pointEmissionVolumeCurrentInstance = this;
		m_sourceAt8 = sourceAt8;
		m_sourceAt4 = sourceAt4;
		m_next = pointEmissionVolumeRegistryHead;
		pointEmissionVolumeRegistryHead = this;
		m_table = pointEmissionVolumeVtable;
	}

	~ConcreteModuleClass();
	static const ConcreteModuleClass<PointEmissionVolumeTag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<PointEmissionVolumeTag> &
ConcreteModuleClass<PointEmissionVolumeTag>::getInstance()
{
	static ConcreteModuleClass<PointEmissionVolumeTag> instance;
	return instance;
}

}
