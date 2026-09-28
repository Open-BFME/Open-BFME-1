// ?Rva0053AF50PlayerTooltip@@YGXPAVGameSpyGameSlot@@@Z
// partial score=0.982039 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/psplayerstats /Iinputs/reference/shims/nat /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include <string>
#include <map>
#include <string.h>
#include "ascii_string.h"
#include "Common/UnicodeString.h"

template<> inline const char *StringBase<char>::str() const
{ return m_data ? &m_data->data[0] : ""; }

template<> inline const wchar_t *StringBase<wchar_t>::str() const
{ return m_data ? &m_data->data[0] : L""; }

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

class RGBColor;

class RetailLayoutString : public AsciiString
{
public:
	void set(const char *, Int);
	void concat(const char *, Int);
};

class BFMERetailAsciiString : public RetailLayoutString
{
public:
	BFMERetailAsciiString(const char *);
	~BFMERetailAsciiString() {}

private:
	void releaseBuffer();
};

class GameSlot
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual GameSlot *rva004FA1A0Self() const = 0;
	Bool isHuman() const;
	UnicodeString getName() const;
};

class GameSpyGameSlot : public GameSlot
{
public:
	Int getPingAsInt() const
	{
		return *(const Int *)((const char *)rva004FA1A0Self() + 0x54);
	}
};

class GameSpyStagingRoom
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void startGame(Int) = 0;
	virtual void slot10() = 0;
	virtual Int getLocalSlotNum() const = 0;
	GameSpyGameSlot *getGameSpySlot(Int);
};

struct Rva0053AF50PlayerInfo
{
	char m_prefix[0x14];
	Int m_profileID;
	char m_gap18[8];
	Int m_rank1;
	Int m_rank2;
};

typedef _STL::map<Int, unsigned char> BuddyInfoMap;

class GameSpyInfo
{
public:
	virtual void slot000() = 0; virtual void slot004() = 0;
	virtual void slot008() = 0; virtual void slot00C() = 0;
	virtual void slot010() = 0; virtual void slot014() = 0;
	virtual void slot018() = 0; virtual void slot01C() = 0;
	virtual void slot020() = 0; virtual void slot024() = 0;
	virtual void slot028() = 0; virtual void slot02C() = 0;
	virtual void slot030() = 0; virtual void slot034() = 0;
	virtual void slot038() = 0; virtual void slot03C() = 0;
	virtual void slot040() = 0; virtual void slot044() = 0;
	virtual void slot048() = 0;
	virtual Rva0053AF50PlayerInfo *findPlayerInfo(const char *) = 0;
	virtual void slot050() = 0;
	virtual BuddyInfoMap *getBuddyMap() = 0;
	virtual void slot058() = 0; virtual void slot05C() = 0;
	virtual void slot060() = 0; virtual void slot064() = 0;
	virtual void slot068() = 0; virtual void slot06C() = 0;
	virtual void slot070() = 0; virtual void slot074() = 0;
	virtual void slot078() = 0; virtual void slot07C() = 0;
	virtual void slot080() = 0; virtual void slot084() = 0;
	virtual void slot088() = 0; virtual void slot08C() = 0;
	virtual void slot090() = 0; virtual void slot094() = 0;
	virtual void slot098() = 0; virtual void slot09C() = 0;
	virtual void slot0A0() = 0; virtual void slot0A4() = 0;
	virtual void slot0A8() = 0; virtual void slot0AC() = 0;
	virtual void slot0B0() = 0; virtual void slot0B4() = 0;
	virtual void slot0B8() = 0; virtual void slot0BC() = 0;
	virtual void slot0C0() = 0;
	virtual GameSpyStagingRoom *getCurrentStagingRoom() = 0;
};

class PSPlayerStats;

class GameSpyPSMessageQueueInterface
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual PSPlayerStats findPlayerStatsByID(Int id) = 0;
};

