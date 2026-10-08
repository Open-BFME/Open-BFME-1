// cl: /O2

// SubsystemDeleter<AttributeModifierStore> scalar-deleting destructor, retail
// 0x000714F0 (30 bytes). The exact constructor at 0x000714D0 installs the
// one-slot vtable 0x01075E30, whose slot routes here through ILT 0x00043AC7.
// The wrapper calls the paired 89-byte owned-subsystem destructor at
// 0x00071520 through ILT 0x00020941.

class AttributeModifierStore;

template<class SUBSYSTEM>
class SubsystemDeleter
{
public:
	virtual ~SubsystemDeleter();
	void *m_slot;
};

void forceAttributeModifierStoreSlotDeletingDestructor()
{
	SubsystemDeleter<AttributeModifierStore> value;
}
