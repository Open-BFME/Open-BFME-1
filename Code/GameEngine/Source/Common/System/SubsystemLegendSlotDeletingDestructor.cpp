// cl: /O2
//
// SubsystemSlot<SubsystemLegend> scalar-deleting destructor, retail
// 0x0006F630 (30 bytes).  The exact constructor at 0x0006F610 installs
// vtable 0x01075D8C, whose slot zero routes here through ILT 0x00032376.
// This wrapper calls the 89-byte owned-subsystem destructor at 0x0006F660
// through ILT 0x00002BDF.

class SubsystemLegend;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceSubsystemLegendSlotDeletingDestructor()
{
	SubsystemSlot<SubsystemLegend> value;
}
