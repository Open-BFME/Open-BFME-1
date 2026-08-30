// cl: /DNDEBUG /MD /EHsc

struct BfmeNestedFlags
{
	unsigned char m_pad00[0x20];
	unsigned char m_primary : 1;
};

class BfmeNestedFlagOwner
{
public:
	char hasPrimaryFlag() const;

private:
	unsigned char m_pad00[0x10];
	BfmeNestedFlags *m_flags;
};

char BfmeNestedFlagOwner::hasPrimaryFlag() const
{
	return m_flags->m_primary;
}
