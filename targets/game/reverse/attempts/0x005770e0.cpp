// ?_bfme_populateMultiPlayer@BfmeAptScreenScoreScreen@@QAEXH@Z
// partial score=0.43 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc
// stlport
#include <algorithm>
#include <vector>
//
// Retail 0x005774E0. Open the BFME score screen after game cleanup and fill
// the screen with the single-player or multiplayer score data.

typedef bool Bool;
typedef int Int;

enum RecorderModeType
{
	RECORDERMODETYPE_RECORD,
	RECORDERMODETYPE_PLAYBACK,
	RECORDERMODETYPE_NONE
};

class RecorderClass
{
public:
	RecorderModeType getMode(void);
};

class GameLogic
{
public:
	char m_bfmeHead[0x10C];
	Int m_bfmeMode;
	Bool isInSinglePlayerGame(void);
};

template <typename T> class StringBase
{
	friend class AsciiString;

	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

public:
	Bool isEmpty() const
	{
		return m_data == 0 || m_data->length == 0;
	}
	const T *str() const
	{
		return m_data ? &m_data->data[0] : (const T *)"";
	}

private:
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	Bool isEmpty() const { return StringBase<char>::isEmpty(); }
	const char *str() const { return StringBase<char>::str(); }
};

class Rva0069AEB0Node
{
public:
	virtual void slot00(void);
	void stop(Int which);
};

class AudioEventRTS : public Rva0069AEB0Node
{
public:
	virtual void slot00(void);
	AudioEventRTS(const AsciiString &eventName, Int extra);
	~AudioEventRTS();

private:
	char m_data[0x6C];
};

class AudioClientUpdate
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void addAudioEvent(AudioEventRTS *event) = 0;
};

class Shell
{
public:
	void push(AsciiString filename, Bool shutdownImmediate = false);
};

class Player;
class GameSlot;
class BfmeAptScreenScoreScreen
{
public:
	void _bfme_populateSinglePlayer(void);
	void _bfme_populateMultiPlayer(Int type);
	void _bfme_addPlayerTable(Player *player, GameSlot *slot, Int row);

private:
	char m_unmodelled_prefix[0x25C];
	Int m_type;
	char m_unmodelled_between[0x10];
	Int m_teamBreakWords[2];
};

extern RecorderClass *TheRecorder;
extern GameLogic *TheBfmeGameLogic;
extern AudioClientUpdate *TheAudioClientUpdate;
extern Shell *TheShell;
extern void *g_obj12F4B50;

// ?_bfme_showScoreScreen@@YA_NXZ
Bool _bfme_showScoreScreen(void)
{
	Int type = 0;

	if (g_obj12F4B50 != 0)
		goto success;

	if (TheRecorder != 0 && TheRecorder->getMode() == RECORDERMODETYPE_PLAYBACK)
	{
		type = 4;
	}
	else if (TheBfmeGameLogic->m_bfmeMode == 5)
	{
		type = 3;
	}
	else if (TheBfmeGameLogic->m_bfmeMode == 1)
	{
		type = 2;
	}
	else if (TheBfmeGameLogic->m_bfmeMode == 2)
	{
		type = 1;
	}
	else if (!TheBfmeGameLogic->isInSinglePlayerGame() &&
		TheBfmeGameLogic->m_bfmeMode != 6)
	{
		return false;
	}
	else
	{
		type = 0;
	}

	{
		AudioEventRTS audioEvent(AsciiString("ScoreScreenMusic"), 2);
		audioEvent.stop(1);
		TheAudioClientUpdate->addAudioEvent(&audioEvent);
		TheShell->push(AsciiString("ScoreScreen.apt"), false);

		if (type == 0)
			((BfmeAptScreenScoreScreen *)g_obj12F4B50)->_bfme_populateSinglePlayer();
		else
			((BfmeAptScreenScoreScreen *)g_obj12F4B50)->_bfme_populateMultiPlayer(type);
	}

success:
	return true;
}

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
	Relationship getRelationship(const Team *team) const;
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

struct BfmeScoreObject
{
	char m_pad[0x18];
	Int m_order;
};
struct BfmeScoreEntry
{
	BfmeScoreObject *m_object;
	Player *m_player;
	int m_secondary;
	int m_primary;
};
struct BfmeScoreEntryLess
{
	void *m_state;
	Bool operator()(const BfmeScoreEntry *left,
		const BfmeScoreEntry *right) const;
	Bool operator()(const BfmeScoreEntry &left,
		const BfmeScoreEntry &right) const
	{
		return operator()(&left, &right);
	}
};
struct BfmeScoreGameSlotLayout
{
	char m_pad[0x2C];
	AsciiString m_internalPlayerName;
};
struct BfmeScorePlayerLayout
{
	char m_pad[0x230];
	Team *m_team;
};

static __forceinline ScoreKeeper *bfmeScoreKeeper(Player *player)
{
	return (ScoreKeeper *)((char *)player + 0x348);
}
static __forceinline Team *bfmeScoreTeam(Player *player)
{
	return ((BfmeScorePlayerLayout *)player)->m_team;
}

// ?_bfme_populateMultiPlayer@BfmeAptScreenScoreScreen@@QAEXH@Z
void BfmeAptScreenScoreScreen::_bfme_populateMultiPlayer(Int type)
{
	m_type = type;
	Int i = 0;
	std::vector<BfmeScoreEntry> scores;
	scores.reserve(8);
	for (; i < 8; ++i)
	{
		GameSlot *slot = TheGameInfo->getSlot(i);
		if (slot->isOccupied())
		{
			AsciiString playerName =
				((BfmeScoreGameSlotLayout *)slot)->m_internalPlayerName;
			if (!playerName.isEmpty())
			{
				Player *player = ThePlayerList->findPlayerWithNameKey(
					TheNameKeyGenerator->nameToKey(playerName.str()));
				if (player != 0 && !player->isPlayerObserver())
				{
					BfmeScoreEntry entry =
						{(BfmeScoreObject *)slot, player, 0, 0};
					scores.push_back(entry);
				}
			}
		}
	}
	for (BfmeScoreEntry *entry = scores.begin();
		entry != scores.end(); ++entry)
	{
		Int score = bfmeScoreKeeper(entry->m_player)->calculateScore();
		entry->m_primary = score;
		entry->m_secondary = score;
		for (BfmeScoreEntry *other = scores.begin(); other != entry; ++other)
		{
			if (entry->m_player->getRelationship(
					bfmeScoreTeam(other->m_player)) == ALLIES &&
				other->m_player->getRelationship(
					bfmeScoreTeam(entry->m_player)) == ALLIES)
				entry->m_primary +=
					bfmeScoreKeeper(other->m_player)->calculateScore();
		}
	}
	BfmeScoreEntryLess less = {0};
	std::sort(scores.begin(), scores.end(), less);
	m_teamBreakWords[0] = 0;
	m_teamBreakWords[1] = 0;
	unsigned char *teamBreak = (unsigned char *)m_teamBreakWords;
	Player *previous = 0;
	Int row = 0;
	for (BfmeScoreEntry *entry = scores.begin();
		entry != scores.end(); ++entry)
	{
		if (previous != 0 &&
			(entry->m_player->getRelationship(bfmeScoreTeam(previous)) != ALLIES ||
				previous->getRelationship(bfmeScoreTeam(entry->m_player)) != ALLIES))
			teamBreak[row] = 1;
		_bfme_addPlayerTable(entry->m_player,
			(GameSlot *)entry->m_object, row);
		previous = entry->m_player;
		++row;
	}
	if (row < 8)
		teamBreak[row] = 1;
}
