// cl: /O2 /Ob0

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class Rva0036CA00Str
{
	void *m_item;
};

class Rva00133290
{
	Rva0036CA00Str m_00;
	Rva0036CA00Str m_04;
	int m_08;
	int m_0C;
	char m_10;
	char m_11;

public:
	Rva00133290(const Rva00133290 &other);
};

Rva00133290::Rva00133290(const Rva00133290 &other)
{
	reinterpret_cast<StringBase<char> &>(m_00).set(
		*reinterpret_cast<const StringBase<char> *>(&other.m_00));
	reinterpret_cast<StringBase<char> &>(m_04).set(
		*reinterpret_cast<const StringBase<char> *>(&other.m_04));
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_11 = other.m_11;
}
