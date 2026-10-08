// cl: /O2
//
// SubsystemDeleter<VictorySystem> scalar-deleting destructor, retail 0x00071F70 (30 bytes).
// The exact constructor at 0x00071F50 installs the one-slot vtable,
// whose slot routes here.

class VictorySystem;

template<class SUBSYSTEM>
class SubsystemDeleter
{
public:
	virtual ~SubsystemDeleter();
	void *m_slot;
};

void forceVictorySystemSlotDeletingDestructor()
{
	SubsystemDeleter<VictorySystem> value;
}
