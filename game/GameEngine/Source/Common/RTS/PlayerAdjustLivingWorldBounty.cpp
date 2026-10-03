// cl: /DNDEBUG /MD /EHsc

class Rva000C97C0Player;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	bool isLivingWorld();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
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

// Retail 0x012F1028 is EA's `LivingWorldLogic *TheLivingWorldLogic`, defined
// once in game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldLogic.cpp.
// CampaignObject above is this TU's own view of that address, so the read
// casts at the use.
class LivingWorldLogic;

extern GameLogic *TheGameLogic;
extern PlayerList *ThePlayerList;
extern LivingWorldLogic *TheLivingWorldLogic;

// Retail calls both members through their ILT thunks (RVA 0x0001D1C9 and
// RVA 0x00029CBC), the bodies behind them are not recovered yet. Naming the
// thunks keeps both references resolvable at link time and reproduces retail's
// call rel32 encoding.
extern void j_0001d1c9();
extern void j_00029cbc();

static __forceinline bool bfmeIsLivingWorld(GameLogic *logic)
{
	union
	{
		void (*raw)();
		bool (GameLogic::*member)();
	} call;

	call.raw = j_0001d1c9;
	return (logic->*call.member)();
}

static __forceinline int bfmeGetBountyBonusPercent(CampaignObject *campaign)
{
	union
	{
		void (*raw)();
		int (CampaignObject::*member)();
	} call;

	call.raw = j_00029cbc;
	return (campaign->*call.member)();
}

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
	if (bfmeIsLivingWorld(TheGameLogic) && this == ThePlayerList->getLocalPlayer())
	{
		float factor = bfmeGetBountyBonusPercent((CampaignObject *)TheLivingWorldLogic) * 0.01f + 1.0f;
		return bfmeRoundFloat(static_cast<float>(ceil(static_cast<double>(bounty * factor))));
	}

	return bounty;
}
