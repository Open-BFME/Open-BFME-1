// The body at retail RVA 0x003D0190 inserts a key when a five-argument search
// misses it.  The search helper is pinned as bfmeLowerRQ at ILT 0x00016B21.
// The vector insert helper is pinned as bfmeInsertRQ at ILT 0x00034D7E.
// No caller, vtable slot, or string identifies the owner.
// The class therefore keeps its address-derived name.

struct BfmeCmpRQ
{
	char m_bfmeRawRQ;
};

void ** __cdecl bfmeLowerRQ(void **begin, void **end, void **key, BfmeCmpRQ compare, int spare);

class BfmeVecRQ
{
public:
	void bfmeInsertRQ(void **where, void **key);

	void **m_bfmeBeginRQ;
	void **m_bfmeEndRQ;
};

class Rva003D0190
{
public:
	void ensure(void *key);

	unsigned char m_bfmeHeadRQ[0x30];
	BfmeVecRQ m_bfmeVecRQ;
};

void Rva003D0190::ensure(void *key)
{
	void **end = m_bfmeVecRQ.m_bfmeEndRQ;
	BfmeCmpRQ compare;
	compare.m_bfmeRawRQ = 0;
	void **found = bfmeLowerRQ(m_bfmeVecRQ.m_bfmeBeginRQ,
		end, &key, compare, 0);

	if (found == end || *found != key)
		m_bfmeVecRQ.bfmeInsertRQ(found, &key);
}
