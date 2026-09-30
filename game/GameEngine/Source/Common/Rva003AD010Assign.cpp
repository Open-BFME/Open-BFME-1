// cl: /O2 /Ob0 /Igame

// Retail string calls target the existing void StringBase<char>::set body
// at RVA 0x00887C90. Adopt its canonical header and exact signature.
#include "Libraries/Source/WWVegas/WWLib/string_base.h"


class Rva003AD010
{
	virtual void handle();
	StringBase<char> m_04;
	int m_08;
	int m_0C;
	char m_10;
	StringBase<char> m_14;
	StringBase<char> m_18;
	int m_1C;

public:
	Rva003AD010 &operator=(const Rva003AD010 &other);
};

Rva003AD010 &Rva003AD010::operator=(const Rva003AD010 &other)
{
	m_04.set(other.m_04);
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_14.set(other.m_14);
	m_18.set(other.m_18);
	m_1C = other.m_1C;
	return *this;
}
