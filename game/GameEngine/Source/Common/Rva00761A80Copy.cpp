// cl: /O2 /Ob0 /Igame/Libraries/Source/WWVegas/WWLib

#include "string_base.h"

class BfmeSubA
{
public:

private:
	void *m_item;
};

class Rva00761A80
{
	int m_00;
	int m_04;
	int m_08;
	BfmeSubA m_0c;
	int m_10;

public:
	Rva00761A80(const Rva00761A80 &other);
};

Rva00761A80::Rva00761A80(const Rva00761A80 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_08 = other.m_08;
	((StringBase<char> *)&m_0c)->set(*(const StringBase<char> *)&other.m_0c);
	m_10 = other.m_10;
}
