// ?chatPlayerTooltip@Rva005307B0Owner@@QAEXVAsciiString@@@Z
// partial score=0.99 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// ?chatPlayerTooltip@Rva005307B0Owner@@QAEXVAsciiString@@@Z
// Retail 0x005307B0: 2117 bytes of code (ret 4 at +0x842) followed by the
// four-entry side switch table, 2136 bytes in the ledger.  The only caller,
// 0x005369A0, calls it through ILT 0x00002E1E with its own object in ECX
// (esi, whose +0xAC/+0xB0 it writes afterwards), so the owner keeps the
// address token.  The body builds the GameSpy chat-player tooltip from the
// literals TOOLTIP:ChatPlayerInfo / LocalPlayer / BuddyPlayer / ProfiledPlayer
// / GenericPlayer, which names the method.  It is BFME's version of the Zero
// Hour WOLGameSetupMenu playerTooltip: PlayerInfoMap find (the pinned
// map<AsciiString,PlayerInfo,AsciiComparator>::_M_find at ILT 0x00022930),
// PSPlayerStats from TheGameSpyPSMessageQueue with a PSRequest when absent,
// win/loss/favourite-side totals, and the BFME good/evil rank label.
// GameSpyInfo slot 0x48 is the PlayerInfoMap (the find above); slot 0x54 is
// the int-keyed map looked up with the profile ID before TOOLTIP:BuddyPlayer
// (Zero Hour getBuddyMap); slot 0x68 returns an AsciiString by value compared
// with the name before TOOLTIP:LocalPlayer (Zero Hour getLocalName).  Slot
// 0x4C returns the record whose +0x14 is the profile ID and +0x20/+0x24 the
// rank values; it keeps an address-derived name.
#include <map>
#include <string>
#include "ascii_string.h"
#include "Common/UnicodeString.h"
#include <string.h>
#pragma intrinsic(strlen)
#pragma intrinsic(memcmp)
// Visible out-of-line comparison (retail 0x0005FEB0, 92 B): MSVC sees that it
// cannot throw, so the local-name comparison below needs no EH state store.
template <> __declspec(noinline) inline int StringBase<char>::compare(const StringBase<char>& other) const {
    const int len = other.m_data ? other.m_data->length : 0;
    const char *data = other.m_data ? other.m_data->data : "";
    const int myLen = m_data ? m_data->length : 0;
    const char *myData = m_data ? m_data->data : "";
    int result = memcmp(myData, data, myLen<len?myLen:len);
    if (result == 0) result = myLen-len;
    return result;
}

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

template <typename T> inline StringBase<T>::~StringBase() { releaseBuffer(); }
template <typename T> inline const T *StringBase<T>::str() const {
    static const T TheNullChr = 0;
    return m_data ? m_data->data : &TheNullChr;
}
template <typename T> inline void StringBase<T>::set(const T *s) { set(s, s ? strlen((const char*)s) : 0); }
template <typename T> inline void StringBase<T>::concat(const StringBase<T>& s) {
    concat(s.m_data ? s.m_data->data : (const T*)"", s.m_data ? s.m_data->length : 0);
}
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::~StringBase(); }

typedef std::map<Int, UnsignedInt> PerGeneralMap;

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
	char m_rest[0x1c4 - 0x14c];
};

class PSRequest
{
public:
	PSRequest();
	~PSRequest();

	Int requestType;
	PSPlayerStats player;
	char m_rest[0x210 - 4 - sizeof(PSPlayerStats)];
};

class GameSpyPSMessageQueueInterface
{
public:
	virtual ~GameSpyPSMessageQueueInterface();
	virtual void startThread();
	virtual void endThread();
	virtual Bool isThreadRunning();
	virtual void addRequest(const PSRequest &request);
	virtual Bool getRequest(PSRequest &request);
	virtual void addResponse(const void *response);
	virtual Bool getResponse(void *response);
	virtual void trackPlayerStats(PSPlayerStats stats);
	virtual PSPlayerStats findPlayerStatsByID(Int profileID);
};
extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;

// Only the map instantiation is needed; the record is read through slot 0x4C.
class PlayerInfo { char m_body[4]; };
struct AsciiComparator
{
	bool operator()(const AsciiString &a, const AsciiString &b) const;
};
typedef std::map<AsciiString, PlayerInfo, AsciiComparator> PlayerInfoMap;

class BuddyInfo { char m_body[4]; };
typedef std::map<Int, BuddyInfo> BuddyInfoMap;

// The record slot 0x4C returns for a player name: +0x14 is the profile ID,
// +0x20/+0x24 are the two rank values this tooltip renders.
struct Rva005307B0PlayerRecord
{
	char m_pad00[0x14];
	Int m_profileID;
	char m_pad18[0x20 - 0x18];
	Int m_rank20;
	Int m_rank24;
};

class GameSpyInfo
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual PlayerInfoMap *getPlayerInfoMap();
    virtual Rva005307B0PlayerRecord *slot4C(const char *name);
    virtual void slot50();
    virtual BuddyInfoMap *getBuddyMap();
    virtual void slot58();
    virtual void slot5C();
    virtual void slot60();
    virtual void slot64();
    virtual AsciiString getLocalName();
};
extern GameSpyInfo *TheGameSpyInfo;

