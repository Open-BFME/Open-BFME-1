// cl: /O2

// SubsystemDeleter<VictoryConditionsInterface> scalar-deleting destructor, retail
// 0x00071C70 (30 bytes). The exact constructor at 0x00071C50 installs the
// one-slot vtable, whose slot routes here.

class VictoryConditionsInterface;

template<class SUBSYSTEM>
class SubsystemDeleter
{
public:
	virtual ~SubsystemDeleter();
	void *m_slot;
};

void forceVictoryConditionsInterfaceSlotDeletingDestructor()
{
	SubsystemDeleter<VictoryConditionsInterface> value;
}
