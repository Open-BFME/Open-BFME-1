// Four 58-byte bodies with one shape: hand the argument to a cdecl lookup,
// give up on a negative answer, and otherwise set one bit of a word array that
// starts at this+0x00.
//
//     index >> 5      picks the word          (lea esi + ecx*4)
//     index & 0x1F    picks the bit           (mov eax,1 / shl eax,cl)
//
// The shift is shr, not sar, so the index is unsigned by the time it is used.
// It arrives signed -- the guard is jl on the raw result -- so the source has
// to widen it into an unsigned local after the test rather than shifting the
// signed value.
//
// The success path also has to sit inside the if with the plain return false
// last, the same way the reserve family at 0x007B9E80 needed it -- written as
// an early return on the negative case the false exit moves inline.
//
// Each lookup is its own thunk and is pinned here; nothing relates the four
// classes beyond the shape.

typedef unsigned int UnsignedInt;

int bfmeLookup_000d1020(void *name);				// ILT 0x0004AFFC

class Gen_000d1020
{
public:
	bool bfmeSet(void *name);

	UnsignedInt m_bfmeBits[1];					// +0x00
};

int bfmeLookup_001c62b0(void *name);				// ILT 0x000190F1

class Gen_001c62b0
{
public:
	bool bfmeSet(void *name);

	UnsignedInt m_bfmeBits[1];					// +0x00
};

int bfmeLookup_001c6340(void *name);				// ILT 0x00026A3F

class Gen_001c6340
{
public:
	bool bfmeSet(void *name);

	UnsignedInt m_bfmeBits[1];					// +0x00
};

int bfmeLookup_001c63d0(void *name);				// ILT 0x0004B218

class Gen_001c63d0
{
public:
	bool bfmeSet(void *name);

	UnsignedInt m_bfmeBits[1];					// +0x00
};

// ?bfmeSet@Gen_000d1020@@QAE_NPAX@Z
bool Gen_000d1020::bfmeSet(void *name)
{
	int index = bfmeLookup_000d1020(name);

	if (index >= 0)
	{
		UnsignedInt bit = (UnsignedInt)index;

		m_bfmeBits[bit >> 5] |= 1 << (bit & 0x1F);

		return true;
	}

	return false;
}

// ?bfmeSet@Gen_001c62b0@@QAE_NPAX@Z
bool Gen_001c62b0::bfmeSet(void *name)
{
	int index = bfmeLookup_001c62b0(name);

	if (index >= 0)
	{
		UnsignedInt bit = (UnsignedInt)index;

		m_bfmeBits[bit >> 5] |= 1 << (bit & 0x1F);

		return true;
	}

	return false;
}

// ?bfmeSet@Gen_001c6340@@QAE_NPAX@Z
bool Gen_001c6340::bfmeSet(void *name)
{
	int index = bfmeLookup_001c6340(name);

	if (index >= 0)
	{
		UnsignedInt bit = (UnsignedInt)index;

		m_bfmeBits[bit >> 5] |= 1 << (bit & 0x1F);

		return true;
	}

	return false;
}

// ?bfmeSet@Gen_001c63d0@@QAE_NPAX@Z
bool Gen_001c63d0::bfmeSet(void *name)
{
	int index = bfmeLookup_001c63d0(name);

	if (index >= 0)
	{
		UnsignedInt bit = (UnsignedInt)index;

		m_bfmeBits[bit >> 5] |= 1 << (bit & 0x1F);

		return true;
	}

	return false;
}
