// cl: /O2
//
// SubsystemSlot<ArmorStore> scalar-deleting destructor, retail 0x00070B30
// (30 bytes).  The exact constructor at 0x00070B10 installs the one-slot
// vtable 0x01075DFC, whose slot routes here through ILT 0x0004156F.  The
// wrapper calls the paired 89-byte owned-subsystem destructor at 0x00070B60
// through ILT 0x000172CE.

class ArmorStore;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceArmorStoreSlotDeletingDestructor()
{
	SubsystemSlot<ArmorStore> value;
}
