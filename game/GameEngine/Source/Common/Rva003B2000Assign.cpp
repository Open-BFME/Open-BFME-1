// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva0076F980Mid
{
public:
	Rva0076F980Mid &operator=(const Rva0076F980Mid &other);

private:
	int m_00;
	int m_04;
	int m_08;
};

class Rva003B2000
{
	virtual void handle();
	Rva0036CA00Str m_04;
	Rva0076F980Mid m_08;
	int m_14;
	int m_18;
	int m_1C;
	char m_20;
	char m_21;
	char m_22;

public:
	Rva003B2000 &operator=(const Rva003B2000 &other);
};

Rva003B2000 &Rva003B2000::operator=(const Rva003B2000 &other)
{
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1C = other.m_1C;
	m_20 = other.m_20;
	m_21 = other.m_21;
	m_22 = other.m_22;
	return *this;
}
