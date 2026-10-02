// cl: /DNDEBUG /MD /EHsc
// Retail 0x00589320 returns the active Living World status code.

class Glo012F1028Type
{
public:
	char m_pad00[0x2c];
	unsigned char m_campaignLoaded;
	unsigned char m_campaignActive;
};

class BfmeLivingWorldCampaignManager
{
public:
	char m_pad00[0x1c];
	unsigned char m_campaignFlag;
};

class GameLogic
{
public:
	char m_pad00[0x10c];
	int m_gameMode;
};

class Rva00589320Player
{
public:
	char m_pad00[4];
	void *m_playerData;
	char m_pad08[0x110];
	unsigned char m_active;
};

// Rva002EE330PlayerList is this TU's view of retail's player-list global at
// 0x012ED748.  The global itself carries its canonical spelling, so this TU
// links against game/GameEngine/Source/Common/RTS/PlayerList.cpp's definition.
class Rva002EE330PlayerList
{
public:
	Rva00589320Player *getLocalPlayer();
};

class PlayerList;

extern Glo012F1028Type *Glo012F1028;
// Retail's global at 0x012F1024 is EA's LivingWorldCampaignManager singleton,
// defined once in GameEngine/Source/GameLogic/LivingWorld/
// LivingWorldCampaignManager.cpp, so this reference carries that canonical type
// (class, not struct); the local view above is cast in at the one use.
class LivingWorldCampaignManager;

extern LivingWorldCampaignManager *TheLivingWorldCampaignManager;
extern GameLogic *TheGameLogic;
extern PlayerList *ThePlayerList;

int Rva00589320(void)
{
	Glo012F1028Type *campaign = Glo012F1028;
	if (campaign && campaign->m_campaignLoaded && campaign->m_campaignActive)
	{
		int flag = ((BfmeLivingWorldCampaignManager *)TheLivingWorldCampaignManager)->m_campaignFlag != 0;
		return flag + flag + 2;
	}

	GameLogic *logic = TheGameLogic;
	if (!logic)
		return 1;

	int mode = logic->m_gameMode;
	if (mode == 8 || mode == 4)
		return 1;

	Rva00589320Player *player =
		((Rva002EE330PlayerList *)ThePlayerList)->getLocalPlayer();
	if (!player)
		return 1;

	player = *(Rva00589320Player **)((char *)player + 4);
	if (!player)
		return 1;

	return player->m_active ? 3 : 1;
}
