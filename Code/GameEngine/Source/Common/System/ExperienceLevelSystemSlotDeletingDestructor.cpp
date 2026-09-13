// cl: /O2
//
// SubsystemSlot<ExperienceLevelSystem> scalar-deleting destructor, retail
// 0x00070EF0 (30 bytes).  The exact constructor at 0x00070ED0 installs the
// one-slot vtable 0x01075E10, whose slot routes here through ILT 0x0001333B.
// The wrapper calls the paired 89-byte owned-subsystem destructor at
// 0x00070F20 through ILT 0x000083C3.

class ExperienceLevelSystem;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceExperienceLevelSystemSlotDeletingDestructor()
{
	SubsystemSlot<ExperienceLevelSystem> value;
}
