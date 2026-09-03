// cl: /DNDEBUG /MD /EHsc

class Rva000C97C0Player;

class GameLogic
{
public:
	bool isLivingWorld();
};

class PlayerList
{
public:
	Rva000C97C0Player *getLocalPlayer() const { return m_localPlayer; }

private:
	unsigned char m_bfmeBeforeLocalPlayer[0x0c];
	Rva000C97C0Player *m_localPlayer;
};

class CampaignObject
{
public:
	int getBountyBonusPercent();
};

extern GameLogic *TheGameLogic;
extern PlayerList *ThePlayerList;
extern CampaignObject *TheLivingWorldLogic;

inline long bfmeRoundFloat(float value)
{
	long result;
	// BaseType's retail helper deliberately uses the active x87 rounding mode.
	__asm
	{
		fld value
		fistp result
	}
	return result;
}

extern "C" __declspec(dllimport) double __cdecl ceil(double value);

class Rva000C97C0Player
{
public:
	int adjustBountyForLivingWorld(int bounty);
};

int Rva000C97C0Player::adjustBountyForLivingWorld(int bounty)
{
	if (TheGameLogic->isLivingWorld() && this == ThePlayerList->getLocalPlayer())
	{
		float factor = TheLivingWorldLogic->getBountyBonusPercent() * 0.01f + 1.0f;
		return bfmeRoundFloat(static_cast<float>(ceil(static_cast<double>(bounty * factor))));
	}

	return bounty;
}
