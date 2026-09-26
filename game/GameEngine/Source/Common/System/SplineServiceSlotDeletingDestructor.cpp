// cl: /O2

// SubsystemSlot<SplineService> scalar-deleting destructor, retail
// 0x00071430 (30 bytes). The exact constructor at 0x00071410 installs the
// one-slot vtable 0x01075E2C, whose slot routes here through ILT 0x000274DA.
// The wrapper calls the paired 89-byte owned-subsystem destructor at
// 0x00071460 through ILT 0x00039BDF.

class SplineService;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceSplineServiceSlotDeletingDestructor()
{
	SubsystemSlot<SplineService> value;
}
