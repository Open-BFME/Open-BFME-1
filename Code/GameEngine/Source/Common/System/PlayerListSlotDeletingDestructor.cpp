// cl: /O2

// SubsystemSlot<PlayerList> scalar-deleting destructor, retail
// 0x00071970 (30 bytes). The exact constructor at 0x00071950 installs the
// one-slot vtable, whose slot routes here.

class PlayerList;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forcePlayerListSlotDeletingDestructor()
{
	SubsystemSlot<PlayerList> value;
}
