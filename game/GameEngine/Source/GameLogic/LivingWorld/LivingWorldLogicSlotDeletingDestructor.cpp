// cl: /O2

// SubsystemSlot<LivingWorldLogic> scalar-deleting destructor, retail
// 0x00071370 (30 bytes). The exact constructor at 0x00071350 installs the
// one-slot vtable 0x01075E28, whose slot routes here through ILT 0x0002F838.
// The wrapper calls the paired 89-byte owned-subsystem destructor at
// 0x000713A0 through ILT 0x0000F240.

class LivingWorldLogic;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceLivingWorldLogicSlotDeletingDestructor()
{
	SubsystemSlot<LivingWorldLogic> value;
}
