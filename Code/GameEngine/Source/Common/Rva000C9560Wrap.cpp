// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class AIPlayer
{
public:
	bool isSupplySourceSafe(int id);
};

class Rva000C9560
{
	char m_pad[0x220];
	AIPlayer *m_ai;

public:
	bool wrap(int id);
};

bool Rva000C9560::wrap(int id)
{
	if (m_ai)
		return m_ai->isSupplySourceSafe(id);
	return true;
}
