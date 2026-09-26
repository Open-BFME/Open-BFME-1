// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	void clear();

private:
	void *m_item;
};

class Rva00466730
{
	Rva0036CA00Str m_00;
	Rva0036CA00Str m_04;
	int m_08;
	int m_0C;
	unsigned char m_flags;

public:
	void reset();
};

void Rva00466730::reset()
{
	m_00.clear();
	m_04.clear();
	m_flags &= 0xF4;
	m_08 = 0;
	m_0C = -1;
}
