// cl: /O2
//
// SubsystemSlot<GameState> scalar-deleting destructor, retail (30 bytes).
// The exact constructor installs the one-slot vtable,
// whose slot routes here.

class GameState;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceGameStateSlotDeletingDestructor()
{
	SubsystemSlot<GameState> value;
}
