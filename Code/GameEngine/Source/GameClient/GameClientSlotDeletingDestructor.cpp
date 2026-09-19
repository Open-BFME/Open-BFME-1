// cl: /O2
//
// SubsystemSlot<GameClient> scalar-deleting destructor, retail 0x00071130
// (30 bytes).  The exact constructor at 0x00071110 installs the one-slot
// vtable 0x01075E1C, whose slot routes here through ILT 0x000173B4.  The
// wrapper calls the paired 89-byte owned-subsystem destructor at 0x00071160
// through ILT 0x0004473D.

class GameClient;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceGameClientSlotDeletingDestructor()
{
	SubsystemSlot<GameClient> value;
}
