// cl: /O2

// SubsystemSlot<CrateSystem> scalar-deleting destructor, retail
// 0x000718B0 (30 bytes). The exact constructor at 0x00071890 installs the
// one-slot vtable, whose slot routes here.

class CrateSystem;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceCrateSystemSlotDeletingDestructor()
{
	SubsystemSlot<CrateSystem> value;
}
