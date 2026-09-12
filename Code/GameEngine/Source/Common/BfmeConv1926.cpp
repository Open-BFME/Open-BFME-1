class UnicodeString
{
public:
	void set(const UnicodeString &other);

	~UnicodeString() { releaseBufferCQ(); }

	void releaseBufferCQ();

	void *m_data;
};

struct BfmePairCQ
{
	int m_bfmeACQ;
	int m_bfmeBCQ;
};

class BfmeHostCQ
{
public:
	void bfmeApplyCQ(UnicodeString text, BfmePairCQ *pair);

	unsigned char m_bfmeHeadCQ[0x174];
	UnicodeString m_bfmeTextCQ;
	int m_bfmeACQ;
	int m_bfmeBCQ;
};

void BfmeHostCQ::bfmeApplyCQ(UnicodeString text, BfmePairCQ *pair)
{
	UnicodeString *dst = &m_bfmeTextCQ;

	dst->set(text);

	m_bfmeACQ = pair->m_bfmeACQ;
	m_bfmeBCQ = pair->m_bfmeBCQ;
}
