// cl: /O2

// SubsystemSlot<TaintManager> scalar-deleting destructor, retail
// 0x000715B0 (30 bytes). The exact constructor at 0x00071590 installs the
// one-slot vtable, whose slot routes here.

class TaintManager;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceTaintManagerSlotDeletingDestructor()
{
	SubsystemSlot<TaintManager> value;
}
