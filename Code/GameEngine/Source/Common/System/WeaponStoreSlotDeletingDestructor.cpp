// cl: /O2
//
// SubsystemSlot<WeaponStore> scalar-deleting destructor, retail 0x00070770
// (30 bytes).  The exact constructor at 0x00070750 installs the one-slot
// vtable 0x01075DE8, whose slot routes here through ILT 0x000314EE.  The
// wrapper calls the paired 89-byte owned-subsystem destructor at 0x000707A0
// through ILT 0x000307B5.

class WeaponStore;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceWeaponStoreSlotDeletingDestructor()
{
	SubsystemSlot<WeaponStore> value;
}
