// ?grabSinglePlayerInfo@@YAXXZ
// partial score=0.9334 date=2026-10-01
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseascii /Igame/Libraries/Source/WWVegas/WWLib
// BFME score-screen single-player aggregation, retail 0x004E8320.

#include <string.h>

extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned int count);
#pragma intrinsic(memcmp)

typedef int Int;
typedef bool Bool;
typedef int Color;

template <typename T> struct StringData
{
	Int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();
	void set(const T *text, Int length);
	void concat(const T *text, Int length);

	StringData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	void set(const char *text)
	{
		StringBase<char>::set(text, text ? strlen(text) : 0);
	}

	void concat(const char *text)
	{
		StringBase<char>::concat(text, text ? strlen(text) : 0);
	}

	void concat(const AsciiString &other)
	{
		const StringBase<char> *source = (const StringBase<char> *)&other;
		Int length = source->m_data ? source->m_data->length : 0;
		const char *text = source->m_data ? source->m_data->text : "";
		((StringBase<char> *)this)->concat(text, length);
	}

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : "";
	}

	Int compare(const AsciiString &other) const
	{
		const StringBase<char> *self = (const StringBase<char> *)this;
		const StringBase<char> *source = (const StringBase<char> *)&other;
		Int selfLength = self->m_data ? self->m_data->length : 0;
		const char *selfText = self->m_data ? self->m_data->text : "";
		Int sourceLength = source->m_data ? source->m_data->length : 0;
		const char *sourceText = source->m_data ? source->m_data->text : "";
		Int length = sourceLength < selfLength ? sourceLength : selfLength;
		Int result = memcmp(sourceText, selfText, length);
		if (result != 0)
			return result;
		return sourceLength - selfLength;
	}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
};

class Image;
class Team;

struct ScoreGather
{
	Int m_totalMoneyEarned;
	Int m_totalMoneySpent;
	Int m_totalUnitsDestroyed;
	Int m_totalUnitsBuilt;
	Int m_totalUnitsLost;
	Int m_totalBuildingsDestroyed;
	Int m_totalBuildingsBuilt;
	Int m_totalBuildingsLost;
	const Image *m_sideImage;
};

class ScoreKeeper
{
public:
	Int getTotalMoneyEarned() { return m_totalMoneyEarned; }
	Int getTotalMoneySpent() { return m_totalMoneySpent; }
	Int getTotalUnitsDestroyed();
	Int getTotalUnitsBuilt() { return *(const volatile Int *)&m_totalUnitsBuilt; }
	Int getTotalUnitsLost() { return m_totalUnitsLost; }
	Int getTotalBuildingsDestroyed();
	Int getTotalBuildingsBuilt() { return m_totalBuildingsBuilt; }
	Int getTotalBuildingsLost() { return m_totalBuildingsLost; }

private:
	void *m_vtable;
	Int m_totalMoneyEarned;
	Int m_totalMoneySpent;
	Int m_totalUnitsDestroyed[32];
	Int m_totalUnitsBuilt;
	Int m_totalUnitsLost;
	Int m_totalBuildingsDestroyed[32];
	Int m_totalBuildingsBuilt;
	Int m_totalBuildingsLost;
};

class PlayerTemplate
{
public:
	const AsciiString &getScoreScreen() const
	{
		return *(const AsciiString *)((const char *)this + 0xCC);
	}

	const Image *getSideIconImage() const;
};

enum PlayerType
{
	PLAYER_HUMAN = 0
};

enum Relationship
{
	ENEMIES = 0,
	ALLIES = 2
};

class Player
{
public:
	Bool isPlayerObserver() const;
	PlayerType getPlayerType() const
	{
		return *(const PlayerType *)((const char *)this + 0x2C);
	}

	const PlayerTemplate *getPlayerTemplate() const
	{
		return *(const PlayerTemplate *const *)((const char *)this + 4);
	}

	const AsciiString &getBaseSide() const
	{
		return *(const AsciiString *)((const char *)this + 0x28);
	}

	Team *getDefaultTeam() const
	{
		return *(Team *const *)((const char *)this + 0x230);
	}

	Relationship getRelationship(const Team *team) const;
	ScoreKeeper *getScoreKeeper()
	{
		return (ScoreKeeper *)((char *)this + 0x348);
	}
	Bool getListInScoreScreen() const;
	Color getPlayerColor() const
	{
		return *(const Color *)((const char *)this + 0x1C4);
	}
};

class PlayerList
{
public:
	Player *getLocalPlayer()
	{
		return *(Player **)((char *)this + 0x0C);
	}
	Player *getNthPlayer(Int index);
};

class GameLogic
{
public:
	Bool isInSinglePlayerGame();
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

class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0) = 0;
};

extern PlayerList *ThePlayerList;
extern GameLogic *TheGameLogic;
extern MappedImageCollection *TheMappedImageCollection;
extern GameTextInterface *TheGameText;
extern GameWindow *parent;

