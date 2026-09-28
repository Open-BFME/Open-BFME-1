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

class Rva002EE330PlayerList
{
public:
	Rva00589320Player *getLocalPlayer();
};

extern Glo012F1028Type *Glo012F1028;
extern BfmeLivingWorldCampaignManager *TheLivingWorldCampaignManager;
extern GameLogic *TheBfmeGameLogic;
extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

int Rva00589320(void)
{
	Glo012F1028Type *campaign = Glo012F1028;
	if (campaign && campaign->m_campaignLoaded && campaign->m_campaignActive)
	{
		int flag = TheLivingWorldCampaignManager->m_campaignFlag != 0;
		return flag + flag + 2;
	}

	GameLogic *logic = TheBfmeGameLogic;
	if (!logic)
		return 1;

	int mode = logic->m_gameMode;
	if (mode == 8 || mode == 4)
		return 1;

	Rva00589320Player *player = Rva002EE330ThePlayers->getLocalPlayer();
	if (!player)
		return 1;

	player = *(Rva00589320Player **)((char *)player + 4);
	if (!player)
		return 1;

	return player->m_active ? 3 : 1;
}
