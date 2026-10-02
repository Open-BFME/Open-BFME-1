// cl: /O2 /Ob0
// The +4 sub-object is a StringBase<char>: retail's body (0x001C0B40) loads
// both ends and calls StringBase<char>::set (0x00887C90) with this+4 as the
// destination and other+4 as the source, which is what a member copy spelled
// against the real class spells. StringBase's own constructors are private and
// are defined elsewhere, so the member is held at its own size and viewed
// through the real header at the two uses that matter.

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class Rva001C0B40
{
	int m_00;
	void *m_04;					// StringBase<char>, seen through its own size
	int m_08;
	int m_0c;

public:
	Rva001C0B40(const Rva001C0B40 &other);
};

Rva001C0B40::Rva001C0B40(const Rva001C0B40 &other)
	: m_00(other.m_00)
{
	reinterpret_cast<StringBase<char> *>(&m_04)->set(
		*reinterpret_cast<const StringBase<char> *>(&other.m_04));
	m_08 = other.m_08;
	m_0c = other.m_0c;
}