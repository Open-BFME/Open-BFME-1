// cl: /O2 /Ob0 /Igame

// Retail +0x24 calls void StringBase<char>::set at RVA 0x00887C90.
// Reuse the canonical string field and signature; no assignment alias is needed.
#include "Libraries/Source/WWVegas/WWLib/string_base.h"

struct Rva000FC550Pod
{
	int a;
	int b;
	int c;
};

class Rva000FC550
{
	Rva000FC550Pod m_00;
	StringBase<char> m_0C;

public:
	Rva000FC550 &operator=(const Rva000FC550 &other);
};

Rva000FC550 &Rva000FC550::operator=(const Rva000FC550 &other)
{
	m_00 = other.m_00;
	m_0C.set(other.m_0C);
	return *this;
}
