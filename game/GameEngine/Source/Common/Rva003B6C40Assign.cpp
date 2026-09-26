// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva003B6C40Mid
{
public:
	Rva003B6C40Mid &operator=(const Rva003B6C40Mid &other);

private:
	int m_00;
	int m_04;
	int m_08;
};

class Rva003B6C40
{
	virtual void handle();
	Rva0036CA00Str m_04;
	int m_08;
	Rva003B6C40Mid m_0C;
	int m_18;
	char m_1C;

public:
	Rva003B6C40 &operator=(const Rva003B6C40 &other);
};

Rva003B6C40 &Rva003B6C40::operator=(const Rva003B6C40 &other)
{
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_18 = other.m_18;
	m_1C = other.m_1C;
	return *this;
}
