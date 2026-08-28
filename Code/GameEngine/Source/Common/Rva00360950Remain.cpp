// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char m_pad[0x3C];
	int m_3C;
};

extern GameLogic *TheGameLogic;

class Rva00360950
{
	unsigned char m_pad[0x28];
	int m_28;

public:
	int remain() const;
};

int Rva00360950::remain() const
{
	int g = TheGameLogic->m_3C;
	int v = m_28;
	if (g < v)
		return v - g;
	return 0;
}
