// cl: /O2
//
// SubsystemSlot<TerrainTypeCollection> scalar-deleting destructor, retail
// 0x0006FCF0 (30 bytes).  The exact constructor at 0x0006FCD0 installs the
// one-slot vtable 0x01075DB0, whose slot routes here through ILT 0x0000F26D.
// The wrapper calls the paired 89-byte owned-subsystem destructor at
// 0x0006FD20 through ILT 0x0002C520.

class TerrainTypeCollection;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceTerrainTypeCollectionSlotDeletingDestructor()
{
	SubsystemSlot<TerrainTypeCollection> value;
}
