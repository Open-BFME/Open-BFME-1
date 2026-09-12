// cl: /O2
//
// SubsystemSlot<CDManagerInterface> scalar-deleting destructor, retail
// 0x0006FE70 (30 bytes).  The exact constructor at 0x0006FE50 installs the
// one-slot vtable 0x01075DB8, whose slot routes here through ILT 0x0002501D.
// The wrapper calls the paired 89-byte owned-subsystem destructor at
// 0x0006FEA0 through ILT 0x000220E3.

class CDManagerInterface;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceCDManagerInterfaceSlotDeletingDestructor()
{
	SubsystemSlot<CDManagerInterface> value;
}
