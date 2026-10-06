// cl: /Igame/Libraries/Source/WWVegas/WWLib
// Two-part record equality at retail RVA 0x000AA4A0.

#include "ascii_string.h"

template <> inline int StringBase<char>::compare(const StringBase<char> &str) const
{
	int otherLength = str.m_data ? str.m_data->length : 0;
	const char *otherData = str.m_data ? str.m_data->data : (const char *)"";
	int length = m_data ? m_data->length : 0;
	const char *data = m_data ? m_data->data : (const char *)"";
	int result = memcmp(data, otherData, length < otherLength ? length : otherLength);
	return result ? result : length - otherLength;
}

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
	if (m_member.StringBase<char>::compare(other.m_member) == 0 && m_kind == other.m_kind)
		return true;
	return false;
}
