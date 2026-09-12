// cl: /O2
//
// SubsystemSlot<GameTextInterface> scalar-deleting destructor, retail
// 0x0006F870 (30 bytes).  The exact constructor at 0x0006F850 installs the
// one-slot vtable 0x01075D98, whose slot routes here through ILT 0x00034400.
// The wrapper calls the paired 89-byte owned-subsystem destructor at
// 0x0006F8A0 through ILT 0x0001C274.

class GameTextInterface;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceGameTextInterfaceSlotDeletingDestructor()
{
	SubsystemSlot<GameTextInterface> value;
}
