// Six more tiny ones: a second flag written into the same singleton, a swap of
// one field between two objects, two affine sign tests, a bounded lookup into
// an array of pairs and a table copied between two globals.
//
// The sign tests return an int, not a byte: the zero has to be moved into the
// whole register before the setns because an xor would clobber the flags the
// addition just set, and a one-byte return skips it. The swap has to go
// through a helper taking references, as the other swaps in this codebase do.

class BfmeHolderBQ
{
public:
	char m_bfmeHead[0xBD];					// +0x00
	unsigned char m_bfmeFlag;				// +0xBD
};

extern BfmeHolderBQ *g_bfmeHolderBQ;				// retail 0x012F1464

inline void bfmeSwapInt(int &left, int &right)
{
	int value = left;

	left = right;
	right = value;
}

class Gen_00339020
{
public:
	void bfmeSwap(Gen_00339020 *other);

private:
	int m_bfmeTag;						// +0x00
	int m_bfmeValue;					// +0x04
};

// ?bfmeSwap@Gen_00339020@@QAEXPAV1@@Z
void Gen_00339020::bfmeSwap(Gen_00339020 *other)
{
	bfmeSwapInt(m_bfmeValue, other->m_bfmeValue);
}

class Gen_0037A810
{
public:
	int bfmeFirstIsPositive(int value) const;
	int bfmeSecondIsPositive(int value) const;

private:
	int m_bfmeHead[7];					// +0x00
	int m_bfmeFirstScale;					// +0x1C
	int m_bfmeFirstOffset;					// +0x20
	int m_bfmeSecondScale;					// +0x24
	int m_bfmeSecondOffset;					// +0x28
};

class BfmePairBQ
{
public:
	unsigned char m_bfmeFlag;				// +0x00
	char m_bfmeRest[7];					// +0x01
};

class Gen_0039B020
{
public:
	unsigned char bfmeFlag(void) const;

private:
	int m_bfmeHead[3];					// +0x00
	int m_bfmeIndex;					// +0x0C
	int m_bfmeGap[7];					// +0x10
	BfmePairBQ m_bfmePairs[5];				// +0x2C
};

// ?bfmeFlag@Gen_0039B020@@QBEEXZ
unsigned char Gen_0039B020::bfmeFlag(void) const
{
	int index = m_bfmeIndex;

	if (index < 0 || index >= 5)
		return 0;

	return m_bfmePairs[index].m_bfmeFlag;
}

extern int g_bfmeTableSrcBQ[24];				// retail 0x012B5040
extern int g_bfmeTableDstBQ[24];				// retail 0x012B50A0

extern "C" void * __cdecl memcpy(void *destination, const void *source, unsigned int bytes);

#pragma intrinsic(memcpy)

// ?bfmeCopyTable@@YAXXZ
void __cdecl bfmeCopyTable(void)
{
	memcpy(g_bfmeTableDstBQ, g_bfmeTableSrcBQ, sizeof(g_bfmeTableDstBQ));
}
