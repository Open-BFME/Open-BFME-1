// cl: /O2
//
// SubsystemSlot<GameStateMap> scalar-deleting destructor, retail (30 bytes).
// The exact constructor installs the one-slot vtable,
// whose slot routes here.

class GameStateMap;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceGameStateMapSlotDeletingDestructor()
{
	SubsystemSlot<GameStateMap> value;
}
