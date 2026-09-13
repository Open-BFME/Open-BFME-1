// cl: /O2
//
// SubsystemSlot<PlayerAITypeSet> scalar-deleting destructor, retail
// 0x00070470 (30 bytes).  The exact constructor at 0x00070450 installs the
// one-slot vtable 0x01075DD8, whose slot routes here through ILT 0x0003C38F.
// The wrapper calls the paired 89-byte owned-subsystem destructor at
// 0x000704A0 through ILT 0x00042C21.

class PlayerAITypeSet;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forcePlayerAITypeSetSlotDeletingDestructor()
{
	SubsystemSlot<PlayerAITypeSet> value;
}
