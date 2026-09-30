// cl: /O2 /Ob0 /Igame

// Both retail string calls reach void StringBase<char>::set directly at
// RVA 0x00887C90. Reuse its native layout and signature while preserving
// the opaque owner, record layout, and public assignment ABI.
#include "Libraries/Source/WWVegas/WWLib/string_base.h"


struct Rva0014A470Pod
{
	int a[21];
};

class Rva0014A470
{
	int m_00;
	StringBase<char> m_04;
	int m_08;
	int m_0C;
	int m_10;
	Rva0014A470Pod m_14;
	Rva0014A470Pod m_68;
	Rva0014A470Pod m_BC;
	Rva0014A470Pod m_110;
	Rva0014A470Pod m_164;
	StringBase<char> m_1B8;
	int m_1BC;

public:
	Rva0014A470 &operator=(const Rva0014A470 &other);
};

Rva0014A470 &Rva0014A470::operator=(const Rva0014A470 &other)
{
	m_04.set(other.m_04);
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_68 = other.m_68;
	m_BC = other.m_BC;
	m_110 = other.m_110;
	m_164 = other.m_164;
	m_1B8.set(other.m_1B8);
	m_1BC = other.m_1BC;
	return *this;
}
