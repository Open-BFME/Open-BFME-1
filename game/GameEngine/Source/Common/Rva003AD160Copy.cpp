// cl: /O2 /Ob0

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class Rva0036CA00Str
{
private:
	void *m_item;
};

class Rva003AD160
{
	Rva0036CA00Str m_00;
	Rva0036CA00Str m_04;
	Rva0036CA00Str m_08;

public:
	Rva003AD160(const Rva003AD160 &other);
};

Rva003AD160::Rva003AD160(const Rva003AD160 &other)
{
	((StringBase<char> *)&m_00)->set(*(const StringBase<char> *)&other.m_00);
	((StringBase<char> *)&m_04)->set(*(const StringBase<char> *)&other.m_04);
	((StringBase<char> *)&m_08)->set(*(const StringBase<char> *)&other.m_08);
}
