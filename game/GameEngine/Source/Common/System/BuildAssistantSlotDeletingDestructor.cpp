// cl: /O2
//
// SubsystemSlot<BuildAssistant> scalar-deleting destructor, retail 0x00070BF0
// (30 bytes).  The exact constructor at 0x00070BD0 installs the one-slot
// vtable 0x01075E00, whose slot routes here through ILT 0x00043C61.  The
// wrapper calls the paired 89-byte owned-subsystem destructor at 0x00070C20
// through ILT 0x0001B7DE.

class BuildAssistant;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceBuildAssistantSlotDeletingDestructor()
{
	SubsystemSlot<BuildAssistant> value;
}
