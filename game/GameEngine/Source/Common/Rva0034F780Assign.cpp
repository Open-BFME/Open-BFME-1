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

void j_00007a63();

// Keep the target's member-call ABI while referring to its recorded thunk name.
union Rva0076F980MidAssign
{
	void (*function)(void);
	Rva0076F980Mid &(Rva0076F980Mid::*member)(const Rva0076F980Mid &);
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
	Rva0076F980MidAssign assign;
	assign.function = &j_00007a63;
	(m_08.*assign.member)(other.m_08);
	return *this;
}
