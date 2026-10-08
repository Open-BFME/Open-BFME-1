// cl: /O2

// SubsystemDeleter<RecorderClass> scalar-deleting destructor, retail
// 0x00071AF0 (30 bytes). The exact constructor at 0x00071AD0 installs the
// one-slot vtable, whose slot routes here.

class RecorderClass;

template<class SUBSYSTEM>
class SubsystemDeleter
{
public:
	virtual ~SubsystemDeleter();
	void *m_slot;
};

void forceRecorderClassSlotDeletingDestructor()
{
	SubsystemDeleter<RecorderClass> value;
}
