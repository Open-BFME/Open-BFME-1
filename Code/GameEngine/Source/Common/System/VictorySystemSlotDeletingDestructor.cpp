// cl: /O2
//
// SubsystemSlot<VictorySystem> scalar-deleting destructor, retail 0x00071F70 (30 bytes).
// The exact constructor at 0x00071F50 installs the one-slot vtable,
// whose slot routes here.

class VictorySystem;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceVictorySystemSlotDeletingDestructor()
{
	SubsystemSlot<VictorySystem> value;
}
