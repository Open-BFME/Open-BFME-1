// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	void clear();

private:
	void *m_item;
};

class Rva009CC470
{
	Rva0036CA00Str m_00;
	Rva0036CA00Str m_04;
	int m_08;
	int m_0C;

public:
	void reset();
};

void Rva009CC470::reset()
{
	m_00.clear();
	m_04.clear();
	m_08 = 0;
	m_0C = 0;
}
