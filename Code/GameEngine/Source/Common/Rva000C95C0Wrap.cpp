// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Team;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class AIPlayer
{
public:
	void guardSupplyCenter(Team *team, int id);
};

class Rva000C95C0
{
	char m_pad[0x220];
	AIPlayer *m_ai;

public:
	void wrap(Team *team, int id);
};

void Rva000C95C0::wrap(Team *team, int id)
{
	if (m_ai)
		m_ai->guardSupplyCenter(team, id);
}
