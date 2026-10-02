// cl: /O2 /Ob0

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva003A4040
{
	int m_00;
	int m_04;
	Rva0036CA00Str m_08;
	Rva0036CA00Str m_0C;
	int m_10;

public:
	Rva003A4040 &operator=(const Rva003A4040 &other);
};

Rva003A4040 &Rva003A4040::operator=(const Rva003A4040 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	reinterpret_cast<StringBase<char> &>(m_08).set(
		reinterpret_cast<const StringBase<char> &>(other.m_08));
	reinterpret_cast<StringBase<char> &>(m_0C).set(
		reinterpret_cast<const StringBase<char> &>(other.m_0C));
	m_10 = other.m_10;
	return *this;
}
