// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva003AD010
{
	virtual void handle();
	Rva0036CA00Str m_04;
	int m_08;
	int m_0C;
	char m_10;
	Rva0036CA00Str m_14;
	Rva0036CA00Str m_18;
	int m_1C;

public:
	Rva003AD010 &operator=(const Rva003AD010 &other);
};

Rva003AD010 &Rva003AD010::operator=(const Rva003AD010 &other)
{
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1C = other.m_1C;
	return *this;
}
