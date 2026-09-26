// cl: /O2 /DNDEBUG /MD /EHsc- /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/stringinline
// Retail RVA 0x004FB500, 1404 bytes. WOLLobbyMenuUpdate and System call
// ILT 0x000070B3 -> this body. The full boundary ends at 0x004FBA7C.
// The canonical-string helper below also reproduces its existing 333-byte
// body at 0x004F9E60; its definition supplies MSVC's private ECX/stack ABI.
// Only PopulateLobbyPlayerListbox is newly claimed here.
// stlport
// The production WOLLobbyMenu.cpp includes the ZH PeerDefs view. This isolated
// TU keeps the BFME record and GameSpy vtable view local while preserving the
// retail function's real names and external helper ABIs.

#define _STLP_NO_EXCEPTIONS 1
#define PEER_FLAG_OP 0x20
#define NEW new

#include <map>
#include <set>

#include "string_base.h"
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef bool Bool;
typedef int Color;
typedef int GPProfile;
typedef int GPEnum;

// The shared headers carry the canonical one-pointer string layout and the
// matched StringBase declarations. These TU-local definitions keep the
// retail's visible delegations at this call site (rather than exposing a
// copied string implementation through a shared header).
inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}

inline UnicodeString::UnicodeString()
{
	m_text = 0;
}

