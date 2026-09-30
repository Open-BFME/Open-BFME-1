// cl: /O2 /Ob0 /Igame

// Retail string calls target the existing void StringBase<char>::set body
// at RVA 0x00887C90. Adopt its canonical header and exact signature.
#include "Libraries/Source/WWVegas/WWLib/string_base.h"


struct Rva006EAFA0Pod
{
	int a[10];
};

class Rva006EAFA0
{
	StringBase<char> m_00;
	StringBase<char> m_04;
	Rva006EAFA0Pod m_08;
	int m_30;
	int m_34;

public:
	Rva006EAFA0 &operator=(const Rva006EAFA0 &other);
};

Rva006EAFA0 &Rva006EAFA0::operator=(const Rva006EAFA0 &other)
{
	m_00.set(other.m_00);
	m_04.set(other.m_04);
	m_08 = other.m_08;
	m_30 = other.m_30;
	m_34 = other.m_34;
	return *this;
}
