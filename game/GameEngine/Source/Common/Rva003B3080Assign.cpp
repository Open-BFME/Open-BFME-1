// cl: /O2 /Ob0 /Igame

// Retail string calls target the existing void StringBase<char>::set body
// at RVA 0x00887C90. Adopt its canonical header and exact signature.
#include "Libraries/Source/WWVegas/WWLib/string_base.h"


class Rva003B3080
{
	virtual void handle();
	StringBase<char> m_04;
	StringBase<char> m_08;
	StringBase<char> m_0C;
	char m_10;

public:
	Rva003B3080 &operator=(const Rva003B3080 &other);
};

Rva003B3080 &Rva003B3080::operator=(const Rva003B3080 &other)
{
	m_04.set(other.m_04);
	m_08.set(other.m_08);
	m_0C.set(other.m_0C);
	m_10 = other.m_10;
	return *this;
}
