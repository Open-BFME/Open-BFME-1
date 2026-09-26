// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// BFME ScoreScreen::grabMultiPlayerInfo, retail 0x004E8050.  The four matched
// score-screen initialisers call this through its ILT at 0x00042640.  The
// Zero Hour source supplies the score-map ordering and display dispatch; BFME
// differs by taking each player's internal name from GameInfo's slot and by
// placing Player::m_scoreKeeper at +0x348.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

typedef int Int;
typedef bool Bool;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();
	void set(const StringBase<T> &other);

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	AsciiString &operator=(const AsciiString &other)
	{
		StringBase<char>::set(other);
		return *this;
	}

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : "";
	}
};

class Image;

class GameSlot
{
public:
	const AsciiString &getInternalPlayerName() const
	{
		return m_internalPlayerName;
	}

private:
	unsigned char m_head[0x2C];
	AsciiString m_internalPlayerName;
};

class GameInfo
{
public:
	GameSlot *getSlot(Int slot);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
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
	ScoreKeeper *getScoreKeeper()
	{
		return &m_scoreKeeper;
	}

private:
	unsigned char m_head[0x348];
	ScoreKeeper m_scoreKeeper;
};

class PlayerList
{
public:
	Player *getLocalPlayer()
	{
		return m_local;
	}

	Player *findPlayerWithNameKey(NameKeyType key);

private:
	unsigned char m_head[0x0C];
	Player *m_local;
};

class MappedImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

class GameWindow
{
public:
	Int winSetEnabledImage(Int index, const Image *image);
	unsigned int winGetStatus();
	unsigned int winSetStatus(unsigned int status);
};

extern GameInfo *TheGameInfo;
extern MappedImageCollection *TheMappedImageCollection;
extern NameKeyGenerator *TheNameKeyGenerator;
extern PlayerList *ThePlayerList;
extern GameWindow *parent;

void hideWindows(Int pos);
void setObserverWindows(Player *player, Int pos);
void populatePlayerInfo(Player *player, Int pos);

enum { MAX_SLOTS = 8 };

void grabMultiPlayerInfo()
{
	typedef std::map<Int, Player *> ScoreMap;
	typedef ScoreMap::iterator ScoreMapIt;
	typedef ScoreMap::reverse_iterator RevScoreMapIt;

	Int playerCount = 0;
	AsciiString playerName;
	Player *player;
	ScoreMap scores;
	ScoreMapIt it;
	scores.clear();
	Int adder = 1;

	player = ThePlayerList->getLocalPlayer();
	if (player)
	{
		const Image *image = TheMappedImageCollection->findImageByName("MutiPlayer_ScoreScreen");
		if (image)
		{
			parent->winSetEnabledImage(0, image);
			parent->winSetStatus(parent->winGetStatus() | 0x80);
		}
	}

	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		playerName = TheGameInfo->getSlot(i)->getInternalPlayerName();
		player = ThePlayerList->findPlayerWithNameKey(
			TheNameKeyGenerator->nameToKey(playerName.str()));
		if (player)
		{
			Int score = player->getScoreKeeper()->calculateScore();
			it = scores.find(score);
			if (it != scores.end())
				score += adder++;
			scores[score] = player;
			++playerCount;
		}
	}

	hideWindows(playerCount);
	Int count = 0;
	RevScoreMapIt revIt;
	for (revIt = scores.rbegin(); revIt != scores.rend(); ++revIt)
	{
		Player *p = revIt->second;
		if (p->isPlayerObserver())
			setObserverWindows(p, count);
		else
			populatePlayerInfo(p, count);
		++count;
	}
}
