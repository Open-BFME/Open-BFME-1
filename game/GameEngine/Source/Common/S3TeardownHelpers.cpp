// Six more bodies in two shapes.
//
// 0x004410A0, 0x0077F000 and 0x007892D0 are three no-argument member calls in
// a row on the same this: esi holds it across the first two calls and the
// third is in tail position, so it becomes a jump after esi is popped.
//
// 0x008A0D60, 0x008C5B30 and 0x008C5C00 free a buffer only when it exists,
// passing the element count at +0x04 scaled by four; the scale is a shl, so
// the count is a count and not a byte size.

class Gen_004410A0
{
public:
	void bfmeRun(void);

private:
	void bfmeStep1(void);					// ILT 0x000459CB
	void bfmeStep2(void);					// ILT 0x0000B613
	void bfmeStep3(void);					// ILT 0x0002E8CA
};

class Gen_0077F000
{
public:
	void bfmeRun(void);

private:
	void bfmeStep1(void);					// ILT 0x00039428
	void bfmeStep2(void);					// ILT 0x0002398E
	void bfmeStep3(void);					// ILT 0x0001B32E
};

class Gen_007892D0
{
public:
	void bfmeRun(void);

private:
	void bfmeStep1(void);					// ILT 0x000270FC
	void bfmeStep2(void);					// ILT 0x0003879E
	void bfmeStep3(void);					// ILT 0x0004264A
};

struct BfmeRefBlock
{
	unsigned short m_bfmeRefCount;				// +0x00
};

struct BfmeReleaseTable
{
	void (*m_bfmeReserved)(void *block);			// +0x00
	void (*m_bfmeRelease)(void *block);			// +0x04
};

extern BfmeReleaseTable *TheBfmeReleaseTable;			// 0x01337A30

class Gen_00891B80
{
public:
	void bfmeRelease(void);

private:
	BfmeRefBlock *m_bfmeBlock;
};

class Gen_00892890
{
public:
	void bfmeRelease(void);

private:
	BfmeRefBlock *m_bfmeBlock;
};

class Gen_008AD330
{
public:
	void bfmeRelease(void);

private:
	BfmeRefBlock *m_bfmeBlock;
};

extern void (*TheBfmeBufferFree)(void *buffer, int bytes);	// 0x01337830

class Gen_008A0D60
{
public:
	void bfmeFreeBuffer(void);

private:
	char m_bfmeHead[4];
	int m_bfmeCount;					// +0x04
	void *m_bfmeBuffer;					// +0x08
};

class Gen_008C5B30
{
public:
	void bfmeFreeBuffer(void);

private:
	char m_bfmeHead[4];
	int m_bfmeCount;					// +0x04
	void *m_bfmeBuffer;					// +0x08
};

class Gen_008C5C00
{
public:
	void bfmeFreeBuffer(void);

private:
	char m_bfmeHead[4];
	int m_bfmeCount;					// +0x04
	void *m_bfmeBuffer;					// +0x08
};

// ?bfmeRun@Gen_004410A0@@QAEXXZ
void Gen_004410A0::bfmeRun(void)
{
	bfmeStep1();
	bfmeStep2();
	bfmeStep3();
}

// ?bfmeRun@Gen_0077F000@@QAEXXZ
void Gen_0077F000::bfmeRun(void)
{
	bfmeStep1();
	bfmeStep2();
	bfmeStep3();
}

// ?bfmeRun@Gen_007892D0@@QAEXXZ
void Gen_007892D0::bfmeRun(void)
{
	bfmeStep1();
	bfmeStep2();
	bfmeStep3();
}

// ?bfmeFreeBuffer@Gen_008A0D60@@QAEXXZ
void Gen_008A0D60::bfmeFreeBuffer(void)
{
	if (m_bfmeBuffer)
		TheBfmeBufferFree(m_bfmeBuffer, m_bfmeCount * 4);
}

// ?bfmeFreeBuffer@Gen_008C5B30@@QAEXXZ
void Gen_008C5B30::bfmeFreeBuffer(void)
{
	if (m_bfmeBuffer)
		TheBfmeBufferFree(m_bfmeBuffer, m_bfmeCount * 4);
}

// ?bfmeFreeBuffer@Gen_008C5C00@@QAEXXZ
void Gen_008C5C00::bfmeFreeBuffer(void)
{
	if (m_bfmeBuffer)
		TheBfmeBufferFree(m_bfmeBuffer, m_bfmeCount * 4);
}
