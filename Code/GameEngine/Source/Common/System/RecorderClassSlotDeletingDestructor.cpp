// cl: /O2

// SubsystemSlot<RecorderClass> scalar-deleting destructor, retail
// 0x00071AF0 (30 bytes). The exact constructor at 0x00071AD0 installs the
// one-slot vtable, whose slot routes here.

class RecorderClass;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceRecorderClassSlotDeletingDestructor()
{
	SubsystemSlot<RecorderClass> value;
}
