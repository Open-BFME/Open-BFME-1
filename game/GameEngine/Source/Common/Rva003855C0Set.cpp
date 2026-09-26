// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

extern Rva0036CA00Str Rva01336E50Str;

class Rva003855C0
{
	char m_00[0x174];
	Rva0036CA00Str m_174;
	int m_178;
	int m_17C;

public:
	void reset();
};

void Rva003855C0::reset()
{
	m_174 = Rva01336E50Str;
	m_178 = 0;
	m_17C = 0;
}
