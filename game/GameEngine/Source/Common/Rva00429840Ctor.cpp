// cl: /O2 /Ob0

class GenBase000426E0
{
public:
	GenBase000426E0();
	virtual void handle();
};

class Rva00429840 : public GenBase000426E0
{
	int m_04;
	char m_gap[0xAC];
	int m_B4;
	int m_B8;
	int m_BC;
	int m_C0;
	int m_C4;
	int m_C8;

public:
	Rva00429840();
};

Rva00429840::Rva00429840()
{
	m_C0 = 0;
	m_C4 = 0;
	m_C8 = 0;
	m_B4 = 0;
	m_B8 = 0;
	m_BC = 0;
	m_04 = 5;
}
