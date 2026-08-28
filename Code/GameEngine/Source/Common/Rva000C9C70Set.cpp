// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char m_pad[0x3C];
	unsigned m_3C;
};

extern GameLogic *TheGameLogic;

class Rva000C9C70
{
	unsigned char m_pad[0x29F];
	unsigned char m_flags[0x21];
	unsigned m_frame;

public:
	void set(int index);
};

void Rva000C9C70::set(int index)
{
	m_flags[index] = 1;
	m_frame = TheGameLogic->m_3C;
}
