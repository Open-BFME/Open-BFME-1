// cl: /O2
//
// SubsystemDeleter<GameStateMap> scalar-deleting destructor, retail (30 bytes).
// The exact constructor installs the one-slot vtable,
// whose slot routes here.

class GameStateMap;

template<class SUBSYSTEM>
class SubsystemDeleter
{
public:
	virtual ~SubsystemDeleter();
	void *m_slot;
};

void forceGameStateMapSlotDeletingDestructor()
{
	SubsystemDeleter<GameStateMap> value;
}
