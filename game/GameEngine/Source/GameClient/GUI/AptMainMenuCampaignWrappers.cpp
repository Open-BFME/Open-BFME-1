// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// The MainMenu constructor at retail 0x0051F3A0 binds these two bodies beside
// the literal callback names "AptMainMenu::GoodCampaign" and
// "AptMainMenu::EvilCampaign".  Both forward to the still-opaque common body
// at 0x0051F1C0 through its retail ILT at 0x00047D2A.

class BfmeAptScreenMainMenu
{
public:
	void rva0051F1C0Campaign(const char *campaign, bool evil);
	void rva0051F360GoodCampaign(const char *campaign);
	void rva0051F380EvilCampaign(const char *campaign);
};

// ?rva0051F360GoodCampaign@BfmeAptScreenMainMenu@@QAEXPBD@Z
void BfmeAptScreenMainMenu::rva0051F360GoodCampaign(const char *campaign)
{
	rva0051F1C0Campaign(campaign, false);
}

// ?rva0051F380EvilCampaign@BfmeAptScreenMainMenu@@QAEXPBD@Z
void BfmeAptScreenMainMenu::rva0051F380EvilCampaign(const char *campaign)
{
	rva0051F1C0Campaign(campaign, true);
}
