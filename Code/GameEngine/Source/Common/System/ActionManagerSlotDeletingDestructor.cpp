// cl: /O2
//
// SubsystemSlot<ActionManager> scalar-deleting destructor, retail (30 bytes).
// The exact constructor installs the one-slot vtable,
// whose slot routes here.

class ActionManager;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceActionManagerSlotDeletingDestructor()
{
	SubsystemSlot<ActionManager> value;
}
