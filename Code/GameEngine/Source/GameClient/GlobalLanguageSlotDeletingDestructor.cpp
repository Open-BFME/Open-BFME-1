// cl: /O2
//
// SubsystemSlot<GlobalLanguage> scalar-deleting destructor, retail 0x0006F7B0
// (30 bytes).  The exact constructor at 0x0006F790 installs the one-slot
// vtable 0x01075D94, which routes here through ILT 0x00015726.  The wrapper
// calls the paired 89-byte owned-subsystem destructor at 0x0006F7E0 through
// ILT 0x000268AA.

class GlobalLanguage;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceGlobalLanguageSlotDeletingDestructor()
{
	SubsystemSlot<GlobalLanguage> value;
}
