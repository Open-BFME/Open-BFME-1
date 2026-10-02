// cl: /O2 /Ob0

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class Rva0036CA00Str
{
private:
	void *m_item;
};

class Rva009CEA90
{
	Rva0036CA00Str m_00;
	Rva0036CA00Str m_04;
	int m_08;
	int m_0C;

public:
	Rva009CEA90(const Rva009CEA90 &other);
};

Rva009CEA90::Rva009CEA90(const Rva009CEA90 &other)
{
	((StringBase<char> *)&m_00)->set(*(const StringBase<char> *)&other.m_00);
	((StringBase<char> *)&m_04)->set(*(const StringBase<char> *)&other.m_04);
	m_08 = other.m_08;
	m_0C = other.m_0C;
}
