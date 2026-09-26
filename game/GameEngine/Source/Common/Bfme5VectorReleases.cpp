// Four vector releases.
//
// Each frees the block its three pointers describe, choosing the free by the
// byte size exactly as the matching allocate chooses the allocator: over 0x80
// bytes goes to the scalar free, otherwise to the sized deallocator.
//
// The size is written as the element size times the pointer difference, which
// is why the compiler divides the byte span by the width and multiplies it
// straight back -- casting the pointers to char first would leave a plain
// subtraction and no magic multiply at all. The multiply-back names the width:
// 0x60 for the first, 0x0C for the other three.
//
// The start pointer is read into a local before the guard. Testing the member
// directly instead lets MSVC shrink-wrap the callee-saved push into the
// guarded region, which costs two bytes and moves the load past the test.

void __cdecl bfmeFreeScalar(void *block);			// retail 0x00881EB0
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

inline void bfmeRelease(void *block, unsigned int bytes)
{
	if (bytes > 0x80)
		bfmeFreeScalar(block);
	else
		bfmeDeallocate(block, bytes);
}

struct BfmeElem_000CEDF0 { char m_bfmeBytes[0x60]; };

class Gen_000CEDF0
{
public:
	void bfmeClear(void);

private:
	BfmeElem_000CEDF0 *m_bfmeStart;			// +0x00
	BfmeElem_000CEDF0 *m_bfmeFinish;			// +0x04
	BfmeElem_000CEDF0 *m_bfmeEnd;			// +0x08
};

struct BfmeElem_000D7330 { char m_bfmeBytes[0xC]; };

class Gen_000D7330
{
public:
	void bfmeClear(void);

private:
	char m_bfmePad[0x20];					// +0x00
	BfmeElem_000D7330 *m_bfmeStart;			// +0x20
	BfmeElem_000D7330 *m_bfmeFinish;			// +0x24
	BfmeElem_000D7330 *m_bfmeEnd;			// +0x28
};

struct BfmeElem_007D84C0 { char m_bfmeBytes[0xC]; };

class Gen_007D84C0
{
public:
	void bfmeClear(void);

private:
	char m_bfmePad[0x18];					// +0x00
	BfmeElem_007D84C0 *m_bfmeStart;			// +0x18
	BfmeElem_007D84C0 *m_bfmeFinish;			// +0x1C
	BfmeElem_007D84C0 *m_bfmeEnd;			// +0x20
};

struct BfmeElem_007D8520 { char m_bfmeBytes[0xC]; };

class Gen_007D8520
{
public:
	void bfmeClear(void);

private:
	char m_bfmePad[0x10];					// +0x00
	BfmeElem_007D8520 *m_bfmeStart;			// +0x10
	BfmeElem_007D8520 *m_bfmeFinish;			// +0x14
	BfmeElem_007D8520 *m_bfmeEnd;			// +0x18
};

// ?bfmeClear@Gen_000CEDF0@@QAEXXZ
void Gen_000CEDF0::bfmeClear(void)
{
	BfmeElem_000CEDF0 *start = m_bfmeStart;

	if (start == 0)
		return;

	bfmeRelease(start, sizeof(BfmeElem_000CEDF0) * (m_bfmeEnd - start));
}

// ?bfmeClear@Gen_000D7330@@QAEXXZ
void Gen_000D7330::bfmeClear(void)
{
	BfmeElem_000D7330 *start = m_bfmeStart;

	if (start == 0)
		return;

	bfmeRelease(start, sizeof(BfmeElem_000D7330) * (m_bfmeEnd - start));
}

// ?bfmeClear@Gen_007D84C0@@QAEXXZ
void Gen_007D84C0::bfmeClear(void)
{
	BfmeElem_007D84C0 *start = m_bfmeStart;

	if (start == 0)
		return;

	bfmeRelease(start, sizeof(BfmeElem_007D84C0) * (m_bfmeEnd - start));
}

// ?bfmeClear@Gen_007D8520@@QAEXXZ
void Gen_007D8520::bfmeClear(void)
{
	BfmeElem_007D8520 *start = m_bfmeStart;

	if (start == 0)
		return;

	bfmeRelease(start, sizeof(BfmeElem_007D8520) * (m_bfmeEnd - start));
}
