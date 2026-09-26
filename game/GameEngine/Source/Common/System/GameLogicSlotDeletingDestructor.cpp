// cl: /O2

// SubsystemSlot<GameLogic> scalar-deleting destructor, retail
// 0x00071A30 (30 bytes). The exact constructor at 0x00071A10 installs the
// one-slot vtable, whose slot routes here.

class GameLogic;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceGameLogicSlotDeletingDestructor()
{
	SubsystemSlot<GameLogic> value;
}