inline UnicodeString::UnicodeString(const UnicodeString &that)
{
	((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(
		*(const StringBase<wchar_t> *)&that);
}

inline UnicodeString::~UnicodeString()
{
	((StringBase<wchar_t> *)this)->releaseBuffer();
}

inline UnicodeString &UnicodeString::operator=(const UnicodeString &that)
{
	((StringBase<wchar_t> *)this)->set(
		*(const StringBase<wchar_t> *)&that);
	return *this;
}

class PlayerInfo
{
public:
	// The BFME copy ctor at 0x004F1120 copies three strings at +0/+4/+8,
	// then ten integers from +0x0c through +0x30: this is a 52-byte record.
	AsciiString m_name;
	AsciiString m_baseName;
	AsciiString m_unusedString;
	Int m_unused0c;
	Int m_unused10;
	Int m_profileID;
	Int m_flags;
	Int m_rankPoints;
	Int m_unused20;
	Int m_unused24;
	Int m_unused28;
	Int m_side;
	Int m_unused30;

	PlayerInfo(const PlayerInfo &other);
	Bool isIgnored();
};

struct AsciiComparator
{
	Bool operator()(AsciiString first, AsciiString second) const;
};

typedef std::map<AsciiString, PlayerInfo, AsciiComparator> PlayerInfoMap;

class BuddyInfo
{
public:
	GPProfile m_id;
	AsciiString m_name;
	AsciiString m_email;
	AsciiString m_countryCode;
	GPEnum m_status;
	UnicodeString m_statusString;
	UnicodeString m_locationString;
};

typedef std::map<GPProfile, BuddyInfo> BuddyInfoMap;

class GameSpyInfoInterface
{
public:
	virtual ~GameSpyInfoInterface() {}
	virtual void slot_004();
	virtual void slot_008();
	virtual void slot_00c();
	virtual void slot_010();
	virtual void slot_014();
	virtual void slot_018();
	virtual void slot_01c();
	virtual void slot_020();
	virtual void slot_024();
	virtual void slot_028();
	virtual void slot_02c();
	virtual void slot_030();
	virtual void slot_034();
	virtual void slot_038();
	virtual void slot_03c();
	virtual void slot_040();
	virtual void playerLeftGroupRoom(AsciiString nick);
	virtual PlayerInfoMap *getPlayerInfoMap();
	virtual void slot_04c();
	virtual void slot_050();
	virtual BuddyInfoMap *getBuddyMap();
	virtual void slot_058();
	virtual void slot_05c();
	virtual void slot_060();
	virtual void slot_064();
	virtual void slot_068();
	virtual void slot_06c();
	virtual void slot_070();
	virtual void slot_074();
	virtual void slot_078();
	virtual void slot_07c();
	virtual void slot_080();
	virtual void slot_084();
	virtual void slot_088();
	virtual void slot_08c();
	virtual void slot_090();
	virtual void slot_094();
	virtual void slot_098();
	virtual void slot_09c();
	virtual void slot_0a0();
	virtual void slot_0a4();
	virtual void slot_0a8();
	virtual void slot_0ac();
	virtual void slot_0b0();
	virtual void slot_0b4();
	virtual void slot_0b8();
	virtual void slot_0bc();
	virtual void slot_0c0();
	virtual void slot_0c4();
	virtual void slot_0c8();
	virtual void slot_0cc();
	virtual void slot_0d0();
	virtual void slot_0d4();
	virtual void slot_0d8();
	virtual void slot_0dc();
	virtual void slot_0e0();
	virtual void slot_0e4();
	virtual void slot_0e8();
	virtual void slot_0ec();
	virtual void slot_0f0();
	virtual void slot_0f4();
	virtual void slot_0f8();
	virtual void slot_0fc();
	virtual void slot_100();
	virtual void slot_104();
	virtual void slot_108();
	virtual void slot_10c();
	virtual void slot_110();
	virtual void slot_114();
	virtual void slot_118();
	virtual void slot_11c();
	virtual void slot_120();
	virtual void slot_124();
	virtual void slot_128();
	virtual void slot_12c();
	virtual void slot_130();
	virtual void slot_134();
	virtual void slot_138();
	virtual void slot_13c();
	virtual void slot_140();
	virtual void slot_144();
	virtual void slot_148();
	virtual void slot_14c();
	virtual void slot_150();
	virtual void slot_154();
	virtual void slot_158();
	virtual void slot_15c();
	virtual Bool didPlayerPreorder(Int profileID) const;
};

class GameSpyConfigInterface
{
public:
	virtual ~GameSpyConfigInterface() {}
	virtual void slot_004();
	virtual void slot_008();
	virtual void slot_00c();
	virtual void slot_010();
	virtual void slot_014();
	virtual void slot_018();
	virtual void slot_01c();
	virtual void slot_020();
	virtual void slot_024();
	virtual void slot_028();
	virtual Bool isPlayerVIP(Int id);
};

class GameWindow {};

class GameWindowManager
{
public:
	virtual void slot_000();
	virtual void slot_004();
	virtual void slot_008();
	virtual void slot_00c();
	virtual void slot_010();
	virtual void slot_014();
	virtual void slot_018();
	virtual void slot_01c();
	virtual void slot_020();
	virtual void slot_024();
	virtual void slot_028();
	virtual void slot_02c();
	virtual void slot_030();
	virtual void slot_034();
	virtual void slot_038();
	virtual void slot_03c();
	virtual void slot_040();
	virtual void slot_044();
	virtual void slot_048();
	virtual void slot_04c();
	virtual void slot_050();
	virtual void slot_054();
	virtual void slot_058();
	virtual void slot_05c();
	virtual void slot_060();
	virtual void slot_064();
	virtual void slot_068();
	virtual void slot_06c();
	virtual void slot_070();
	virtual void slot_074();
	virtual void slot_078();
	virtual void slot_07c();
	virtual void slot_080();
	virtual void slot_084();
	virtual void slot_088();
	virtual void slot_08c();
	virtual void slot_090();
	virtual void slot_094();
	virtual void slot_098();
	virtual void slot_09c();
	virtual void slot_0a0();
	virtual void slot_0a4();
	virtual void slot_0a8();
	virtual void slot_0ac();
	virtual void slot_0b0();
	virtual void slot_0b4();
	virtual void slot_0b8();
	virtual void winSetLoneWindow(GameWindow *window);
};

class GameSpyInfo;
class GameSpyConfig;
extern GameSpyInfo *TheGameSpyInfo;
extern GameSpyConfig *TheGameSpyConfig;
extern GameWindowManager *TheWindowManager;
extern Color GameSpyColor[];
static GameWindow *listboxLobbyPlayers;

inline GameSpyInfoInterface *gameSpyInfoView()
{
	return reinterpret_cast<GameSpyInfoInterface *>(TheGameSpyInfo);
}

enum GameSpyColors
{
	GSCOLOR_PLAYER_NORMAL = 6,
	GSCOLOR_PLAYER_OWNER = 7,
	GSCOLOR_PLAYER_BUDDY = 8,
	GSCOLOR_PLAYER_IGNORED = 9,
};

extern Int GadgetListBoxGetNumEntries(GameWindow *listbox);
extern void GadgetListBoxGetSelected(GameWindow *listbox, Int *selectList);
extern UnicodeString GadgetListBoxGetText(GameWindow *listbox, Int row, Int column = 0);
extern Int GadgetListBoxGetTopVisibleEntry(GameWindow *listbox);
extern void GadgetListBoxReset(GameWindow *listbox);
extern void GadgetListBoxSetSelected(GameWindow *listbox, const Int *selectList, Int count = 1);
extern void GadgetListBoxSetTopVisibleEntry(GameWindow *listbox, Int topEntry);

struct BFMEPlayerInfoLayout
{
	char m_prefix[4];
	AsciiString m_baseName;
	char m_fields08[12];
	Int m_profileID;
	char m_fields18[4];
	Int m_rankPoints;
	char m_fields20[12];
	Int m_side;
};

template <typename T>
inline const T &min(const T &left, const T &right)
{
	return left < right ? left : right;
}

class Image
{
public:
	char m_prefix[0x24];
	Int m_imageWidth;
};

class MappedImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern MappedImageCollection *TheMappedImageCollection;
extern Int GadgetListBoxGetColumnWidth(GameWindow *listbox, Int column);
extern Int GadgetListBoxAddEntryImage(GameWindow *listbox, const Image *image,
	Int row, Int column, Int width, Int height, Bool overwrite, Int color);
extern Int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text,
	Int color, Int row, Int column, Bool overwrite);
extern const Image *LookupSmallRankImage(Int side, Int rankPoints);

static Int insertPlayerInListbox(const PlayerInfo &info, Color color)
{
	const BFMEPlayerInfoLayout &player =
		*reinterpret_cast<const BFMEPlayerInfoLayout *>(&info);
	UnicodeString uStr;
	uStr.translate(player.m_baseName);

	Int currentRank = player.m_rankPoints;
	Int currentSide = player.m_side;
	Bool isPreorder = gameSpyInfoView()->didPlayerPreorder(player.m_profileID);

	const Image *preorderImg;
	{
		AsciiString imageName("OfficersClubsmall");
		preorderImg = TheMappedImageCollection->findImageByName(imageName);
	}
	Int w = preorderImg ? preorderImg->m_imageWidth : 10;
	Int oldW = w;
	w = min(GadgetListBoxGetColumnWidth(listboxLobbyPlayers, 0), oldW);
	Int h = w;
	if (!isPreorder)
		preorderImg = 0;

	const Image *rankImg = LookupSmallRankImage(currentSide, currentRank);
	Int index = GadgetListBoxAddEntryImage(
		listboxLobbyPlayers, preorderImg, -1, 0, w, h, true, -1);
	GadgetListBoxAddEntryImage(
		listboxLobbyPlayers, rankImg, index, 1, w, h, true, -1);
	GadgetListBoxAddEntryText(
		listboxLobbyPlayers, uStr, color, index, 2, true);
	return index;
}

#define DEBUG_LOG(x) {}

void PopulateLobbyPlayerListbox(void)
{
	if (!listboxLobbyPlayers)
		return;

	PlayerInfoMap *players = gameSpyInfoView()->getPlayerInfoMap();
	PlayerInfoMap::iterator it;
	BuddyInfoMap *buddies = gameSpyInfoView()->getBuddyMap();
	BuddyInfoMap::iterator bIt;
	Int maxSelectedItems = GadgetListBoxGetNumEntries(listboxLobbyPlayers);
		Int *selectedIndices;
		GadgetListBoxGetSelected(listboxLobbyPlayers, (Int *)(&selectedIndices));
		std::set<AsciiString> selectedNames;
		std::set<AsciiString>::const_iterator selIt;
		std::set<Int> indicesToSelect;
		UnicodeString uStr;
		Int numSelected = 0;
		for (Int i=0; i<maxSelectedItems; ++i)
		{
			if (selectedIndices[i] < 0)
				break;
			++numSelected;
			AsciiString selectedName;
			uStr = GadgetListBoxGetText(listboxLobbyPlayers, selectedIndices[i], 2);
			selectedName.translate(uStr);
			selectedNames.insert(selectedName);
			DEBUG_LOG(("Saving off old selection %d (%s)\n", selectedIndices[i], selectedName.str()));
		}

		Int previousTopIndex = GadgetListBoxGetTopVisibleEntry(listboxLobbyPlayers);
		GadgetListBoxReset(listboxLobbyPlayers);

		for (it = players->begin(); it != players->end(); ++it)
		{
			PlayerInfo info = it->second;
			if (info.m_flags & PEER_FLAG_OP || reinterpret_cast<GameSpyConfigInterface *>(TheGameSpyConfig)->isPlayerVIP(info.m_profileID))
			{
				Int index = insertPlayerInListbox(info, info.isIgnored() ? GameSpyColor[GSCOLOR_PLAYER_IGNORED] : GameSpyColor[GSCOLOR_PLAYER_OWNER]);
				// The helper and retail lookup both use the +4 display/base-name string.
				selIt = selectedNames.find(info.m_baseName);
				if (selIt != selectedNames.end())
					indicesToSelect.insert(index);
			}
		}

		for (it = players->begin(); it != players->end(); ++it)
		{
			PlayerInfo info = it->second;
			bIt = buddies->find(info.m_profileID);
			if (!(info.m_flags & PEER_FLAG_OP || reinterpret_cast<GameSpyConfigInterface *>(TheGameSpyConfig)->isPlayerVIP(info.m_profileID)) && bIt != buddies->end())
			{
				Int index = insertPlayerInListbox(info, info.isIgnored() ? GameSpyColor[GSCOLOR_PLAYER_IGNORED] : GameSpyColor[GSCOLOR_PLAYER_BUDDY]);
				selIt = selectedNames.find(info.m_baseName);
				if (selIt != selectedNames.end())
					indicesToSelect.insert(index);
			}
		}

		for (it = players->begin(); it != players->end(); ++it)
		{
			PlayerInfo info = it->second;
			bIt = buddies->find(info.m_profileID);
			if (!(info.m_flags & PEER_FLAG_OP || reinterpret_cast<GameSpyConfigInterface *>(TheGameSpyConfig)->isPlayerVIP(info.m_profileID)) && bIt == buddies->end())
			{
				Int index = insertPlayerInListbox(info, info.isIgnored() ? GameSpyColor[GSCOLOR_PLAYER_IGNORED] : GameSpyColor[GSCOLOR_PLAYER_NORMAL]);
				selIt = selectedNames.find(info.m_baseName);
				if (selIt != selectedNames.end())
					indicesToSelect.insert(index);
			}
		}

		if (indicesToSelect.size())
		{
			std::set<Int>::const_iterator indexIt;
			Int *newIndices = NEW Int[indicesToSelect.size()];
			for (i=0, indexIt = indicesToSelect.begin(); indexIt != indicesToSelect.end(); ++i, ++indexIt)
				newIndices[i] = *indexIt;
			GadgetListBoxSetSelected(listboxLobbyPlayers, newIndices, indicesToSelect.size());
			delete[] newIndices;
		}

		if (indicesToSelect.size() != numSelected)
			TheWindowManager->winSetLoneWindow(NULL);

	GadgetListBoxSetTopVisibleEntry(listboxLobbyPlayers, previousTopIndex);
}
