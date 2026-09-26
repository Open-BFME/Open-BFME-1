// cl: /Igame/Libraries/Source/WWVegas/WWLib
// Two-part record equality at retail RVA 0x000AA4A0.

#include "ascii_string.h"

class BfmeRecordAA4A0
{
public:
	int operator==(const BfmeRecordAA4A0 &other) const;

private:
	int m_head;
	AsciiString m_member;
	unsigned short m_kind;
};

int BfmeRecordAA4A0::operator==(const BfmeRecordAA4A0 &other) const
{
	if (m_member.compare(other.m_member) == 0 && m_kind == other.m_kind)
		return true;
	return false;
}
