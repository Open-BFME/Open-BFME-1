// cl: /O2

// SubsystemDeleter<LivingWorldCampaignManager> scalar-deleting destructor, retail
// 0x00071EB0 (30 bytes). The exact constructor at 0x00071E90 installs the
// one-slot vtable, whose slot routes here.

class LivingWorldCampaignManager;

template<class SUBSYSTEM>
class SubsystemDeleter
{
public:
	virtual ~SubsystemDeleter();
	void *m_slot;
};

void forceLivingWorldCampaignManagerSlotDeletingDestructor()
{
	SubsystemDeleter<LivingWorldCampaignManager> value;
}