class GameTextInterface
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual UnicodeString fetch(const char *, bool *exists = 0) = 0;
	virtual UnicodeString fetch(AsciiString, bool *exists = 0) = 0;
};

class Mouse
{
public:
	void setCursorTooltip(UnicodeString tooltip, Int delay,
		const RGBColor *color, Real width);
};

typedef _STL::map<Int, UnsignedInt> PerGeneralMap;

class PSPlayerStats
{
public:
	PSPlayerStats();
	PSPlayerStats(const PSPlayerStats &other);
	~PSPlayerStats();

	Int id;
	PerGeneralMap wins;
	PerGeneralMap losses;
	PerGeneralMap map1c;
	PerGeneralMap map28;
	PerGeneralMap map34;
	PerGeneralMap map40;
	PerGeneralMap games;
	PerGeneralMap map58;
	PerGeneralMap map64;
	PerGeneralMap map70;
	PerGeneralMap map7c;
	PerGeneralMap map88;
	PerGeneralMap map94;
	PerGeneralMap mapa0;
	PerGeneralMap mapac;
	PerGeneralMap discons;
	PerGeneralMap desyncs;
	PerGeneralMap mapd0;
	PerGeneralMap mapdc;
	PerGeneralMap mape8;
	PerGeneralMap mapf4;
	PerGeneralMap map100;
	PerGeneralMap map10c;
	PerGeneralMap map118;
	PerGeneralMap map124;
	PerGeneralMap map130;
	PerGeneralMap map13c;
	Int locale;
	std::string dateCreated;
	Int gamesAsRandom;
	std::string options;
	std::string systemSpec;
	Real lastFPS;
	Int lastGeneral;
	Int gamesInRowWithLastGeneral;
	Int builtParticleCannon;
	Int builtNuke;
	Int builtSCUD;
	Int challengeMedals;
	Int battleHonors;
	Int winsInARow;
	Int maxWinsInARow;
	Int lossesInARow;
	Int maxLossesInARow;
	Int disconsInARow;
	Int maxDisconsInARow;
	Int desyncsInARow;
	Int maxDesyncsInARow;
	Int lastLadderPort;
	std::string lastLadderHost;
};

typedef char Rva0053AF50StatsSize[sizeof(PSPlayerStats) == 0x1c4 ? 1 : -1];

class Gen_uw_00025c1b;
int bfmePickBestRankSide(Gen_uw_00025c1b *stats);
int bfmeRankPointsFromStats(Gen_uw_00025c1b *stats, int side);
bool Rva004D8F50(int state);
UnicodeString formatLadderRankText(int rank);

extern GameSpyInfo *TheGameSpyInfo;
extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;
class BfmeQueueEUG;
extern BfmeQueueEUG *g_bfmeQueueEUG;
extern GameTextInterface *TheGameText;
extern Mouse *TheMouse;
extern int *g_bfmeLimitsDF;

