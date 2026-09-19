// cl: /O2
//
// SubsystemSlot<SidesList> scalar-deleting destructor, retail 0x00070230
// (30 bytes).  The exact constructor at 0x00070210 installs the one-slot
// vtable 0x01075DCC, whose slot routes here through ILT 0x0000494E.  The
// wrapper calls the paired 89-byte owned-subsystem destructor at 0x00070260
// through ILT 0x000467FE.

class SidesList;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceSidesListSlotDeletingDestructor()
{
	SubsystemSlot<SidesList> value;
}
