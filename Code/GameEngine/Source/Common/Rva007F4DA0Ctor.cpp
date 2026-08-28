// cl: /O2 /Ob0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	Snapshot();
	virtual void handle();
};

class Rva007F4DA0 : public Snapshot
{
	int m_04;
	char m_08;
	char m_gap[0x1B];
	int m_24;

public:
	Rva007F4DA0();
};

Rva007F4DA0::Rva007F4DA0()
{
	m_08 = 0;
	m_24 = 0;
	m_04 = 1;
}
