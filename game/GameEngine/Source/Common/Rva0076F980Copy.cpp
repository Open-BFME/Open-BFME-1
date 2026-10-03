// cl: /O2 /Ob0
//
// Retail 0x0076F980 assigns both live subobjects: 0x00887C90 releases the
// destination string before retaining the source, and ILT 0x00007A63 reaches
// vector<AsciiString>::operator= at 0x000DE2C0.  This is therefore an
// assignment operator, not a copy constructor.

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

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

class Rva0076F980
{
	StringBase<char> m_00;
	Rva0076F980Mid m_04;
	int m_10;

public:
	Rva0076F980 &operator=(const Rva0076F980 &other);
};

Rva0076F980 &Rva0076F980::operator=(const Rva0076F980 &other)
{
	m_00.set(other.m_00);
	Rva0076F980MidAssign assign;
	assign.function = &j_00007a63;
	(m_04.*assign.member)(other.m_04);
	m_10 = other.m_10;
	return *this;
}