void populatePlayerInfo(Player *player, Int pos);
void populateSideInfo(UnicodeString side, ScoreGather *sg, Int pos, Color color);
void hideWindows(Int pos);

enum
{
	MAX_PLAYER_COUNT = 32,
	USA_FRIEND = 0,
	CHINA_FRIEND,
	GLA_FRIEND,
	USA_ENEMY,
	CHINA_ENEMY,
	GLA_ENEMY,
	MAX_RELATIONS
};

static __forceinline void accumulateScore(ScoreGather &sg, ScoreKeeper *sk)
{
	sg.m_totalBuildingsBuilt += sk->getTotalBuildingsBuilt();
	sg.m_totalBuildingsDestroyed += sk->getTotalBuildingsDestroyed();
	sg.m_totalBuildingsLost += sk->getTotalBuildingsLost();
	sg.m_totalMoneySpent += sk->getTotalMoneySpent();
	sg.m_totalMoneyEarned += sk->getTotalMoneyEarned();
	sg.m_totalUnitsBuilt += sk->getTotalUnitsBuilt();
	sg.m_totalUnitsDestroyed += sk->getTotalUnitsDestroyed();
	sg.m_totalUnitsLost += sk->getTotalUnitsLost();
}

void grabSinglePlayerInfo()
{
	Int playerCount = 0;
	Player *localPlayer, *player;
	localPlayer = ThePlayerList->getLocalPlayer();

	if (localPlayer)
	{
		if (!localPlayer->isPlayerObserver())
		{
			populatePlayerInfo(localPlayer, playerCount);
			++playerCount;
		}
		else
		{
			for (Int k = 0; k < MAX_PLAYER_COUNT; ++k)
			{
				localPlayer = ThePlayerList->getNthPlayer(k);
				if (localPlayer->getPlayerType() == PLAYER_HUMAN)
				{
					populatePlayerInfo(localPlayer, playerCount);
					++playerCount;
					break;
				}
				localPlayer = 0;
			}
		}

		const PlayerTemplate *fact = ThePlayerList->getLocalPlayer()->getPlayerTemplate();
		if (fact != 0)
		{
			const Image *image = TheMappedImageCollection->findImageByName(ThePlayerList->getLocalPlayer()->getPlayerTemplate()->getScoreScreen());
			if (image)
			{
				parent->winSetEnabledImage(0, image);
				parent->winSetStatus(parent->winGetStatus() | 0x80);
			}
		}
	}

	if (!localPlayer)
		return;

	AsciiString side;
	for (Int j = 0; j < MAX_RELATIONS; ++j)
	{
		Bool isFriend = true;
		switch (j)
		{
		case USA_ENEMY:
			isFriend = false;
		case USA_FRIEND:
			side.set("America");
			break;
		case CHINA_ENEMY:
			isFriend = false;
		case CHINA_FRIEND:
			side.set("China");
			break;
		case GLA_ENEMY:
			isFriend = false;
		case GLA_FRIEND:
			side.set("GLA");
			break;
		}

		ScoreGather sg;
		sg.m_totalBuildingsBuilt = 0;
		sg.m_totalBuildingsDestroyed = 0;
		sg.m_totalBuildingsLost = 0;
		sg.m_totalMoneyEarned = 0;
		sg.m_totalMoneySpent = 0;
		sg.m_totalUnitsBuilt = 0;
		sg.m_totalUnitsDestroyed = 0;
		sg.m_totalUnitsLost = 0;
		sg.m_sideImage = 0;
		Bool populate = false;
		Color color = 0x00FFFFFF;

		for (Int i = 0; i < MAX_PLAYER_COUNT; ++i)
		{
			player = ThePlayerList->getNthPlayer(i);
			if (player && player != localPlayer && side.compare(player->getBaseSide()) == 0)
			{
				if ((TheGameLogic->isInSinglePlayerGame() == false) ||
					(player->getListInScoreScreen() == true))
				{
					if ((isFriend == true && localPlayer->getRelationship(player->getDefaultTeam()) == ALLIES) ||
						(isFriend == false && localPlayer->getRelationship(player->getDefaultTeam()) == ENEMIES))
					{
						ScoreKeeper *sk = player->getScoreKeeper();
						accumulateScore(sg, sk);
						sg.m_sideImage = player->getPlayerTemplate()->getSideIconImage();
						color = player->getPlayerColor();
						populate = true;
					}
				}
			}
		}

		if (populate)
		{
			AsciiString label;
			label.set("GUI:");
			label.concat(side);
			if (isFriend)
				label.concat("Allies");
			else
				label.concat("Enemies");
			populateSideInfo(TheGameText->fetch(label), &sg, playerCount, color);
			++playerCount;
		}
	}
	hideWindows(playerCount);
}
