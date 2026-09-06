// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// readable body of ?buildSpecificTeam@Player@@QAEXPAVTeamPrototype@@@Z: Code/GameEngine/Source/Common/RTS/Player.cpp

typedef bool Bool;

class TeamPrototype;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class AIPlayer
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void buildSpecificAITeam(TeamPrototype *, Bool);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
	char m_unreconstructed[0x220];
	AIPlayer *m_ai;

public:
	void buildSpecificTeam(TeamPrototype *);
};

// ?buildSpecificTeam@Player@@QAEXPAVTeamPrototype@@@Z
void Player::buildSpecificTeam(TeamPrototype *teamPrototype)
{
	if (m_ai) {
		m_ai->buildSpecificAITeam(teamPrototype, true);
	}
}
