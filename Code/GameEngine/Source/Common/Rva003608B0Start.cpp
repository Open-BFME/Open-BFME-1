// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char m_pad[0x3C];
	unsigned m_3C;
};

extern GameLogic *TheGameLogic;

class Rva003608B0
{
	unsigned char m_pad[0x20];
	unsigned m_20;
	unsigned m_24;
	unsigned m_28;
	unsigned m_2C;

public:
	void start();
};

void Rva003608B0::start()
{
	if (m_20 == 0)
	{
		m_20 = 2;
		m_2C = TheGameLogic->m_3C;
		m_28 = TheGameLogic->m_3C + m_24;
	}
}
