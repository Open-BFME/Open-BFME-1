// ?Rva005337E0@BfmeAptScreenOnlineChat@@QAEXXZ
// partial score=0.72 date=2026-09-17
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail RVA 0x005337E0, 1382 bytes.  The ILT caller in OnlineChat's
// InitGadgets path proves the address-derived member name below.  The body
// rebuilds the player-list refresh: preserve selected display names, classify
// the player map, sort twelve-byte records, refill the list, and restore the
// selection/top entry.

#include <algorithm>
#include <map>
#include <vector>

#include "ascii_string.h"
#include "string_base.h"

typedef int Int;
typedef bool Bool;
typedef int Color;
typedef int GPProfile;
typedef int GPEnum;

class GameWindow {};

// Retail's UnicodeString is the thin StringBase<unsigned short> wrapper.  A
// local view is required here: the shared convenience header exposes the
// wrapper's out-of-line copy/destructor symbols, while this body calls the
// inherited StringBase copy/release operations directly.
class UnicodeString
{
public:
	UnicodeString()
	{
		m_text = 0;
	}
	UnicodeString(const UnicodeString &other)
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&other);
	}
	~UnicodeString()
	{
		((StringBase<unsigned short> *)this)->releaseBuffer();
	}

	void translate(const AsciiString &other);
	int compareNoCase(const UnicodeString &other) const
	{
		return ((const StringBase<unsigned short> *)this)->compareNoCase(
			*(const StringBase<unsigned short> *)&other);
	}

	private:
	unsigned short *m_text;
};

// These are the BFME record layouts witnessed by the PlayerInfo map and the
// matched PlayerInfo::isIgnored body.  The map stores its value at node+0x14.
class PlayerInfo
{
public:
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
extern GameSpyConfigInterface *TheGameSpyConfig;
extern GameWindowManager *TheWindowManager;
extern Color GameSpyColor[];

extern Int GadgetListBoxGetNumEntries(GameWindow *listbox);
extern void GadgetListBoxGetSelected(GameWindow *listbox, Int *selectList);
extern UnicodeString GadgetListBoxGetText(GameWindow *listbox, Int row, Int column);
extern Int GadgetListBoxGetTopVisibleEntry(GameWindow *listbox);
extern void GadgetListBoxReset(GameWindow *listbox);
extern void GadgetListBoxSetSelected(GameWindow *listbox, const Int *selectList,
	Int count);
extern void GadgetListBoxSetTopVisibleEntry(GameWindow *listbox, Int topEntry);

// The queue and request names are the address-derived declarations already
// used by BfmeConv1990.  Its addRequest slot is +0x10; the persistent-stats
// lookup is the same object's +0x24 slot.
class PSPlayerStats
{
public:
	~PSPlayerStats();

	Int id;
	unsigned char m_unmodelled[0x1c0];
};

class BfmeReqEUG
{
public:
	BfmeReqEUG();
	~BfmeReqEUG();

	Int m_bfmeKindEUG;
	unsigned char m_bfmeBodyEUG[0x20c];
};

class BfmeQueueEUG
{
public:
	virtual void bfmeSlot0EUG();
	virtual void bfmeSlot1EUG();
	virtual void bfmeSlot2EUG();
	virtual void bfmeSlot3EUG();
	virtual void bfmeAddEUG(BfmeReqEUG *req);
	virtual void bfmeSlot5EUG();
	virtual void bfmeSlot6EUG();
	virtual void bfmeSlot7EUG();
	virtual void bfmeSlot8EUG();
	virtual PSPlayerStats findPlayerStatsByID(Int id);
};

extern BfmeQueueEUG *g_bfmeQueueEUG;

// The sort family is independently matched at these addresses.  The
// comparator's state dword is unused by the proven comparator body.
struct S4Named0052E880
{
	Int m_bfmeUnused;
	StringBase<char> m_bfmeName;
};

struct S4SortElem12
{
	S4Named0052E880 *m_bfmeObj;
	Int m_bfmeKey;
	Int m_bfmeThird;

