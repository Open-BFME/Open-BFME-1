class BfmeOneCHF
{
public:
	void bfmeOneCHF();
};

class BfmeTwoCHF
{
public:
	void bfmeTwoCHF();
	unsigned char m_bfmeHead[0x44];
	bool m_bfmeFlag;
};

// 0x012F1024 is EA's `TheLivingWorldCampaignManager`, defined once in
// game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldCampaignManager.cpp:
// GameEngine::init pushes the literal "TheLivingWorldCampaignManager"
// (0x01076174, its only occurrence and only xref) into a BFMERetailAsciiString
// and passes 0x012F1024 as the `T*&` to `??$initSubsystem@VLivingWorldCampaignManager@@`
// (RVA 0x00075660), whose `mov [esi],edi` is the store.  BfmeOneCHF above is
// this TU's view of that pointee (its member is the pinned bfmeOneCHF callee),
// so the use casts rather than declaring a second name for the address.
class LivingWorldCampaignManager;
extern LivingWorldCampaignManager *TheLivingWorldCampaignManager;

// 0x012F1028 is EA's `TheLivingWorldLogic`, defined once in
// game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldLogic.cpp, by the
// same initSubsystem evidence (literal "TheLivingWorldLogic" at 0x010762B4,
// RVA 0x00074B10).  BfmeTwoCHF above is this TU's view of that object.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

void bfmeGoCHF()
{
	BfmeTwoCHF *two = (BfmeTwoCHF *)TheLivingWorldLogic;
	if (two->m_bfmeFlag)
	{
		((BfmeOneCHF *)TheLivingWorldCampaignManager)->bfmeOneCHF();
		two->bfmeTwoCHF();
		((BfmeTwoCHF *)TheLivingWorldLogic)->m_bfmeFlag = false;
	}
}
