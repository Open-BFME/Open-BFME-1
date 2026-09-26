// cl: /O2 /Ob0

class Rva00532230
{
	void *m_00;
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
	int m_30;
	void *m_34;
	int m_38;

public:
	Rva00532230 &set(void *p);
};

Rva00532230 &Rva00532230::set(void *p)
{
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_20 = 0;
	m_24 = 0;
	m_28 = 0;
	m_2C = 0;
	m_30 = 0;
	m_00 = (void *)0x01106F08;
	m_34 = p;
	m_38 = 0;
	return *this;
}
