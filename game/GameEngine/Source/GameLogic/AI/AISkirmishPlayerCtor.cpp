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

// TU-local view of the frame counter at +0x3C of the GameLogic singleton.
struct GameLogicFrameView
{
	char m_beforeFrame[0x3c];
	int m_frame;
};

// Retail's GameLogic singleton at 0x012F0898; the one canonical spelling.
class GameLogic;
extern GameLogic *TheGameLogic;

// Retail's vftable for AISkirmishPlayer is 0x01096FB0, pinned in symbols.csv as
// ??_7AISkirmishPlayer@@6B@ and corroborated by Player::setPlayerType's
// skirmish branch and by the destructor at 0x00168710 which reads the same
// table.  The stand-in name below resolved nothing; __identifier spells the
// compiler-emitted symbol so the reference links to that real definition.
extern "C" const char __identifier("??_7AISkirmishPlayer@@6B@")[];

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
	*(UnsignedInt *)this = (UnsignedInt)__identifier("??_7AISkirmishPlayer@@6B@");
	m_skillsetSelector = ((GameLogicFrameView *)TheGameLogic)->m_frame;
	player->m_canBuildUnits = 1;
}
