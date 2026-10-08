// cl: /O2
//
// SubsystemDeleter<ActionManager> scalar-deleting destructor, retail (30 bytes).
// The exact constructor installs the one-slot vtable,
// whose slot routes here.

class ActionManager;

template<class SUBSYSTEM>
class SubsystemDeleter
{
public:
	virtual ~SubsystemDeleter();
	void *m_slot;
};

void forceActionManagerSlotDeletingDestructor()
{
	SubsystemDeleter<ActionManager> value;
}
