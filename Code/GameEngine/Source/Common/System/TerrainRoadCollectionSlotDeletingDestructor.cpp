// cl: /O2
//
// SubsystemSlot<TerrainRoadCollection> scalar-deleting destructor, retail
// 0x0006FDB0 (30 bytes).  The exact constructor at 0x0006FD90 installs the
// one-slot vtable 0x01075DB4, whose slot routes here through ILT 0x0001F280.
// The wrapper calls the paired 89-byte owned-subsystem destructor at
// 0x0006FDE0 through ILT 0x00045C50.

class TerrainRoadCollection;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceTerrainRoadCollectionSlotDeletingDestructor()
{
	SubsystemSlot<TerrainRoadCollection> value;
}
