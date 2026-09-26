// cl: /O2
//
// SubsystemSlot<MultiplayerSettings> scalar-deleting destructor, retail
// 0x0006FC30 (30 bytes).  The exact constructor at 0x0006FC10 installs the
// one-slot vtable 0x01075DAC, whose slot routes here through ILT 0x00018F48.
// The wrapper calls the paired 89-byte owned-subsystem destructor at
// 0x0006FC60 through ILT 0x0002C543.

class MultiplayerSettings;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceMultiplayerSettingsSlotDeletingDestructor()
{
	SubsystemSlot<MultiplayerSettings> value;
}
