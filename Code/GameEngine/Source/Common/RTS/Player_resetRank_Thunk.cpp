// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ivendor/stlport
#include <limits.h>
#include <vector>

typedef int Bool;

enum ScienceType {};
typedef std::vector<ScienceType> ScienceVec;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerTemplate.h
class PlayerTemplate
{
public:
	int getIntrinsicSciencePurchasePoints() const
	{
		return m_intrinsicSciencePurchasePoints;
	}

private:
	char m_retailPrefix[0xc0];
	int m_intrinsicSciencePurchasePoints;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/RankInfo.h
class RankInfo
{
public:
	int getSkillPointsNeeded(const AsciiString &side) const;

	char m_retailPrefix[0x28];
	int m_sciencePurchasePointsGranted;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/RankInfo.h
class RankInfoStore
{
public:
	const RankInfo *getRankInfo(int level) const;
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
	virtual UnicodeString fetch(const char *label, Bool *exists = 0);
};

extern RankInfoStore *TheRankInfoStore;
extern GameTextInterface *TheGameText;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	void resetRank();
	void resetSciences();

private:
	char m_vtable[4];
	const PlayerTemplate *m_playerTemplate;
	char m_beforeSide[0x20];
	AsciiString m_side;
	// BFME places additional player state before its science vectors.
	char m_beforeSciences[0x208];
	ScienceVec m_sciences;
	ScienceVec m_sciencesDisabled;
	ScienceVec m_sciencesHidden;
	int m_rankLevel;
	int m_skillPoints;
	int m_retailRankPadding;
	int m_sciencePurchasePoints;
	int m_levelUp;
	int m_levelDown;
	UnicodeString m_generalName;
	char m_afterGeneralName[0x42c];
	// Retail mirrors rank one in a later Player field used by its accessors.
	int m_rankLevelMirror;
};

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
