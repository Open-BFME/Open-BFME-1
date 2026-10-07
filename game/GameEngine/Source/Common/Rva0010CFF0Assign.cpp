// cl: /O2 /Ob0 /Igame/Libraries/Source/WWVegas/WWLib

// The 0x24 member is the wide string: retail's call at 0x0010CFF0+0x51 targets
// 0x00888530, which is StringBase<unsigned short>::set (it mangles @G for
// unsigned short), not an operator=.  One pointer wide, same layout as before.
// The narrow members call 0x00887C90, StringBase<char>::set.
#include "string_base.h"

struct Rva0010CFF0Pod
{
	int a;
	int b;
	int c;
	int d;
};

class Rva0010CFF0
{
	StringBase<char> m_00;
	StringBase<char> m_04;
	StringBase<char> m_08;
	Rva0010CFF0Pod m_0C;
	StringBase<char> m_1C;
	int m_20;
	StringBase<unsigned short> m_24;
	int m_28;
	StringBase<char> m_2C;

public:
	Rva0010CFF0 &operator=(const Rva0010CFF0 &other);
};

Rva0010CFF0 &Rva0010CFF0::operator=(const Rva0010CFF0 &other)
{
	m_00.set(other.m_00);
	m_04.set(other.m_04);
	m_08.set(other.m_08);
	m_0C = other.m_0C;
	m_1C.set(other.m_1C);
	m_20 = other.m_20;
	m_24.set(other.m_24);
	m_28 = other.m_28;
	m_2C.set(other.m_2C);
	return *this;
}