void __stdcall Rva0053AF50PlayerTooltip(GameSpyGameSlot *slot)
{
	if (!TheGameSpyInfo)
		return;
	GameSpyStagingRoom *game = TheGameSpyInfo->getCurrentStagingRoom();
	if (!game)
		return;
	if (!slot->rva004FA1A0Self())
		return;
	if (!slot->isHuman())
	{
		TheMouse->setCursorTooltip(UnicodeString::TheEmptyString, -1, NULL, 1.0f);
		return;
	}

	UnicodeString uName = slot->getName();
	AsciiString aName;
	aName.translate(uName);
	Rva0053AF50PlayerInfo *player = TheGameSpyInfo->findPlayerInfo(aName.str());
	if (player)
	{
	Int profileID = player->m_profileID;
	PSPlayerStats stats = reinterpret_cast<GameSpyPSMessageQueueInterface *>(g_bfmeQueueEUG)->findPlayerStatsByID(profileID);
	if (stats.id == 0)
	{
		TheMouse->setCursorTooltip(uName, -1, NULL, 1.5f);
		return;
	}

	Bool isLocalPlayer = slot == game->getGameSpySlot(game->getLocalSlotNum());
	AsciiString localeIdentifier;
	localeIdentifier.format("WOL:Locale%2.2d", stats.locale);
	UnicodeString playerInfo;
	Int totalWins = 0, totalLosses = 0;
	PerGeneralMap::iterator it;
	for (it = stats.wins.begin(); it != stats.wins.end(); ++it)
		totalWins += it->second;
	for (it = stats.losses.begin(); it != stats.losses.end(); ++it)
		totalLosses += it->second;

	UnicodeString favoriteSide;
	Int numGames = 0;
	Int favorite = 0;
	for (it = stats.games.begin(); it != stats.games.end(); ++it)
	{
		if (it->second > numGames)
		{
			numGames = it->second;
			favorite = it->first;
		}
	}
	if (numGames == 0)
		favoriteSide = TheGameText->fetch("GUI:None");
	else
	{
		AsciiString sideName;
		switch (favorite)
		{
		case 0: sideName = "Gondor"; break;
		case 1: sideName = "Rohan"; break;
		case 2: sideName = "Isengard"; break;
		case 3: sideName = "Mordor"; break;
		}
		AsciiString sideKey;
		sideKey.format("SIDE:%s", sideName.str());
		favoriteSide = TheGameText->fetch(sideKey);
	}

	int bestSide = bfmePickBestRankSide((Gen_uw_00025c1b *)&stats);
	int rankPoints = bfmeRankPointsFromStats((Gen_uw_00025c1b *)&stats, bestSide);
	Bool evil = Rva004D8F50(bestSide);
	Int rank = 1;
	while (rank < 10 && rankPoints >= g_bfmeLimitsDF[rank])
		++rank;
	AsciiString rankKey("TOOLTIP:");
	AsciiString rankName;
	if (evil)
		{ const char *name = ((const char *const *)0x012B7888)[rank]; ((StringBase<char> *)&rankName)->set(name, name ? strlen(name) : 0); }
	else
		{ const char *name = ((const char *const *)0x012B7860)[rank]; ((StringBase<char> *)&rankName)->set(name, name ? strlen(name) : 0); }
	((StringBase<char> *)&rankKey)->concat(rankName.str(), *(char **)&rankName ? *(unsigned short *)(*(char **)&rankName + 4) : 0);
	UnicodeString ladder1, ladder2;
	ladder1 = formatLadderRankText(player->m_rank1);
	ladder2 = formatLadderRankText(player->m_rank2);

	playerInfo.format(TheGameText->fetch("TOOLTIP:StagingPlayerInfo"),
		TheGameText->fetch(rankKey).str(), TheGameText->fetch(localeIdentifier).str(),
		slot->getPingAsInt(), totalWins, totalLosses, favoriteSide.str(), ladder1.str(), ladder2.str());

	UnicodeString tooltip = UnicodeString::TheEmptyString;
	if (isLocalPlayer)
		tooltip.format(TheGameText->fetch("TOOLTIP:LocalPlayer"), uName.str());
	else if (TheGameSpyInfo->getBuddyMap()->find(profileID) !=
		TheGameSpyInfo->getBuddyMap()->end())
		tooltip.format(TheGameText->fetch("TOOLTIP:BuddyPlayer"), uName.str());
	else if (profileID)
		tooltip.format(TheGameText->fetch("TOOLTIP:ProfiledPlayer"), uName.str());
	else
		tooltip.format(TheGameText->fetch("TOOLTIP:GenericPlayer"), uName.str());

	tooltip.concat(playerInfo);
	TheMouse->setCursorTooltip(tooltip, -1, NULL, 1.0f);
	}
	else
	{
		TheMouse->setCursorTooltip(uName, -1, NULL, 1.5f);
	}
}
