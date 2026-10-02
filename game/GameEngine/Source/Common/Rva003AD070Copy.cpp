// cl: /O2 /Ob0

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class BfmeSubA
{
private:
	void *m_item;
};

class Rva003AD070
{
	int m_00;
	BfmeSubA m_04;
	char m_08;

public:
	Rva003AD070(const Rva003AD070 &other);
};

Rva003AD070::Rva003AD070(const Rva003AD070 &other)
{
	((StringBase<char> *)&m_04)->set(*(const StringBase<char> *)&other.m_04);
	m_08 = other.m_08;
}
