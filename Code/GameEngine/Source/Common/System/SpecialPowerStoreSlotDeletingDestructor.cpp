// cl: /O2
//
// SubsystemSlot<SpecialPowerStore> scalar-deleting destructor, retail
// 0x000709B0 (30 bytes).  The exact constructor at 0x00070990 installs the
// one-slot vtable 0x01075DF4, whose slot routes here through ILT 0x00030DD7.
// The wrapper calls the paired 89-byte owned-subsystem destructor at
// 0x000709E0 through ILT 0x000248C0.

class SpecialPowerStore;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceSpecialPowerStoreSlotDeletingDestructor()
{
	SubsystemSlot<SpecialPowerStore> value;
}
