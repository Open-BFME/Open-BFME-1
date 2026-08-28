// cl: /O2 /Ob0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	Snapshot();
	virtual void handle();
};

class Rva007E8810 : public Snapshot
{
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	char m_30;

public:
	Rva007E8810();
};

Rva007E8810::Rva007E8810()
{
	m_08 = 0;
	m_0C = 0;
	m_04 = 0;
	m_10 = 0;
	m_18 = 0;
	m_14 = 0;
	m_28 = 0;
	m_24 = 0;
	m_20 = 0;
	m_1C = 0;
	m_30 = 0;
	m_2C = 4;
}
