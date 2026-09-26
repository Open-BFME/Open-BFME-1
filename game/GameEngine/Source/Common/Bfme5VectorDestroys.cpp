// Four vector destroys.
//
// Each runs the destructor over every live element and then frees the block,
// picking the free by byte size the same way the matching allocate picks its
// allocator.
//
// The element destructor goes through slot zero with a zero flag, which is a
// direct destructor call on a polymorphic element rather than a delete. The
// walk runs from start to finish; the release reads the start again afterwards
// and measures against end, so it covers the capacity and not just the live
// range.
//
// The shift pair around the size is the element width divided out of the
// pointer span and multiplied straight back: five for the thirty-two byte
// elements, four for the sixteen byte ones.

void __cdecl bfmeFreeScalar(void *block);			// retail 0x00881EB0
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

inline void bfmeRelease(void *block, unsigned int bytes)
{
	if (bytes > 0x80)
		bfmeFreeScalar(block);
	else
		bfmeDeallocate(block, bytes);
}

class BfmeVecElem_003AFBB0
{
public:
	virtual ~BfmeVecElem_003AFBB0(void);

private:
	char m_bfmePad[0x1C];
};

class Gen_003AFBB0
{
public:
	void bfmeDestroy(void);

private:
	BfmeVecElem_003AFBB0 *m_bfmeStart;			// +0x00
	BfmeVecElem_003AFBB0 *m_bfmeFinish;			// +0x04
	BfmeVecElem_003AFBB0 *m_bfmeEnd;			// +0x08
};

class BfmeVecElem_003AFDA0
{
public:
	virtual ~BfmeVecElem_003AFDA0(void);

private:
	char m_bfmePad[0x1C];
};

class Gen_003AFDA0
{
public:
	void bfmeDestroy(void);

private:
	BfmeVecElem_003AFDA0 *m_bfmeStart;			// +0x00
	BfmeVecElem_003AFDA0 *m_bfmeFinish;			// +0x04
	BfmeVecElem_003AFDA0 *m_bfmeEnd;			// +0x08
};

class BfmeVecElem_003AFF10
{
public:
	virtual ~BfmeVecElem_003AFF10(void);

private:
	char m_bfmePad[0xC];
};

class Gen_003AFF10
{
public:
	void bfmeDestroy(void);

private:
	BfmeVecElem_003AFF10 *m_bfmeStart;			// +0x00
	BfmeVecElem_003AFF10 *m_bfmeFinish;			// +0x04
	BfmeVecElem_003AFF10 *m_bfmeEnd;			// +0x08
};

class BfmeVecElem_003AFF80
{
public:
	virtual ~BfmeVecElem_003AFF80(void);

private:
	char m_bfmePad[0xC];
};

class Gen_003AFF80
{
public:
	void bfmeDestroy(void);

private:
	BfmeVecElem_003AFF80 *m_bfmeStart;			// +0x00
	BfmeVecElem_003AFF80 *m_bfmeFinish;			// +0x04
	BfmeVecElem_003AFF80 *m_bfmeEnd;			// +0x08
};

// ?bfmeDestroy@Gen_003AFBB0@@QAEXXZ
void Gen_003AFBB0::bfmeDestroy(void)
{
	BfmeVecElem_003AFBB0 *first = m_bfmeStart;
	BfmeVecElem_003AFBB0 *last = m_bfmeFinish;

	for (; first != last; ++first)
		first->~BfmeVecElem_003AFBB0();

	BfmeVecElem_003AFBB0 *start = m_bfmeStart;

	if (start)
		bfmeRelease(start, sizeof(BfmeVecElem_003AFBB0) * (m_bfmeEnd - start));
}

// ?bfmeDestroy@Gen_003AFDA0@@QAEXXZ
void Gen_003AFDA0::bfmeDestroy(void)
{
	BfmeVecElem_003AFDA0 *first = m_bfmeStart;
	BfmeVecElem_003AFDA0 *last = m_bfmeFinish;

	for (; first != last; ++first)
		first->~BfmeVecElem_003AFDA0();

	BfmeVecElem_003AFDA0 *start = m_bfmeStart;

	if (start)
		bfmeRelease(start, sizeof(BfmeVecElem_003AFDA0) * (m_bfmeEnd - start));
}

// ?bfmeDestroy@Gen_003AFF10@@QAEXXZ
void Gen_003AFF10::bfmeDestroy(void)
{
	BfmeVecElem_003AFF10 *first = m_bfmeStart;
	BfmeVecElem_003AFF10 *last = m_bfmeFinish;

	for (; first != last; ++first)
		first->~BfmeVecElem_003AFF10();

	BfmeVecElem_003AFF10 *start = m_bfmeStart;

	if (start)
		bfmeRelease(start, sizeof(BfmeVecElem_003AFF10) * (m_bfmeEnd - start));
}

// ?bfmeDestroy@Gen_003AFF80@@QAEXXZ
void Gen_003AFF80::bfmeDestroy(void)
{
	BfmeVecElem_003AFF80 *first = m_bfmeStart;
	BfmeVecElem_003AFF80 *last = m_bfmeFinish;

	for (; first != last; ++first)
		first->~BfmeVecElem_003AFF80();

	BfmeVecElem_003AFF80 *start = m_bfmeStart;

	if (start)
		bfmeRelease(start, sizeof(BfmeVecElem_003AFF80) * (m_bfmeEnd - start));
}
