// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Iinputs/vendor/stlport
// readable body of ?addScience@Player@@AAE_NW4ScienceType@@@Z: game/GameEngine/Source/Common/RTS/Player.cpp

// Everything a Player knows about its rank and its sciences:
//
//   0x00036057  addScience               forward to the shim that owns the set
//   0x000CBDC0  getRankLevelCap          how high this player may climb
//   0x000D5640  setScienceAvailability   move a science between the two vectors
//   0x000D7CA0  resetRank                put rank, points and sciences back
//
// The four sat in four files and between them held four partial pictures of
// one Player. Put together they agree, and each one fills in what the others
// left as padding:
//
//   +0x04  the PlayerTemplate       (resetRank, getRankLevelCap)
//   +0x28  the side string          (resetRank)
//   +0x234 m_sciences               (resetRank)
//   +0x240 m_sciencesDisabled       (resetRank, setScienceAvailability)
//   +0x24C m_sciencesHidden         (resetRank, setScienceAvailability)
//   +0x258 the rank/points block    (resetRank)
//   +0x6A0 the rank mirror          (resetRank)
//
// setScienceAvailability had spelled the whole run up to +0x240 as one 0x240
// byte prefix, which is right and says nothing; resetRank reaches the same two
// vectors by naming everything in front of them. One layout keeps the naming
// and loses the second copy.
//
// PlayerTemplate is the same story one level down: resetRank knew the
// intrinsic purchase points at +0xC0 and getRankLevelCap knew the two rank
// caps at +0xC4 and +0xC8. They are three adjacent fields that no single file
// could see were adjacent.
//
// One trap the merge had to step around. The two files both defined a type
// called Bool and defined it differently -- int in the rank file, for the
// out-parameter of TheGameText->fetch, and bool in the cap file, for
// GameLogic::_bfme_isInLivingWorldCampaign. Sharing either typedef silently
// renames the other file's callee (QAE_NXZ against QAEHXZ), so both are
// written out as the concrete type they were and the typedef is gone.
//
// addScience keeps its private access: the row mangles AAE, and moving it into
// the public section would rename it out of existence.
#include <limits.h>
#include <vector>

typedef int Int;

enum ScienceType {};

enum ScienceAvailabilityType
{
	SCIENCE_AVAILABILITY_INVALID = -1,
	SCIENCE_AVAILABLE,
	SCIENCE_DISABLED,
	SCIENCE_HIDDEN
};

typedef std::vector<ScienceType> ScienceVec;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
private:
	char *m_data;
};

