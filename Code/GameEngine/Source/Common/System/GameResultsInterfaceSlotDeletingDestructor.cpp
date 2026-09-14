// cl: /O2
//
// SubsystemSlot<GameResultsInterface> scalar-deleting destructor, retail (30 bytes).
// The exact constructor installs the one-slot vtable,
// whose slot routes here.

class GameResultsInterface;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceGameResultsInterfaceSlotDeletingDestructor()
{
	SubsystemSlot<GameResultsInterface> value;
}
