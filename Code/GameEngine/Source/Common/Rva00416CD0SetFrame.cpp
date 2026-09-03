// cl: /O2 /Ob0

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride();

	char m_vptr[4];
	BfmeOverridable *m_nextOverride;
	char m_pad[0x430];
	int m_438;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char m_pad[0x3C];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;

class Rva00416CD0
{
	int m_00;
	BfmeOverridable *m_04;
	char m_pad[0x308];
	int m_310;

public:
	void set();
};

void Rva00416CD0::set()
{
	BfmeOverridable *p = m_04;
	if (!p)
		return;
	if (p->m_nextOverride)
		p = p->m_nextOverride->friend_getFinalOverride();
	if (!p)
		return;
	if (!TheGameLogic)
		return;
	m_310 = p->m_438 + TheGameLogic->m_frame;
}
