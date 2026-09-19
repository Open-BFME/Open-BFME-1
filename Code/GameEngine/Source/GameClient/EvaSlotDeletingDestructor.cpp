// cl: /O2
//
// SubsystemSlot<Eva> scalar-deleting destructor, retail 0x0006F9F0
// (30 bytes).  The exact constructor at 0x0006F9D0 installs the one-slot
// vtable 0x01075DA0, whose slot routes here through ILT 0x0000C13F.  The
// wrapper calls the paired 89-byte owned-subsystem destructor at 0x0006FA20
// through ILT 0x0003B51B.

class Eva;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceEvaSlotDeletingDestructor()
{
	SubsystemSlot<Eva> value;
}
