// cl: /O2

// SubsystemSlot<HouseColorSystem> scalar-deleting destructor, retail
// 0x00071DF0 (30 bytes). The exact constructor at 0x00071DD0 installs the
// one-slot vtable, whose slot routes here.

class HouseColorSystem;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceHouseColorSystemSlotDeletingDestructor()
{
	SubsystemSlot<HouseColorSystem> value;
}
