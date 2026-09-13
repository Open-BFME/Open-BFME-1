// cl: /O2
//
// SubsystemSlot<FXListStore> scalar-deleting destructor, retail 0x000706B0
// (30 bytes).  The exact constructor at 0x00070690 installs the one-slot
// vtable 0x01075DE4, whose slot routes here through ILT 0x00027CFA.  The
// wrapper calls the paired 89-byte owned-subsystem destructor at 0x000706E0
// through ILT 0x00027728.

class FXListStore;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceFXListStoreSlotDeletingDestructor()
{
	SubsystemSlot<FXListStore> value;
}
