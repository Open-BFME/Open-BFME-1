// cl: /O2 /Ob0 /Igame/Libraries/Source/WWVegas/WWLib

#include <string_base.h>

class Rva0036CA00Str
{
public:
private:
	void *m_item;
};

class Rva00338CA0
{
	Rva0036CA00Str m_00;
	Rva0036CA00Str m_04;
	int m_08;
	Rva0036CA00Str m_0C;

public:
	Rva00338CA0(const Rva00338CA0 &other);
};

Rva00338CA0::Rva00338CA0(const Rva00338CA0 &other)
{
	((StringBase<char> *)&m_00)->set(*(const StringBase<char> *)&other.m_00);
	((StringBase<char> *)&m_04)->set(*(const StringBase<char> *)&other.m_04);
	m_08 = other.m_08;
	((StringBase<char> *)&m_0C)->set(*(const StringBase<char> *)&other.m_0C);
}
