// cl: /O2

// SubsystemSlot<LivingWorldCampaignManager> scalar-deleting destructor, retail
// 0x00071EB0 (30 bytes). The exact constructor at 0x00071E90 installs the
// one-slot vtable, whose slot routes here.

class LivingWorldCampaignManager;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceLivingWorldCampaignManagerSlotDeletingDestructor()
{
	SubsystemSlot<LivingWorldCampaignManager> value;
}
