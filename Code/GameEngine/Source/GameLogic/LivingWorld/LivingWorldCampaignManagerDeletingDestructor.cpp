// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: LivingWorldCampaignManager scalar-deleting destructor at retail
// RVA 0x003A87A0 (30 bytes).  The exact default constructor at 0x003B7C70
// installs the primary one-slot vtable at 0x010EC770; slot zero is the ILT
// 0x00022250, whose jump reaches this wrapper.  The wrapper calls the matched
// virtual complete destructor at 0x003B7D30 through ILT 0x00045E26.

class LivingWorldCampaignManager
{
public:
	virtual ~LivingWorldCampaignManager();
};

void forceLivingWorldCampaignManagerDeletingDestructor()
{
	LivingWorldCampaignManager value;
}
