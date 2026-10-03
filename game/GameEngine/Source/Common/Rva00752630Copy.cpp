// cl: /O2 /Ob0 /Igame/Libraries/Source/WWVegas/WWLib

#include "string_base.h"

class BfmeSubA
{
public:

private:
	void *m_item;
};

class Rva00752630
{
	BfmeSubA m_00;
	char m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;

public:
	Rva00752630(const Rva00752630 &other);
};

Rva00752630::Rva00752630(const Rva00752630 &other)
{
	((StringBase<char> *)&m_00)->set(*(const StringBase<char> *)&other.m_00);
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0c = other.m_0c;
	m_10 = other.m_10;
	m_14 = other.m_14;
}