class GameTextInterface
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual UnicodeString fetch(const char *label, Bool *exists = 0);
    virtual UnicodeString fetch(AsciiString label, Bool *exists = 0);
};
extern GameTextInterface *TheGameText;

struct RGBColor;
class Mouse
{
public:
	void setCursorTooltip(UnicodeString tooltip, Int width, const RGBColor *color, Real scale);
};
extern Mouse *TheMouse;

class RankPoints
{
public:
	Int m_ranks[10];
};
extern RankPoints *TheRankPointValues;

class Gen_uw_00025c1b;
Int bfmePickBestRankSide(Gen_uw_00025c1b *stats);
Int bfmeRankPointsFromStats(Gen_uw_00025c1b *stats, Int side);
Bool Rva004D8F50(Int side);
UnicodeString Rva0052DEB0RankText(Int value);

extern const char *g_rva012B7828EvilRanks[];
extern const char *g_rva012B7800GoodRanks[];

class Rva005307B0Owner
{
public:
	void chatPlayerTooltip(AsciiString name);
};

void Rva005307B0Owner::chatPlayerTooltip(AsciiString name)
{
	if (!TheGameSpyInfo)
		return;

	UnicodeString uName;
	uName.translate(name);

	PlayerInfoMap::iterator pmIt = TheGameSpyInfo->getPlayerInfoMap()->find(name);
	if (pmIt == TheGameSpyInfo->getPlayerInfoMap()->end())
	{
		TheMouse->setCursorTooltip(uName, -1, 0, 1.5f);
		return;
	}

	Rva005307B0PlayerRecord *info = TheGameSpyInfo->slot4C(name.str());
	if (info)
	{
		Int profileID = info->m_profileID;
		PSPlayerStats stats = TheGameSpyPSMessageQueue->findPlayerStatsByID(profileID);
		if (stats.id == 0)
		{
			PSRequest req;
			req.requestType = 0;
			req.player.id = profileID;
			TheGameSpyPSMessageQueue->addRequest(req);
			TheMouse->setCursorTooltip(uName, -1, 0, 1.5f);
			return;
		}

		AsciiString localName = TheGameSpyInfo->getLocalName();
		Bool isLocalPlayer = (((StringBase<char> &)name).compare(localName) == 0);

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
		UnsignedInt numGames = 0;
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
			favoriteSide = TheGameText->fetch("APT:Gondor");
		else
		{
			AsciiString side;
			switch (favorite)
			{
			case 1:
				side.set("Gondor");
				break;
			case 3:
				side.set("Isengard");
				break;
			case 0:
				side.set("Rohan");
				break;
			case 2:
				side.set("Mordor");
				break;
			}
			AsciiString sideKey;
			sideKey.format("SIDE:%s", side.str());
			favoriteSide = TheGameText->fetch(sideKey);
		}

		Int bestSide = bfmePickBestRankSide((Gen_uw_00025c1b *)&stats);
		Int points = bfmeRankPointsFromStats((Gen_uw_00025c1b *)&stats, bestSide);
		Bool evil = Rva004D8F50(bestSide);
		Int rank = 1;
		while (rank < 10 && points >= TheRankPointValues->m_ranks[rank])
			++rank;

		AsciiString rankKey("TOOLTIP:");
		AsciiString rankLabel;
		if (evil)
			rankLabel.set(g_rva012B7828EvilRanks[rank]);
		else
			rankLabel.set(g_rva012B7800GoodRanks[rank]);
		rankKey.concat(rankLabel);

		UnicodeString rank20;
		UnicodeString rank24;
		rank20 = Rva0052DEB0RankText(info->m_rank20);
		rank24 = Rva0052DEB0RankText(info->m_rank24);

		playerInfo.format(TheGameText->fetch("TOOLTIP:ChatPlayerInfo"),
			TheGameText->fetch(localeIdentifier).str(),
			TheGameText->fetch(rankKey).str(),
			totalWins, totalLosses, favoriteSide.str(), rank20.str(), rank24.str());

		UnicodeString tooltip = UnicodeString::TheEmptyString;
		if (isLocalPlayer)
			tooltip.format(TheGameText->fetch("TOOLTIP:LocalPlayer"), uName.str());
		else if (TheGameSpyInfo->getBuddyMap()->find(profileID) != TheGameSpyInfo->getBuddyMap()->end())
			tooltip.format(TheGameText->fetch("TOOLTIP:BuddyPlayer"), uName.str());
		else if (profileID)
			tooltip.format(TheGameText->fetch("TOOLTIP:ProfiledPlayer"), uName.str());
		else
			tooltip.format(TheGameText->fetch("TOOLTIP:GenericPlayer"), uName.str());

		tooltip.concat(playerInfo);
		TheMouse->setCursorTooltip(tooltip, -1, 0, 1.0f);
		return;
	}
	TheMouse->setCursorTooltip(uName, -1, 0, 1.5f);
}
