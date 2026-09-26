// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva000A8490Mid10
{
public:
	Rva000A8490Mid10 &operator=(const Rva000A8490Mid10 &other);

private:
	int m_00;
	int m_04;
	int m_08;
};

class Rva000A8490Mid24
{
public:
	Rva000A8490Mid24 &operator=(const Rva000A8490Mid24 &other);

private:
	int m_00;
};

class Rva000A8490
{
	virtual void handle();
	Rva0036CA00Str m_04;
	Rva0036CA00Str m_08;
	char m_0C;
	Rva000A8490Mid10 m_10;
	char m_1C;
	int m_20;
	Rva000A8490Mid24 m_24;

public:
	Rva000A8490 &operator=(const Rva000A8490 &other);
};

Rva000A8490 &Rva000A8490::operator=(const Rva000A8490 &other)
{
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_1C = other.m_1C;
	m_20 = other.m_20;
	m_24 = other.m_24;
	return *this;
}
