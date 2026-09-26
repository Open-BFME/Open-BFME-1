// cl: /O2 /Ob0

class GenBase000426E0
{
public:
	GenBase000426E0();
	virtual void handle();
};

class Rva00428830 : public GenBase000426E0
{
	int m_04;
	char m_gap[0xAC];
	int m_B4;
	int m_B8;
	int m_BC;

public:
	Rva00428830();
};

Rva00428830::Rva00428830()
{
	m_B4 = -1;
	m_B8 = -1;
	m_BC = -1;
	m_04 = 1;
}
