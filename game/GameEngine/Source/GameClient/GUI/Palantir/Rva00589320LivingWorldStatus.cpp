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

// 0x000DF860 via ILT 0x0000762B, matched as BfmeThingRV::bfmePickRV
// (BfmeThreeHundredTwentyFour.cpp).
class BfmeMemberRV;
class BfmeThingRV
{
public:
	BfmeMemberRV *bfmePickRV();
};

class PlayerList;

// Retail 0x012F1028 is EA's TheLivingWorldLogic (data_rows.csv owns
// ?TheLivingWorldLogic@@3PAVLivingWorldLogic@@A, LivingWorldLogic.cpp); the
// Glo012F1028 spelling is only a pin nothing defines.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#define Glo012F1028 ( reinterpret_cast<Glo012F1028Type *>( TheLivingWorldLogic ) )
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
		(Rva00589320Player *)((BfmeThingRV *)ThePlayerList)->bfmePickRV();
	if (!player)
		return 1;

	player = *(Rva00589320Player **)((char *)player + 4);
	if (!player)
		return 1;

	return player->m_active ? 3 : 1;
}

// Retail 0x005893C0 (69 B): file-static progress percentage of owner+0x25C between the
// integer bounds at +0x26C and +0x268, clamped to 1..100 (1 for an empty range). The
// owner arrives in EAX through MSVC's private static convention; types are address-named.
class Rva005893C0Owner
{
public:
	unsigned char m_unmodelled000[0x25c];
	float m_value25c;
	unsigned char m_unmodelled260[8];
	int m_end268;
	int m_start26c;
};

static int rva005893C0(const Rva005893C0Owner *owner)
{
	int start = owner->m_start26c;
	int range = owner->m_end268 - start;
	if (range == 0)
		return 1;
	int percent = (int)(owner->m_value25c - start) * 100 / range;
	if (percent < 1)
		return 1;
	if (percent > 100)
		return 100;
	return percent;
}

// absent-from-retail: TU-local caller that keeps the static above alive.
int rva005893C0Caller(const Rva005893C0Owner *owner)
{
	return rva005893C0(owner);
}