	Bool BfmeLess0052E880(const S4SortElem12 &other) const;
};

struct S4Cmp00531FA0
{
	void *m_bfmeState;
	Bool operator()(S4SortElem12 left, S4SortElem12 right) const;
};

// The target inlines STLport's sort driver but reaches the already-landed
// helper bodies through their retail ILT thunks.  Variadic declarations keep
// the exact dword-push ABI without inventing a semantic callee name.
extern void Rva005337E0Intro(void *, ...);
extern void Rva005337E0Insertion(void *, ...);
extern void Rva005337E0Unguarded(void *, ...);

#pragma comment(linker, "/alternatename:?Rva005337E0Intro@@YAXPAXZZ=?j_00025b03@@YAXXZ")
#pragma comment(linker, "/alternatename:?Rva005337E0Insertion@@YAXPAXZZ=?j_000118d8@@YAXXZ")
#pragma comment(linker, "/alternatename:?Rva005337E0Unguarded@@YAXPAXZZ=?j_0002ec80@@YAXXZ")

extern Int Rva005337E0AddPlayer(void *, ...);
#pragma comment(linker, "/alternatename:?Rva005337E0AddPlayer@@YAHPAXZZ=?j_00019141@@YAXXZ")

inline Bool operator==(const UnicodeString &left, const UnicodeString &right)
{
	return left.compareNoCase(right) == 0;
}

class BfmeAptScreenOnlineChat
{
public:
	void Rva005337E0();

private:
	unsigned char m_unmodelled000[0x40];
	GameWindow *m_playersList;
};

void BfmeAptScreenOnlineChat::Rva005337E0()
{
	if (m_playersList == 0)
		return;

	if (TheGameSpyInfo == 0)
		return;

	PlayerInfoMap *players =
		reinterpret_cast<GameSpyInfoInterface *>(TheGameSpyInfo)->getPlayerInfoMap();
	PlayerInfoMap::iterator it;
	BuddyInfoMap &buddies =
		*reinterpret_cast<GameSpyInfoInterface *>(TheGameSpyInfo)->getBuddyMap();
	Int maxSelectedItems;
	maxSelectedItems = GadgetListBoxGetNumEntries(m_playersList);
	Int *selectedIndices;
	GadgetListBoxGetSelected(m_playersList, (Int *)(&selectedIndices));

	std::vector<S4SortElem12> records;
	std::vector<Int> indicesToSelect;
	std::vector<UnicodeString> selectedNames;
	Int numSelected = 0;
	Int i;

	for (i = 0;
		i < maxSelectedItems && selectedIndices[i] >= 0; ++i)
	{
		++numSelected;
		UnicodeString selectedName =
			GadgetListBoxGetText(m_playersList, selectedIndices[i], 2);
		selectedNames.push_back(selectedName);
	}

	Int previousTopIndex = GadgetListBoxGetTopVisibleEntry(m_playersList);
	GadgetListBoxReset(m_playersList);

	for (it = players->begin(); it != players->end(); ++it)
	{
		PlayerInfo *info = &it->second;
		Int key;
		Int color;

		if (info->m_flags & 0x20)
		{
			key = 1000;
			color = 7;
		}
		else if (TheGameSpyConfig->isPlayerVIP(info->m_profileID))
		{
			key = 1000;
			color = 7;
		}
		else
		{
			BuddyInfoMap::iterator bIt = buddies.find(info->m_profileID);
			if (bIt != buddies.end())
			{
				key = 500;
				color = 8;
			}
			else
			{
				key = 0;
				color = 6;
			}
		}

		if (info->isIgnored())
		{
			key -= 1001;
			color = 11;
		}

		if (info->m_profileID != 0)
		{
			if (g_bfmeQueueEUG->findPlayerStatsByID(info->m_profileID).id == 0)
			{
				BfmeReqEUG request;
				request.m_bfmeKindEUG = 0;
				*reinterpret_cast<Int *>(request.m_bfmeBodyEUG) =
					info->m_profileID;
				g_bfmeQueueEUG->bfmeAddEUG(&request);
			}
		}

		S4SortElem12 record;
		record.m_bfmeObj = reinterpret_cast<S4Named0052E880 *>(info);
		record.m_bfmeKey = key;
		record.m_bfmeThird = color;
		records.push_back(record);
	}

	S4Cmp00531FA0 comparator;
	std::sort(records.begin(), records.end(), comparator);

	for (std::vector<S4SortElem12>::iterator it = records.begin();
		it != records.end(); ++it)
	{
		S4SortElem12 *record = &*it;
		Int index = Rva005337E0AddPlayer(m_playersList,
			reinterpret_cast<PlayerInfo *>(record->m_bfmeObj),
			GameSpyColor[record->m_bfmeThird]);

		UnicodeString name;
		name.translate(reinterpret_cast<PlayerInfo *>(record->m_bfmeObj)->m_baseName);
		if (std::find(selectedNames.begin(), selectedNames.end(), name) !=
			selectedNames.end())
		{
			indicesToSelect.push_back(index);
		}
	}

	Int selectedCount = (Int)indicesToSelect.size();
	if (selectedCount != 0)
	{
		Int *newIndices = new Int[selectedCount];
		for (i = 0; i < selectedCount; ++i)
			newIndices[i] = indicesToSelect[i];
		GadgetListBoxSetSelected(m_playersList, newIndices, selectedCount);
		delete[] newIndices;
	}

	if (selectedCount != numSelected)
		TheWindowManager->winSetLoneWindow(0);

	GadgetListBoxSetTopVisibleEntry(m_playersList, previousTopIndex);
}
