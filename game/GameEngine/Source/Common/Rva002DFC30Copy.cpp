// cl: /O2 /Ob0
// The member copy at 0x00887C90 is StringBase<char>::set, the
// ?$StringBase@D row (StringBase.cpp); the ModelConditionInfo copy ctor and
// AudioEventRTS::operator= rows at that address are ICF aliases of the same
// body. The string field is one pointer wide, so the local view casts onto the
// real StringBase.
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

struct Rva00887C90String
{
	void *m_data;
};

class Rva002DFC30
{
	int m_00;
	Rva00887C90String m_04;
	char m_08;

public:
	Rva002DFC30(const Rva002DFC30 &other);
};

Rva002DFC30::Rva002DFC30(const Rva002DFC30 &other)
	: m_00(other.m_00)
{
	reinterpret_cast<StringBase<char> *>(&m_04)->set(
		*reinterpret_cast<const StringBase<char> *>(&other.m_04));
	m_08 = other.m_08;
}