// cl: /O2
//
// SubsystemDeleter<GameResultsInterface> scalar-deleting destructor, retail (30 bytes).
// The exact constructor installs the one-slot vtable,
// whose slot routes here.

class GameResultsInterface;

template<class SUBSYSTEM>
class SubsystemDeleter
{
public:
	virtual ~SubsystemDeleter();
	void *m_slot;
};

void forceGameResultsInterfaceSlotDeletingDestructor()
{
	SubsystemDeleter<GameResultsInterface> value;
}
