// cl: /O2 /Ob0

// Two narrow string heads plus a dword. Retail copies each string head through
// the shared StringBase<char>::set body (0x00887C90) and then the dword; the
// head is declared opaquely here so nothing but that proven member call is
// assumed about it.
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class Rva0036CA00Str
{
	int m_head;
};

class Rva0036CA00
{
	Rva0036CA00Str m_00;
	Rva0036CA00Str m_04;
	int m_08;

public:
	Rva0036CA00(const Rva0036CA00 &other);
};

Rva0036CA00::Rva0036CA00(const Rva0036CA00 &other)
{
	reinterpret_cast<StringBase<char> *>(&m_00)->set(*reinterpret_cast<const StringBase<char> *>(&other.m_00));
	reinterpret_cast<StringBase<char> *>(&m_04)->set(*reinterpret_cast<const StringBase<char> *>(&other.m_04));
	m_08 = other.m_08;
}
