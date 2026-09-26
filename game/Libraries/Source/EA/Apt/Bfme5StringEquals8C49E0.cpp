// Compare shared string blocks by size, identity, then text.
struct BfmeStringBlock8C49E0
{
	unsigned short m_refs;
	unsigned short m_length;
	unsigned m_capacity;
	char m_text[1];
};

int __cdecl bfmeCompareVSC(const char *, const char *);

class Gen_008C49E0
{
public:
	unsigned char bfmeStringEquals8C49E0(const Gen_008C49E0 &other) const;

private:
	BfmeStringBlock8C49E0 *m_block;
};

unsigned char Gen_008C49E0::bfmeStringEquals8C49E0(const Gen_008C49E0 &other) const
{
	BfmeStringBlock8C49E0 *right = other.m_block;
	BfmeStringBlock8C49E0 *left = m_block;
	if (left->m_length != right->m_length)
		return false;
	if (left == right)
		return true;
	return bfmeCompareVSC(left->m_text, right->m_text) == 0;
}
