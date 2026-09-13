// cl: /O2
//
// SubsystemSlot<LocomotorStore> scalar-deleting destructor, retail 0x000708F0
// (30 bytes).  The exact constructor at 0x000708D0 installs the one-slot
// vtable 0x01075DF0, whose slot routes here through ILT 0x0000141F.  The
// wrapper calls the paired 89-byte owned-subsystem destructor at 0x00070920
// through ILT 0x0002F077.

class LocomotorStore;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceLocomotorStoreSlotDeletingDestructor()
{
	SubsystemSlot<LocomotorStore> value;
}
