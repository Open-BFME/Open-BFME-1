// cl: /O2
//
// SubsystemSlot<ObjectCreationListStore> scalar-deleting destructor, retail
// 0x00070830 (30 bytes).  The exact constructor at 0x00070810 installs the
// one-slot vtable 0x01075DEC, whose slot routes here through ILT 0x00033BB8.
// The wrapper calls the paired 89-byte owned-subsystem destructor at
// 0x00070860 through ILT 0x0003817C.

class ObjectCreationListStore;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceObjectCreationListStoreSlotDeletingDestructor()
{
	SubsystemSlot<ObjectCreationListStore> value;
}
