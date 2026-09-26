// cl: /O2
//
// SubsystemSlot<PlayerTemplateStore> scalar-deleting destructor, retail
// 0x00070530 (30 bytes).  The exact constructor at 0x00070510 installs the
// one-slot vtable 0x01075DDC, whose slot routes here through ILT 0x000322E0.
// The wrapper calls the paired 89-byte owned-subsystem destructor at
// 0x00070560 through ILT 0x00041E39.

class PlayerTemplateStore;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forcePlayerTemplateStoreSlotDeletingDestructor()
{
	SubsystemSlot<PlayerTemplateStore> value;
}
