// cl: /O2 /Ob0 /Igame/Libraries/Source/WWVegas/WWLib

// The 0x24 member is the wide string: retail's call at 0x0010CFF0+0x51 targets
// 0x00888530, which is StringBase<unsigned short>::set (it mangles @G for
// unsigned short), not an operator=.  One pointer wide, same layout as before.
#include "string_base.h"

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

struct Rva0010CFF0Pod
{
	int a;
	int b;
	int c;
	int d;
};

class Rva0010CFF0
{
	Rva0036CA00Str m_00;
	Rva0036CA00Str m_04;
	Rva0036CA00Str m_08;
	Rva0010CFF0Pod m_0C;
	Rva0036CA00Str m_1C;
	int m_20;
	StringBase<unsigned short> m_24;
	int m_28;
	Rva0036CA00Str m_2C;

public:
	Rva0010CFF0 &operator=(const Rva0010CFF0 &other);
};

Rva0010CFF0 &Rva0010CFF0::operator=(const Rva0010CFF0 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_1C = other.m_1C;
	m_20 = other.m_20;
	m_24.set(other.m_24);
	m_28 = other.m_28;
	m_2C = other.m_2C;
	return *this;
}
