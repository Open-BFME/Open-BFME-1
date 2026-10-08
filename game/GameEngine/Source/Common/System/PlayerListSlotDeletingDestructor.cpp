// cl: /O2

// SubsystemDeleter<PlayerList> scalar-deleting destructor, retail
// 0x00071970 (30 bytes). The exact constructor at 0x00071950 installs the
// one-slot vtable, whose slot routes here.

class PlayerList;

template<class SUBSYSTEM>
class SubsystemDeleter
{
public:
	virtual ~SubsystemDeleter();
	void *m_slot;
};

void forcePlayerListSlotDeletingDestructor()
{
	SubsystemDeleter<PlayerList> value;
}
