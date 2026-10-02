// cl: /O2 /Ob0

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class Rva0036CA00Str
{
private:
	void *m_item;
};

class Rva0075B750
{
	Rva0036CA00Str m_00;
	Rva0036CA00Str m_04;
	Rva0036CA00Str m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	char m_24;
	char m_25;
	int m_28;
	int m_2C;
	int m_30;
	char m_34;

public:
	Rva0075B750 &operator=(const Rva0075B750 &other);
};

Rva0075B750 &Rva0075B750::operator=(const Rva0075B750 &other)
{
	if (this == &other)
		return *this;
	reinterpret_cast<StringBase<char> &>(m_00).set(
		reinterpret_cast<const StringBase<char> &>(other.m_00));
	reinterpret_cast<StringBase<char> &>(m_04).set(
		reinterpret_cast<const StringBase<char> &>(other.m_04));
	reinterpret_cast<StringBase<char> &>(m_08).set(
		reinterpret_cast<const StringBase<char> &>(other.m_08));
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1C = other.m_1C;
	m_20 = other.m_20;
	m_24 = other.m_24;
	m_25 = other.m_25;
	m_28 = other.m_28;
	m_2C = other.m_2C;
	m_30 = other.m_30;
	m_34 = other.m_34;
	return *this;
}
