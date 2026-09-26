// Saturate a twelve-bit local counter and bump the enclosing owner's count.
struct BfmeOwner8D5F40
{
	char m_reserved[0x60];
	unsigned short m_count;
};

class Gen_008D5F40
{
public:
	void bfmeIncrementPacked(void);

private:
	int m_reserved;
	unsigned m_flags;
	char m_other[0x24];
	BfmeOwner8D5F40 *m_owner;
};

void Gen_008D5F40::bfmeIncrementPacked(void)
{
	unsigned count = ((m_flags >> 16) & 0xfff) + 1;
	if (count > 0xfff)
		count = 0xfff;
	m_flags = (m_flags & 0xf000ffff) | (count << 16);
	++m_owner->m_count;
}
