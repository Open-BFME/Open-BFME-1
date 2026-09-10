// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// ?bfmeAppend@Gen003B1B40@@QAEXPAVBfmeItemXN@@@Z
// STLport vector push_back inlined into the owning member at retail 0x003B1B40.
// The vector is bound once as a reference so retail materialises the vector
// address in ecx; the element copy is inlined rather than an out-of-line callee.

extern "C" char bfmeVftXN[];

class BfmeItemXN
{
public:
	void *m_bfmeVfptrXN;
	int m_bfmeAXN;
	unsigned char m_bfmeBXN;
	char m_bfmePadXN[3];
	int m_bfmeCXN;
};

class BfmeVecXN
{
public:
	void bfmeGrowXN(BfmeItemXN *position, BfmeItemXN *value, BfmeItemXN **slot,
		int fillLength, int atEnd);

	BfmeItemXN *m_bfmeStartXN;
	BfmeItemXN *m_bfmeFinishXN;
	BfmeItemXN *m_bfmeCapXN;
};

class Gen003B1B40
{
public:
	void bfmeAppend(BfmeItemXN *value);

private:
	char m_bfmeHeadXN[0xa8];
	BfmeVecXN m_bfmeVecXN;
};

void Gen003B1B40::bfmeAppend(BfmeItemXN *value)
{
	BfmeVecXN &items = m_bfmeVecXN;

	if (items.m_bfmeFinishXN != items.m_bfmeCapXN)
	{
		BfmeItemXN *destination = items.m_bfmeFinishXN;

		if (destination != 0)
		{
			const BfmeItemXN *source = value;

			destination->m_bfmeVfptrXN = bfmeVftXN;
			destination->m_bfmeAXN = source->m_bfmeAXN;
			destination->m_bfmeBXN = source->m_bfmeBXN;
			destination->m_bfmeCXN = source->m_bfmeCXN;
		}

		++items.m_bfmeFinishXN;
	}
	else
	{
		items.bfmeGrowXN(items.m_bfmeFinishXN, value, &value, 1, 1);
	}
}
