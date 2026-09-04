// Two-part record equality at retail RVA 0x000AA4A0.

class AsciiString
{
public:
	int compare(const AsciiString &other) const;

private:
	void *m_data;
};

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
