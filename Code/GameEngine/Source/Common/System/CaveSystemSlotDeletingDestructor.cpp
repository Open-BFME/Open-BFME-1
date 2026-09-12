// cl: /O2
//
// SubsystemSlot<CaveSystem> scalar-deleting destructor, retail 0x000702F0
// (30 bytes).  The exact constructor at 0x000702D0 installs the one-slot
// vtable 0x01075DD0, whose slot routes here through ILT 0x00012B3E.  The
// wrapper calls the paired 89-byte owned-subsystem destructor at 0x00070320
// through ILT 0x000401A1.

class CaveSystem;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceCaveSystemSlotDeletingDestructor()
{
	SubsystemSlot<CaveSystem> value;
}
