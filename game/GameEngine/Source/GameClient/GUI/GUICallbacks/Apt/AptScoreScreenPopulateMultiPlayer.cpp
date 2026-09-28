// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// BfmeAptScreenScoreScreen::_bfme_populateMultiPlayer, retail 0x005770E0 (708 B).
//
// Identity: the pinned name (symbols.csv) is called through ILT 0x0001B626 by
// the matched _bfme_showScoreScreen (AptScoreScreen.cpp), which passes the
// score-screen type. No Zero Hour twin. The body stores the type at +0x25C,
// collects one entry per occupied slot whose player (found by the slot's
// +0x2C name key) is not an observer, gives each its own score and its score
// summed with every mutual ally's, sorts them with the matched
// BfmeScoreEntry sort helpers, then adds one table row per entry through the
// matched row helper 0x00576C20 and marks a team break (+0x270) wherever the
// alliance changes.
//
// Shape notes, measured against retail: the vector's reserve (0x005737F0)
// and push_back (0x00574CD0) bodies stay visible here, so MSVC knows the
// vector never escapes and keeps its bounds in registers across the scoring
// loops; std::sort is expanded in place as an inline function so its empty
// comparator takes the dead name slot; row is declared before previous.

#include <vector>
#include <string.h>
#include "string_base.h"

typedef bool Bool;
typedef int Int;

// The narrow string this body copies out of a game slot. Retail inlines the
// emptiness test and the destructor (a direct call to the private
// releaseBuffer, 0x00887940); the copy constructor (0x00887B60) stays out of
// line. Only the members this body reaches are declared.
template <>
class StringBase<char>
{
	friend class AsciiString;

	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

public:
	Bool isNotEmpty() const { return m_data != 0 && m_data->length != 0; }
	const char *str() const { return m_data ? &m_data->data[0] : ""; }

private:
	StringBase(const StringBase<char> &src);
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();

	Header *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const AsciiString &that) : StringBase<char>(that) {}
	~AsciiString() {}
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Team;

class GameSlot
{
public:
	Bool isOccupied() const;
	// The string the score screen turns into a player name key.
	const AsciiString &getInternalPlayerName() const { return m_internalPlayerName; }

private:
	unsigned char m_unmodelled00[0x2C];
	AsciiString m_internalPlayerName;									///< +0x2C
};

class GameInfo
{
public:
	GameSlot *getSlot(Int slot);
};

class ScoreKeeper
{
public:
	Int calculateScore();
};

class Player
{
public:
	Bool isPlayerObserver() const;
	Relationship getRelationship(const Team *that) const;
	Team *getTeam230() const { return m_team230; }
	ScoreKeeper *getScoreKeeper() { return (ScoreKeeper *)((char *)this + 0x348); }

private:
	unsigned char m_unmodelled00[0x230];
	Team *m_team230;										///< +0x230
};

class PlayerList
{
public:
	Player *findPlayerWithNameKey(NameKeyType key);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern GameInfo *TheGameInfo;
extern PlayerList *ThePlayerList;
extern NameKeyGenerator *TheNameKeyGenerator;

// One score-screen row: the slot, its player, the player's score summed with
// every mutual ally's, and the player's own score.
struct BfmeScoreEntry
{
	GameSlot *m_slot;
	Player *m_player;
	Int m_teamScore;
	Int m_score;
};

struct BfmeScoreEntryLess
{
	bool operator()(const BfmeScoreEntry *left, const BfmeScoreEntry *right) const;
};

// The out-of-line STLport pieces of vector<BfmeScoreEntry> and of the sort.

void Gen00575450(BfmeScoreEntry *first, BfmeScoreEntry *last,
	BfmeScoreEntry *tag, int depthLimit, BfmeScoreEntryLess comp);
void Rva005742C0(BfmeScoreEntry *first, BfmeScoreEntry *last, BfmeScoreEntryLess comp);
void Rva00571AB0(BfmeScoreEntry *first, BfmeScoreEntry *last, BfmeScoreEntry *tag,
	BfmeScoreEntryLess comp);

// STLport __lg.
static inline Int lg00577E0(Int n)
{
	Int k;
	for (k = 0; n != 1; n >>= 1)
		++k;
	return k;
}

// STLport sort<BfmeScoreEntry *, BfmeScoreEntryLess>, expanded in place.
static inline void sort005770E0(BfmeScoreEntry *first, BfmeScoreEntry *last,
	BfmeScoreEntryLess comp)
{
	if (first != last)
	{
		Gen00575450(first, last, (BfmeScoreEntry *)0, lg00577E0(last - first) * 2, comp);
		if (last - first > 16)
		{
			Rva005742C0(first, first + 16, comp);
			Rva00571AB0(first + 16, last, (BfmeScoreEntry *)0, comp);
		}
		else
			Rva005742C0(first, last, comp);
	}
}

class BfmeAptScreenScoreScreen
{
public:
	void _bfme_populateMultiPlayer(Int type);
	void Rva00576C20(Player *player, GameSlot *slot, Int row);

private:
	char m_unmodelled_prefix[0x25C];
	Int m_gameType;											///< +0x25C
	char m_unmodelled_middle[0x10];
	Bool m_teamBreak[8];									///< +0x270
};

// ?_bfme_populateMultiPlayer@BfmeAptScreenScoreScreen@@QAEXH@Z
void BfmeAptScreenScoreScreen::_bfme_populateMultiPlayer(Int type)
{
	m_gameType = type;

	_STL::vector<BfmeScoreEntry> entries;
	entries.reserve(8);
	for (Int i = 0; i < 8; ++i)
	{
		GameSlot *slot = TheGameInfo->getSlot(i);
		if (slot->isOccupied())
		{
			AsciiString name = slot->getInternalPlayerName();
			if (name.isNotEmpty())
			{
				Player *player = ThePlayerList->findPlayerWithNameKey(
					TheNameKeyGenerator->nameToKey(name.str()));
				if (player && !player->isPlayerObserver())
				{
					BfmeScoreEntry entry;
					entry.m_slot = slot;
					entry.m_player = player;
					entry.m_teamScore = 0;
					entry.m_score = 0;
					entries.push_back(entry);
				}
			}
		}
	}

	BfmeScoreEntry *it;
	for (it = entries.begin(); it != entries.end(); ++it)
	{
		it->m_teamScore = it->m_score = it->m_player->getScoreKeeper()->calculateScore();
		for (BfmeScoreEntry *other = entries.begin(); other != entries.end(); ++other)
		{
			if (other == it)
				continue;
			if (it->m_player->getRelationship(other->m_player->getTeam230()) == ALLIES &&
				other->m_player->getRelationship(it->m_player->getTeam230()) == ALLIES)
				it->m_teamScore += other->m_player->getScoreKeeper()->calculateScore();
		}
	}

	sort005770E0(entries.begin(), entries.end(), BfmeScoreEntryLess());

	Int row = 0;
	Player *previous = 0;
	memset(m_teamBreak, 0, sizeof(m_teamBreak));
	for (it = entries.begin(); it != entries.end(); ++it, ++row)
	{
		if (previous &&
			(it->m_player->getRelationship(previous->getTeam230()) != ALLIES ||
			 previous->getRelationship(it->m_player->getTeam230()) != ALLIES))
			m_teamBreak[row] = true;
		Rva00576C20(it->m_player, it->m_slot, row);
		previous = it->m_player;
	}
	if (row < 8)
		m_teamBreak[row] = true;
}
