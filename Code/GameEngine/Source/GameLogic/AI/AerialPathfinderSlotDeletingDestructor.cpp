// cl: /O2

// SubsystemSlot<AerialPathfinder> scalar-deleting destructor, retail
// 0x000712B0 (30 bytes). The exact constructor at 0x00071290 installs the
// one-slot vtable 0x01075E24, whose slot routes here through ILT 0x0002CAF2.
// The wrapper calls the paired 89-byte owned-subsystem destructor at
// 0x000712E0 through ILT 0x000054F7.

class AerialPathfinder;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceAerialPathfinderSlotDeletingDestructor()
{
	SubsystemSlot<AerialPathfinder> value;
}
