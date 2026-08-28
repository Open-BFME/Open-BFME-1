// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char m_pad[0x3C];
	unsigned m_3C;
};

extern GameLogic *TheGameLogic;

class Rva00360970
{
	unsigned char m_pad[0x20];
	unsigned m_20;
	unsigned char m_pad24[4];
	unsigned m_28;

public:
	void advance();
};

void Rva00360970::advance()
{
	if (TheGameLogic->m_3C >= m_28 && m_20 == 2)
		m_20 = 3;
}
