// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva003B3080
{
	virtual void handle();
	Rva0036CA00Str m_04;
	Rva0036CA00Str m_08;
	Rva0036CA00Str m_0C;
	char m_10;

public:
	Rva003B3080 &operator=(const Rva003B3080 &other);
};

Rva003B3080 &Rva003B3080::operator=(const Rva003B3080 &other)
{
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	return *this;
}
