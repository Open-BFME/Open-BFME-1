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

class Rva0034F780
{
	virtual void handle();
	Rva0036CA00Str m_04;
	Rva0076F980Mid m_08;

public:
	Rva0034F780 &operator=(const Rva0034F780 &other);
};

Rva0034F780 &Rva0034F780::operator=(const Rva0034F780 &other)
{
	m_04 = other.m_04;
	m_08 = other.m_08;
	return *this;
}
