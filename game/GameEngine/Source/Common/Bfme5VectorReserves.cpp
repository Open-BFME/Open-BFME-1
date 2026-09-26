// Three vector reserves.
//
// Each divides the byte spans by the element width to get the capacity and the
// used count -- the magic multiplies are the compiler's, not the source's --
// and returns at once when the capacity already covers the request. That
// comparison is unsigned, so the capacity and the request are both unsigned.
//
// Growing takes one of three arms: with storage already held, the elements are
// moved to a fresh block and the old one released; with none held and a
// request, the block comes from the size-dispatch helper; with none held and
// no request, the block is null. Only after that do the three pointers get
// written, and the used count is computed before the branch because every arm
// needs it.

void *bfmeNewAlloc(unsigned int bytes);				// retail 0x00881F30
void *bfmeAllocNode(unsigned int bytes);			// retail 0x0082E540

inline void *bfmeAllocate(unsigned int bytes)
{
	if (bytes > 0x80)
		return bfmeNewAlloc(bytes);

	return bfmeAllocNode(bytes);
}

struct BfmeElem_0023E120 { char m_bfmeBytes[0x1C]; };

class Gen_0023E120
{
public:
	void bfmeReserve(unsigned int count);
	BfmeElem_0023E120 *bfmeMoveTo(unsigned int count, BfmeElem_0023E120 *first, BfmeElem_0023E120 *last);	// retail 0x00041D85
	void bfmeReleaseOld(void);				// retail 0x00045557

private:
	BfmeElem_0023E120 *m_bfmeStart;				// +0x00
	BfmeElem_0023E120 *m_bfmeFinish;				// +0x04
	BfmeElem_0023E120 *m_bfmeEnd;				// +0x08
};

struct BfmeElem_00359A80 { char m_bfmeBytes[0x14]; };

class Gen_00359A80
{
public:
	void bfmeReserve(unsigned int count);
	BfmeElem_00359A80 *bfmeMoveTo(unsigned int count, BfmeElem_00359A80 *first, BfmeElem_00359A80 *last);	// retail 0x00014687
	void bfmeReleaseOld(void);				// retail 0x0002594B

private:
	BfmeElem_00359A80 *m_bfmeStart;				// +0x00
	BfmeElem_00359A80 *m_bfmeFinish;				// +0x04
	BfmeElem_00359A80 *m_bfmeEnd;				// +0x08
};

struct BfmeElem_00359B50 { char m_bfmeBytes[0x14]; };

class Gen_00359B50
{
public:
	void bfmeReserve(unsigned int count);
	BfmeElem_00359B50 *bfmeMoveTo(unsigned int count, BfmeElem_00359B50 *first, BfmeElem_00359B50 *last);	// retail 0x00004FD9
	void bfmeReleaseOld(void);				// retail 0x00015E56

private:
	BfmeElem_00359B50 *m_bfmeStart;				// +0x00
	BfmeElem_00359B50 *m_bfmeFinish;				// +0x04
	BfmeElem_00359B50 *m_bfmeEnd;				// +0x08
};

// ?bfmeReserve@Gen_0023E120@@QAEXI@Z
void Gen_0023E120::bfmeReserve(unsigned int count)
{
	BfmeElem_0023E120 *start = m_bfmeStart;

	if ((unsigned int)(m_bfmeEnd - start) >= count)
		return;

	unsigned int used = (unsigned int)(m_bfmeFinish - start);
	BfmeElem_0023E120 *block;

	if (start)
	{
		block = bfmeMoveTo(count, start, m_bfmeFinish);
		bfmeReleaseOld();
	}
	else if (count)
	{
		block = (BfmeElem_0023E120 *)bfmeAllocate(count * sizeof(BfmeElem_0023E120));
	}
	else
	{
		block = 0;
	}

	m_bfmeFinish = block + used;
	m_bfmeStart = block;
	m_bfmeEnd = block + count;
}

// ?bfmeReserve@Gen_00359A80@@QAEXI@Z
void Gen_00359A80::bfmeReserve(unsigned int count)
{
	BfmeElem_00359A80 *start = m_bfmeStart;

	if ((unsigned int)(m_bfmeEnd - start) >= count)
		return;

	unsigned int used = (unsigned int)(m_bfmeFinish - start);
	BfmeElem_00359A80 *block;

	if (start)
	{
		block = bfmeMoveTo(count, start, m_bfmeFinish);
		bfmeReleaseOld();
	}
	else if (count)
	{
		block = (BfmeElem_00359A80 *)bfmeAllocate(count * sizeof(BfmeElem_00359A80));
	}
	else
	{
		block = 0;
	}

	m_bfmeFinish = block + used;
	m_bfmeStart = block;
	m_bfmeEnd = block + count;
}

// ?bfmeReserve@Gen_00359B50@@QAEXI@Z
void Gen_00359B50::bfmeReserve(unsigned int count)
{
	BfmeElem_00359B50 *start = m_bfmeStart;

	if ((unsigned int)(m_bfmeEnd - start) >= count)
		return;

	unsigned int used = (unsigned int)(m_bfmeFinish - start);
	BfmeElem_00359B50 *block;

	if (start)
	{
		block = bfmeMoveTo(count, start, m_bfmeFinish);
		bfmeReleaseOld();
	}
	else if (count)
	{
		block = (BfmeElem_00359B50 *)bfmeAllocate(count * sizeof(BfmeElem_00359B50));
	}
	else
	{
		block = 0;
	}

	m_bfmeFinish = block + used;
	m_bfmeStart = block;
	m_bfmeEnd = block + count;
}
