// Eight element copy loops.
//
// Each turns a pointer range into a count, walks it, and hands every source
// element to a member of the matching destination element, returning the
// advanced destination. The empty case returns the destination argument
// untouched.
//
// The element width is not in the code as a constant to read off directly: the
// count comes from a magic-multiply division of the byte difference, and it is
// the ADD at the bottom of the loop that names the stride. Six widths appear
// across the eight bodies -- 0x38, 0x5C, 0x70, 0x8C, 0xB4 and 0xB8 -- and the
// three that need a dword displacement for that add are the six bytes longer.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct BfmeCopySubA
{
	void bfmeAssign(BfmeCopySubA *source);		// retail 0x000FF8F0

	char m_bfmeBytes[0x0C];
};

struct BfmeCopySubB
{
	void bfmeAssign(BfmeCopySubB *source);		// retail 0x000FFA60

	char m_bfmeBytes[0x0C];
};

struct BfmeCopyWords
{
	int m_bfmeFirst;
	int m_bfmeSecond;
	int m_bfmeThird;
};

struct BfmeCopyTail
{
	int m_bfmeFirst;
	int m_bfmeSecond;
	int m_bfmeThird;
};

struct BfmeCopyElementA
{
	int m_bfmeHead;
	unsigned char m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	BfmeCopyWords m_bfme18;
	int m_bfme24;
	int m_bfme28;
	BfmeCopySubA m_bfme2c;
	BfmeCopySubB m_bfme38;
	BfmeCopyTail m_bfme44;
	BfmeCopyWords m_bfme50;

	BfmeCopyElementA *bfmeAssign(BfmeCopyElementA *source);		// retail 0x00003828
};

struct BfmeCopyElementB
{
	void bfmeAssign(BfmeCopyElementB *source);		// retail 0x0000D4CC

	char m_bfmeBytes[0x8C];
};

struct BfmeCopyElementC
{
	void bfmeAssign(BfmeCopyElementC *source);		// retail 0x000470F0

	char m_bfmeBytes[0xB4];
};

struct BfmeCopyElementD
{
	void bfmeAssign(BfmeCopyElementD *source);		// retail 0x00024BA9

	char m_bfmeBytes[0xB8];
};

struct BfmeCopyElementE
{
	void bfmeAssign(BfmeCopyElementE *source);		// retail 0x0001F753

	char m_bfmeBytes[0x70];
};

struct BfmeCopyElementF
{
	void bfmeAssign(BfmeCopyElementF *source);		// retail 0x0001B1D5

	char m_bfmeBytes[0x38];
};

BfmeCopyElementA *BfmeCopyElementA::bfmeAssign(BfmeCopyElementA *source)
{
	m_bfme04 = source->m_bfme04;
	m_bfme08 = source->m_bfme08;
	m_bfme0c = source->m_bfme0c;
	m_bfme10 = source->m_bfme10;
	m_bfme14 = source->m_bfme14;
	m_bfme18 = source->m_bfme18;
	m_bfme24 = source->m_bfme24;
	m_bfme28 = source->m_bfme28;
	m_bfme2c.bfmeAssign(&source->m_bfme2c);
	m_bfme38.bfmeAssign(&source->m_bfme38);
	m_bfme44 = source->m_bfme44;
	// Retail finishes this aggregate copy before scheduling the final tail copy.
	_ReadWriteBarrier();
	m_bfme50 = source->m_bfme50;
	return this;
}

// ?bfmeCopy_00138800@@YAPAUBfmeCopyElementA@@PAU1@00@Z
BfmeCopyElementA *bfmeCopy_00138800(BfmeCopyElementA *first, BfmeCopyElementA *last, BfmeCopyElementA *dest)
{
	int count = last - first;

	while (count > 0)
	{
		dest->bfmeAssign(first);

		++first;
		++dest;
		--count;
	}

	return dest;
}

// ?bfmeCopy_00146720@@YAPAUBfmeCopyElementA@@PAU1@00@Z
BfmeCopyElementA *bfmeCopy_00146720(BfmeCopyElementA *first, BfmeCopyElementA *last, BfmeCopyElementA *dest)
{
	int count = last - first;

	while (count > 0)
	{
		dest->bfmeAssign(first);

		++first;
		++dest;
		--count;
	}

	return dest;
}

// ?bfmeCopy_00193AF0@@YAPAUBfmeCopyElementB@@PAU1@00@Z
BfmeCopyElementB *bfmeCopy_00193AF0(BfmeCopyElementB *first, BfmeCopyElementB *last, BfmeCopyElementB *dest)
{
	int count = last - first;

	while (count > 0)
	{
		dest->bfmeAssign(first);

		++first;
		++dest;
		--count;
	}

	return dest;
}

// ?bfmeCopy_00362250@@YAPAUBfmeCopyElementC@@PAU1@00@Z
BfmeCopyElementC *bfmeCopy_00362250(BfmeCopyElementC *first, BfmeCopyElementC *last, BfmeCopyElementC *dest)
{
	int count = last - first;

	while (count > 0)
	{
		dest->bfmeAssign(first);

		++first;
		++dest;
		--count;
	}

	return dest;
}

// ?bfmeCopy_003622F0@@YAPAUBfmeCopyElementC@@PAU1@00@Z
BfmeCopyElementC *bfmeCopy_003622F0(BfmeCopyElementC *first, BfmeCopyElementC *last, BfmeCopyElementC *dest)
{
	int count = last - first;

	while (count > 0)
	{
		dest->bfmeAssign(first);

		++first;
		++dest;
		--count;
	}

	return dest;
}

// ?bfmeCopy_003A1450@@YAPAUBfmeCopyElementD@@PAU1@00@Z
BfmeCopyElementD *bfmeCopy_003A1450(BfmeCopyElementD *first, BfmeCopyElementD *last, BfmeCopyElementD *dest)
{
	int count = last - first;

	while (count > 0)
	{
		dest->bfmeAssign(first);

		++first;
		++dest;
		--count;
	}

	return dest;
}

// ?bfmeCopy_0049D5D0@@YAPAUBfmeCopyElementE@@PAU1@00@Z
BfmeCopyElementE *bfmeCopy_0049D5D0(BfmeCopyElementE *first, BfmeCopyElementE *last, BfmeCopyElementE *dest)
{
	int count = last - first;

	while (count > 0)
	{
		dest->bfmeAssign(first);

		++first;
		++dest;
		--count;
	}

	return dest;
}

// ?bfmeCopy_0075EAA0@@YAPAUBfmeCopyElementF@@PAU1@00@Z
BfmeCopyElementF *bfmeCopy_0075EAA0(BfmeCopyElementF *first, BfmeCopyElementF *last, BfmeCopyElementF *dest)
{
	int count = last - first;

	while (count > 0)
	{
		dest->bfmeAssign(first);

		++first;
		++dest;
		--count;
	}

	return dest;
}
