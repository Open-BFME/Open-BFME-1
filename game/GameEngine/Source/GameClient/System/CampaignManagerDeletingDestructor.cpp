// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: CampaignManager scalar-deleting destructor at retail RVA
// 0x005BC970 (30 bytes). The matched constructor at 0x005BC400 installs
// vtable 0x0110F660, whose remaining slots include the literal name getter
// returning "CampaignManager". Its slot zero routes here, and this wrapper
// calls the matched complete destructor at 0x005BC4E0 through the ILT.

class CampaignManager
{
public:
	virtual ~CampaignManager();
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceCampaignManagerDeletingDestructor(const CampaignManager &that)
{
	CampaignManager value(that);
}
