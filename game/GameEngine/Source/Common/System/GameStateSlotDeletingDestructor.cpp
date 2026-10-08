// cl: /O2
//
// SubsystemDeleter<GameState> scalar-deleting destructor, retail (30 bytes).
// The exact constructor installs the one-slot vtable,
// whose slot routes here.

class GameState;

template<class SUBSYSTEM>
class SubsystemDeleter
{
public:
	virtual ~SubsystemDeleter();
	void *m_slot;
};

void forceGameStateSlotDeletingDestructor()
{
	SubsystemDeleter<GameState> value;
}
