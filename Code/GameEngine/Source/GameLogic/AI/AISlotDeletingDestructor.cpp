// cl: /O2
//
// SubsystemSlot<AI> scalar-deleting destructor, retail 0x000711F0 (30 bytes).
// The exact constructor at 0x000711D0 installs the one-slot vtable
// 0x01075E20, whose slot routes here through ILT 0x00022B83.  The wrapper
// calls the paired 89-byte owned-subsystem destructor at 0x00071220 through
// ILT 0x00013A48.

class AI;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceAISlotDeletingDestructor()
{
	SubsystemSlot<AI> value;
}
