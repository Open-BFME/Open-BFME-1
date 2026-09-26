// ?killPlayer@Player@@QAEXXZ
// partial score=0.98 date=2026-09-10
// ?killPlayer@Player@@QAEXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef bool Bool;
typedef unsigned int UnsignedInt;

class Team
{
public:
	void evacuateTeam();
	void killTeam();
	Team *_bfme_nextInInstanceList();
};

#pragma comment(linker, "/alternatename:?evacuateTeam@Team@@QAEXXZ=?j_0000b582@@YAXXZ")
#pragma comment(linker, "/alternatename:?killTeam@Team@@QAEXXZ=?j_000341d0@@YAXXZ")
#pragma comment(linker, "/alternatename:?_bfme_nextInInstanceList@Team@@QAEPAV1@XZ=?j_00022a70@@YAXXZ")

struct TeamPrototype
{
	char m_pad[0x274];
	Team *m_firstTeam;
};

struct TeamPrototypeNode
{
	TeamPrototypeNode *m_next;
	TeamPrototypeNode *m_previous;
	TeamPrototype *m_value;
};

struct Rva00367E30Logic
{
	Bool isInSinglePlayerGame();
};

#pragma comment(linker, "/alternatename:?isInSinglePlayerGame@Rva00367E30Logic@@QAE_NXZ=?j_0001be28@@YAXXZ")

struct Rva002EE330PlayerList
{
#define PLAYER_LIST_SLOT(n) virtual void slot##n() = 0
	PLAYER_LIST_SLOT(0); PLAYER_LIST_SLOT(1); PLAYER_LIST_SLOT(2);
	PLAYER_LIST_SLOT(3); PLAYER_LIST_SLOT(4); PLAYER_LIST_SLOT(5);
	PLAYER_LIST_SLOT(6); PLAYER_LIST_SLOT(7); PLAYER_LIST_SLOT(8);
	PLAYER_LIST_SLOT(9); PLAYER_LIST_SLOT(10); PLAYER_LIST_SLOT(11);
#undef PLAYER_LIST_SLOT
};

class Money
{
public:
	void *m_unknown;
	UnsignedInt m_amount;
	UnsignedInt withdraw(UnsignedInt amount, Bool playSound);
};

#pragma comment(linker, "/alternatename:?withdraw@Money@@QAEII_N@Z=?j_00041894@@YAXXZ")

class Player
{
public:
	char m_pad00[0x2c];
	int m_playerType;
	char m_pad30[0x18];
	Money m_money;
	char m_pad50[0x238];
	TeamPrototypeNode *m_playerTeamPrototypes;
	char m_pad28c[0x3f4];
	Bool m_isPlayerDead;

	void killPlayer();
};

extern Rva00367E30Logic *TheBfmeGameLogic;
extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

void Player::killPlayer()
{
	for (TeamPrototypeNode *node = m_playerTeamPrototypes->m_next;
		node != m_playerTeamPrototypes; node = node->m_next)
	{
		for (Team *team = node->m_value->m_firstTeam;
			team; team = team->_bfme_nextInInstanceList())
			team->evacuateTeam();
	}

	m_isPlayerDead = 1;

	for (TeamPrototypeNode *node = m_playerTeamPrototypes->m_next;
		node != m_playerTeamPrototypes; node = node->m_next)
	{
		for (Team *team = node->m_value->m_firstTeam;
			team; team = team->_bfme_nextInInstanceList())
			team->killTeam();
	}

	if (TheBfmeGameLogic->isInSinglePlayerGame() && m_playerType == 1)
	{
		m_isPlayerDead = 0;
		return;
	}

	Rva002EE330ThePlayers->slot11();
	m_money.withdraw(m_money.m_amount, 1);
}
