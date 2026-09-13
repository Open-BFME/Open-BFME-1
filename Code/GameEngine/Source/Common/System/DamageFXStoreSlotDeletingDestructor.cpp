// cl: /O2
//
// SubsystemSlot<DamageFXStore> scalar-deleting destructor, retail 0x00070A70
// (30 bytes).  The exact constructor at 0x00070A50 installs the one-slot
// vtable 0x01075DF8, whose slot routes here through ILT 0x000226BF.  The
// wrapper calls the paired 89-byte owned-subsystem destructor at 0x00070AA0
// through ILT 0x000294F1.

class DamageFXStore;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceDamageFXStoreSlotDeletingDestructor()
{
	SubsystemSlot<DamageFXStore> value;
}
