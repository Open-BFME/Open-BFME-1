// cl: /O2
//
// SubsystemSlot<ScienceStore> scalar-deleting destructor, retail 0x0006FAB0
// (30 bytes).  The exact constructor at 0x0006FA90 installs the one-slot
// vtable 0x01075DA4, whose slot routes here through ILT 0x0000B52D.  The
// wrapper calls the paired 89-byte owned-subsystem destructor at 0x0006FAE0
// through ILT 0x0001B18A.

class ScienceStore;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceScienceStoreSlotDeletingDestructor()
{
	SubsystemSlot<ScienceStore> value;
}
