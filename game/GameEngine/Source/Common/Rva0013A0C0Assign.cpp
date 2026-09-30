// cl: /O2 /Ob0 /Igame

// Retail's ten string calls reach void StringBase<char>::set directly at
// RVA 0x00887C90. Adopt its canonical layout and signature; the enclosing
// address-derived owner and its public void assignment signature are retained.
#include "Libraries/Source/WWVegas/WWLib/string_base.h"


class Rva0013A0C0
{
	StringBase<char> m_00;
	StringBase<char> m_04;
	StringBase<char> m_08;
	StringBase<char> m_0C;
	StringBase<char> m_10;
	int m_14;
	int m_18;
	StringBase<char> m_1C;
	StringBase<char> m_20;
	int m_24;
	StringBase<char> m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	StringBase<char> m_3C;
	int m_40;
	StringBase<char> m_44;

public:
	void operator=(const Rva0013A0C0 &other);
};

void Rva0013A0C0::operator=(const Rva0013A0C0 &other)
{
	m_00.set(other.m_00);
	m_04.set(other.m_04);
	m_08.set(other.m_08);
	m_0C.set(other.m_0C);
	m_10.set(other.m_10);
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1C.set(other.m_1C);
	m_20.set(other.m_20);
	m_24 = other.m_24;
	m_28.set(other.m_28);
	m_2C = other.m_2C;
	m_30 = other.m_30;
	m_34 = other.m_34;
	m_38 = other.m_38;
	m_3C.set(other.m_3C);
	m_40 = other.m_40;
	m_44.set(other.m_44);
}
