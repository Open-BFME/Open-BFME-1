// cl: /O2 /Ob0 /Igame

// Retail +0x3C calls StringBase<char>::set at RVA 0x00887C90.
// Its void ABI does not implement the former opaque reference-returning
// assignment alias. Use the canonical string field and callee directly.
#include "Libraries/Source/WWVegas/WWLib/string_base.h"

struct Rva000FC640Pod
{
	int a;
	int b;
	int c;
};

class Rva000FC640
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	Rva000FC640Pod m_10;
	StringBase<char> m_1C;
	char m_20;

public:
	Rva000FC640 &operator=(const Rva000FC640 &other);
};

Rva000FC640 &Rva000FC640::operator=(const Rva000FC640 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_1C.set(other.m_1C);
	m_20 = other.m_20;
	return *this;
}
