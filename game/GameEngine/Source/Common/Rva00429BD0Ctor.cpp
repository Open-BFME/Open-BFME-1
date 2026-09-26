// cl: /O2 /Ob0

class GenBase000426E0
{
public:
	GenBase000426E0();
	virtual void handle();
};

class Rva00429BD0 : public GenBase000426E0
{
	int m_04;
	char m_gap[0xAC];
	int m_B4;
	int m_B8;

public:
	Rva00429BD0();
};

Rva00429BD0::Rva00429BD0()
{
	m_B4 = -1;
	m_B8 = 0;
	m_04 = 7;
}
