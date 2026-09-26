// cl: /O2
//
// SubsystemSlot<LivingWorldManager> scalar-deleting destructor, retail
// 0x00071070 (30 bytes).  The exact constructor at 0x00071050 installs the
// one-slot vtable 0x01075E18, whose slot routes here through ILT 0x000227EB.
// The wrapper calls the paired 89-byte owned-subsystem destructor at
// 0x000710A0 through ILT 0x00034E96.

class LivingWorldManager;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceLivingWorldManagerSlotDeletingDestructor()
{
	SubsystemSlot<LivingWorldManager> value;
}
