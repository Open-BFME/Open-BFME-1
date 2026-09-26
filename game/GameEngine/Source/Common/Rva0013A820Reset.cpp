// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	void clear();

private:
	void *m_item;
};

class Rva0013A820
{
	Rva0036CA00Str m_00;
	Rva0036CA00Str m_04;
	Rva0036CA00Str m_08;
	Rva0036CA00Str m_0C;
	Rva0036CA00Str m_10;
	int m_14;
	int m_18;
	Rva0036CA00Str m_1C;
	Rva0036CA00Str m_20;
	int m_24;
	Rva0036CA00Str m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	Rva0036CA00Str m_3C;
	int m_40;
	Rva0036CA00Str m_44;

public:
	void reset();
};

void Rva0013A820::reset()
{
	m_00.clear();
	m_04.clear();
	m_08.clear();
	m_0C.clear();
	m_10.clear();
	m_1C.clear();
	m_20.clear();
	m_28.clear();
	m_3C.clear();
	m_44.clear();
	m_40 = 0;
	m_38 = 0;
	m_34 = 0;
	m_30 = 0;
	m_2C = 0;
	m_24 = 0;
	m_18 = 0;
	m_14 = 0;
}
