// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Open-BFME5: BfmeAptScreenCampaignReview's scalar-deleting destructor at
// retail RVA 0x0050E1A0 (30 bytes). The matched constructor at 0x0050E320
// installs primary and secondary vtables 0x01104C74 and 0x01104C70; the
// primary slot zero reaches this wrapper. Its complete destructor at
// 0x0050DBD0 resets those views before closing the AptCampaignReview screen.

class BfmeAptScreenCampaignReview
{
public:
	__declspec(noinline) virtual ~BfmeAptScreenCampaignReview();
};

BfmeAptScreenCampaignReview::~BfmeAptScreenCampaignReview()
{
}

void Force_BfmeAptScreenCampaignReview_Deleting_Destructor()
{
	BfmeAptScreenCampaignReview value;
}
