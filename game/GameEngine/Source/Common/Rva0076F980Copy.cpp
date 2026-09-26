// cl: /O2 /Ob0
//
// Retail 0x0076F980 assigns both live subobjects: 0x00887C90 releases the
// destination string before retaining the source, and ILT 0x00007A63 reaches
// vector<AsciiString>::operator= at 0x000DE2C0.  This is therefore an
// assignment operator, not a copy constructor.

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

class Rva0076F980
{
	Rva0036CA00Str m_00;
	Rva0076F980Mid m_04;
	int m_10;

public:
	Rva0076F980 &operator=(const Rva0076F980 &other);
};

Rva0076F980 &Rva0076F980::operator=(const Rva0076F980 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_10 = other.m_10;
	return *this;
}
