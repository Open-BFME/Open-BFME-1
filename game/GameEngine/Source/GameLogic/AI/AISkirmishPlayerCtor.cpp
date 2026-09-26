// ??0AISkirmishPlayer@@QAE@PAVPlayer@@@Z
// Retail 0x00168660. Player::setPlayerType constructs the 0xA0-byte
// skirmish AI after the AIPlayer base constructor returns.

typedef unsigned int UnsignedInt;
typedef unsigned char Bool;

class Player
{
public:
	char m_beforeCanBuildUnits[0x294];
	Bool m_canBuildUnits;
};

struct GameLogic
{
	char m_beforeFrame[0x3c];
	int m_frame;
};

#define TheGameLogic (*(GameLogic **)0x012f0898)

class AIPlayer
{
public:
	AIPlayer(Player *player);

protected:
	char m_beforeSkillsetSelector[0x28];
	int m_skillsetSelector;
	char m_afterSkillsetSelector[0x4c];
};

class AISkirmishPlayer : public AIPlayer
{
public:
	AISkirmishPlayer(Player *player);

private:
	int m_curFrontBaseDefense;
	int m_curFlankBaseDefense;
	int m_curFrontLeftDefenseAngle;
	int m_curFrontRightDefenseAngle;
	int m_curLeftFlankLeftDefenseAngle;
	int m_curLeftFlankRightDefenseAngle;
	int m_curRightFlankLeftDefenseAngle;
	int m_curRightFlankRightDefenseAngle;
	UnsignedInt m_frameToCheckEnemy;
	Player *m_currentEnemy;
};

AISkirmishPlayer::AISkirmishPlayer(Player *player) :
	AIPlayer(player),
	m_curFrontBaseDefense(0),
	m_curFlankBaseDefense(0),
	m_curFrontLeftDefenseAngle(0),
	m_curFrontRightDefenseAngle(0),
	m_curLeftFlankLeftDefenseAngle(0),
	m_curLeftFlankRightDefenseAngle(0),
	m_curRightFlankLeftDefenseAngle(0),
	m_curRightFlankRightDefenseAngle(0),
	m_frameToCheckEnemy(0),
	m_currentEnemy(0)
{
	*(UnsignedInt *)this = 0x01096fb0;
	m_skillsetSelector = TheGameLogic->m_frame;
	player->m_canBuildUnits = 1;
}
