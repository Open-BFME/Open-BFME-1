// cl: /O2
//
// SubsystemSlot<UpgradeCenter> scalar-deleting destructor, retail 0x0006FB70
// (30 bytes).  The exact constructor at 0x0006FB50 installs the one-slot
// vtable 0x01075DA8, whose slot routes here through ILT 0x00048DA1.
// The wrapper calls the paired 89-byte owned-subsystem destructor at
// 0x0006FBA0 through ILT 0x0000111D.

class UpgradeCenter;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceUpgradeCenterSlotDeletingDestructor()
{
	SubsystemSlot<UpgradeCenter> value;
}
