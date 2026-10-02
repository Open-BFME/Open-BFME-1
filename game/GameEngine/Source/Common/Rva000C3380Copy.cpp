// cl: /O2 /Ob0
// The three members at +0/+4/+8 are narrow strings: retail's body calls
// StringBase<char>::set (0x00887C90, ?set@?$StringBase@D@@QAEXABV1@@Z) once per
// member rather than any copy constructor, so the placeholder
// Rva0036CA00Str (whose copy ctor nothing defined) is spelled as the real
// StringBase<char>, viewed through a local POD because StringBase's default
// constructor is private.
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

struct Rva0036CA00Str
{
	void *m_item;
};

class Rva000C3380
{
	Rva0036CA00Str m_00;
	Rva0036CA00Str m_04;
	Rva0036CA00Str m_08;
	char m_0C;
	int m_10;
	char m_14;
	int m_18;

public:
	Rva000C3380(const Rva000C3380 &other);
};

Rva000C3380::Rva000C3380(const Rva000C3380 &other)
{
	((StringBase<char> *)&m_00)->set(*(const StringBase<char> *)&other.m_00);
	((StringBase<char> *)&m_04)->set(*(const StringBase<char> *)&other.m_04);
	((StringBase<char> *)&m_08)->set(*(const StringBase<char> *)&other.m_08);
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
}