template <class Character> class StringBase
{
public:
	void set(const StringBase<Character> &other);

protected:
	Character *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : public StringBase<unsigned short>
{
public:
	~UnicodeString();
	UnicodeString &operator=(const UnicodeString &other)
	{
		set(other);
		return *this;
	}

	static const UnicodeString TheEmptyString;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerTemplate.h
class PlayerTemplate
{
public:
	int getIntrinsicSciencePurchasePoints() const
	{
		return m_intrinsicSciencePurchasePoints;
	}

	char m_retailPrefix[0xc0];
	int m_intrinsicSciencePurchasePoints;			// this+0xC0
	int m_capModes125;					// this+0xC4
	int m_capOtherModes;					// this+0xC8
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/RankInfo.h
class RankInfo
{
public:
	int getSkillPointsNeeded(const AsciiString &side) const;

	char m_retailPrefix[0x28];
	int m_sciencePurchasePointsGranted;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/RankInfo.h
class RankInfoStore
{
public:
	const RankInfo *getRankInfo(int level) const;
	Int getRankLevelCount(void) const;
};

class GameTextInterface
{
public:
	virtual void vfn00();
	virtual void vfn01();
	virtual void vfn02();
	virtual void vfn03();
	virtual void vfn04();
	virtual void vfn05();
	virtual void vfn06();
	virtual void vfn07();
	virtual void vfn08();
	virtual void vfn09();
	// The out-parameter is int-wide, not bool: that width is part of the name.
	virtual UnicodeString fetch(const char *label, int *exists = 0);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	// Returns bool, not the int-wide Bool above: that width is part of the name.
	bool _bfme_isInLivingWorldCampaign(void);
	char m_pad[0x10c];
	Int m_gameMode;
};

// Address-derived name: the living-world level source at 0x003BCC10.
class Rva003BCC10
{
public:
	Int current(void);
};

// The owner of the science set addScience forwards to; nothing here identifies
// it beyond the call shape, so it keeps its shim name.
class PlayerAddScienceShim
{
public:
	bool add(ScienceType science);
};

class Player;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	char m_pad[0x0c];
	Player *m_local;
};

extern RankInfoStore *TheRankInfoStore;
extern GameTextInterface *TheGameText;
extern PlayerList *ThePlayerList;
extern GameLogic *TheGameLogic;
extern Rva003BCC10 *TheLivingWorldLogic;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Int getRankLevelCap(void);
	void setScienceAvailability(ScienceType science, ScienceAvailabilityType type);
	void resetRank();
	void resetSciences();

private:
	bool addScience(ScienceType);

	char m_vtable[4];
	const PlayerTemplate *m_playerTemplate;			// this+0x04
	char m_beforeSide[0x20];
	AsciiString m_side;					// this+0x28
	// BFME places additional player state before its science vectors.
	char m_beforeSciences[0x208];
	ScienceVec m_sciences;					// this+0x234
	ScienceVec m_sciencesDisabled;				// this+0x240
	ScienceVec m_sciencesHidden;				// this+0x24C
	int m_rankLevel;					// this+0x258
	int m_skillPoints;
	int m_retailRankPadding;
	int m_sciencePurchasePoints;
	int m_levelUp;
	int m_levelDown;
	UnicodeString m_generalName;				// this+0x270
	char m_afterGeneralName[0x42c];
	// Retail mirrors rank one in a later Player field used by its accessors.
	int m_rankLevelMirror;					// this+0x6A0
};

// ?addScience@Player@@AAE_NW4ScienceType@@@Z
bool Player::addScience(ScienceType science)
{
	return ((PlayerAddScienceShim *)this)->add(science);
}

// ?getRankLevelCap@Player@@QAEHXZ
// Local living-world campaign uses min(Rva003BCC10::current, the rank count).
// Otherwise min of the player-template cap (+0xC4 for modes 2/1/5, +0xC8 else)
// and the rank count. Descriptive BFME-only name; not ZH getRankLevel.
Int Player::getRankLevelCap(void)
{
	PlayerList *list = ThePlayerList;
	Int slot[2];

	if (this == list->m_local && TheGameLogic->_bfme_isInLivingWorldCampaign())
	{
		slot[1] = TheRankInfoStore->getRankLevelCount();
		slot[0] = TheLivingWorldLogic->current();
		return *((slot[0] < slot[1]) ? &slot[0] : &slot[1]);
	}

	if (m_playerTemplate)
	{
		Int mode = TheGameLogic->m_gameMode;
		if (mode == 2 || mode == 1 || mode == 5)
		{
			slot[0] = TheRankInfoStore->getRankLevelCount();
			slot[1] = m_playerTemplate->m_capModes125;
		}
		else
		{
			slot[0] = TheRankInfoStore->getRankLevelCount();
			slot[1] = m_playerTemplate->m_capOtherModes;
		}
		return *((slot[1] < slot[0]) ? &slot[1] : &slot[0]);
	}

	return TheRankInfoStore->getRankLevelCount();
}

// ?setScienceAvailability@Player@@QAEXW4ScienceType@@W4ScienceAvailabilityType@@@Z
void Player::setScienceAvailability(ScienceType science,
	ScienceAvailabilityType type)
{
	ScienceVec::iterator it;
	bool found = false;

	for (it = m_sciencesDisabled.begin(); it != m_sciencesDisabled.end(); ++it)
	{
		if (*it == science)
		{
			m_sciencesDisabled.erase(it);
			found = true;
			break;
		}
	}

	if (!found)
	{
		for (it = m_sciencesHidden.begin(); it != m_sciencesHidden.end(); ++it)
		{
			if (*it == science)
			{
				m_sciencesHidden.erase(it);
				break;
			}
		}
	}

	if (type == SCIENCE_DISABLED)
	{
		m_sciencesDisabled.push_back(science);
	}
	else if (type == SCIENCE_HIDDEN)
	{
		m_sciencesHidden.push_back(science);
	}
}

// ?resetRank@Player@@QAEXXZ
void Player::resetRank()
{
	m_rankLevel = 1;
	m_rankLevelMirror = 1;
	m_skillPoints = 0;

	const RankInfo *nextRank = TheRankInfoStore->getRankInfo(m_rankLevel + 1);
	m_levelUp = nextRank ? nextRank->getSkillPointsNeeded(m_side) : INT_MAX;
	m_levelDown = 0;
	m_sciences.clear();

	m_sciencePurchasePoints = m_playerTemplate
		? m_playerTemplate->getIntrinsicSciencePurchasePoints()
		: 0;
	const RankInfo *currentRank = TheRankInfoStore->getRankInfo(m_rankLevel);
	m_sciencePurchasePoints += currentRank
		? currentRank->m_sciencePurchasePointsGranted
		: 0;

	m_generalName = TheGameText
		? TheGameText->fetch("SCIENCE:GeneralName")
		: UnicodeString::TheEmptyString;
	resetSciences();
}
