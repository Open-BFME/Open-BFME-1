// Twenty allocate-and-copy-range bodies whose element copy stays out of line.
//
// Same shape as the ones that copy inline: allocate for the count through the
// size-dispatch helper with a zero arm, copy the range in, return the block.
// The difference is that the element here has a real copy constructor, so each
// pass calls it instead of moving words, and the block has to survive that
// call -- which is why it lives in ebp rather than staying in the allocator's
// register.
//
// The copy helper still takes the destination first, so the destination
// induction variable is the one eliminated and the loop runs on the source
// with the destination recomputed each pass. Two of the widths need an imul
// large enough to push the body to a hundred bytes, and those two are also the
// only ones this compiler declines to inline on its own -- hence the forced
// inline, applied uniformly since it changes nothing for the other eighteen.

void *bfmeNewAlloc(unsigned int bytes);				// retail 0x00881F30
void *bfmeAllocNode(unsigned int bytes);			// retail 0x0082E540

inline void *bfmeAllocate(unsigned int bytes)
{
	if (bytes > 0x80)
		return bfmeNewAlloc(bytes);

	return bfmeAllocNode(bytes);
}

struct BfmeCopy_000656F0 { char m_bfmeBytes[0x4]; };

void __cdecl bfmeConstruct_000656F0(BfmeCopy_000656F0 *where, const BfmeCopy_000656F0 *value);	// retail 0x00007554

__forceinline void bfmeUninitCopy_000656F0(BfmeCopy_000656F0 *result, const BfmeCopy_000656F0 *first, const BfmeCopy_000656F0 *last)
{
	for (; first != last; ++first, ++result)
		bfmeConstruct_000656F0(result, first);
}

struct BfmeCopy_00095760 { char m_bfmeBytes[0x8]; };

void __cdecl bfmeConstruct_00095760(BfmeCopy_00095760 *where, const BfmeCopy_00095760 *value);	// retail 0x000060CD

__forceinline void bfmeUninitCopy_00095760(BfmeCopy_00095760 *result, const BfmeCopy_00095760 *first, const BfmeCopy_00095760 *last)
{
	for (; first != last; ++first, ++result)
		bfmeConstruct_00095760(result, first);
}

struct BfmeCopy_000B06B0 { char m_bfmeBytes[0x8]; };

void __cdecl bfmeConstruct_000B06B0(BfmeCopy_000B06B0 *where, const BfmeCopy_000B06B0 *value);	// retail 0x00039F86

__forceinline void bfmeUninitCopy_000B06B0(BfmeCopy_000B06B0 *result, const BfmeCopy_000B06B0 *first, const BfmeCopy_000B06B0 *last)
{
	for (; first != last; ++first, ++result)
		bfmeConstruct_000B06B0(result, first);
}

struct BfmeCopy_000DE0E0 { char m_bfmeBytes[0x4]; };

void __cdecl bfmeConstruct_000DE0E0(BfmeCopy_000DE0E0 *where, const BfmeCopy_000DE0E0 *value);	// retail 0x00007554

__forceinline void bfmeUninitCopy_000DE0E0(BfmeCopy_000DE0E0 *result, const BfmeCopy_000DE0E0 *first, const BfmeCopy_000DE0E0 *last)
{
	for (; first != last; ++first, ++result)
		bfmeConstruct_000DE0E0(result, first);
}

struct BfmeCopy_000DE5D0 { char m_bfmeBytes[0x10]; };

void __cdecl bfmeConstruct_000DE5D0(BfmeCopy_000DE5D0 *where, const BfmeCopy_000DE5D0 *value);	// retail 0x0001B275

__forceinline void bfmeUninitCopy_000DE5D0(BfmeCopy_000DE5D0 *result, const BfmeCopy_000DE5D0 *first, const BfmeCopy_000DE5D0 *last)
{
	for (; first != last; ++first, ++result)
		bfmeConstruct_000DE5D0(result, first);
}

struct BfmeCopy_000FD9E0 { char m_bfmeBytes[0x10]; };

void __cdecl bfmeConstruct_000FD9E0(BfmeCopy_000FD9E0 *where, const BfmeCopy_000FD9E0 *value);	// retail 0x0000F86C

__forceinline void bfmeUninitCopy_000FD9E0(BfmeCopy_000FD9E0 *result, const BfmeCopy_000FD9E0 *first, const BfmeCopy_000FD9E0 *last)
{
	for (; first != last; ++first, ++result)
		bfmeConstruct_000FD9E0(result, first);
}

struct BfmeCopy_00138C40 { char m_bfmeBytes[0x5C]; };

void __cdecl bfmeConstruct_00138C40(BfmeCopy_00138C40 *where, const BfmeCopy_00138C40 *value);	// retail 0x00018D04

__forceinline void bfmeUninitCopy_00138C40(BfmeCopy_00138C40 *result, const BfmeCopy_00138C40 *first, const BfmeCopy_00138C40 *last)
{
	for (; first != last; ++first, ++result)
		bfmeConstruct_00138C40(result, first);
}

struct BfmeCopy_001E3D20 { char m_bfmeBytes[0x8]; };

void __cdecl bfmeConstruct_001E3D20(BfmeCopy_001E3D20 *where, const BfmeCopy_001E3D20 *value);	// retail 0x00046AF1

__forceinline void bfmeUninitCopy_001E3D20(BfmeCopy_001E3D20 *result, const BfmeCopy_001E3D20 *first, const BfmeCopy_001E3D20 *last)
{
	for (; first != last; ++first, ++result)
		bfmeConstruct_001E3D20(result, first);
}

struct BfmeCopy_00233960 { char m_bfmeBytes[0x10]; };

void __cdecl bfmeConstruct_00233960(BfmeCopy_00233960 *where, const BfmeCopy_00233960 *value);	// retail 0x0001476D

__forceinline void bfmeUninitCopy_00233960(BfmeCopy_00233960 *result, const BfmeCopy_00233960 *first, const BfmeCopy_00233960 *last)
{
	for (; first != last; ++first, ++result)
		bfmeConstruct_00233960(result, first);
}

struct BfmeCopy_002349D0 { char m_bfmeBytes[0x1C]; };

void __cdecl bfmeConstruct_002349D0(BfmeCopy_002349D0 *where, const BfmeCopy_002349D0 *value);	// retail 0x000128DC

__forceinline void bfmeUninitCopy_002349D0(BfmeCopy_002349D0 *result, const BfmeCopy_002349D0 *first, const BfmeCopy_002349D0 *last)
{
	for (; first != last; ++first, ++result)
		bfmeConstruct_002349D0(result, first);
}

struct BfmeCopy_00364730 { char m_bfmeBytes[0xB4]; };

void __cdecl bfmeConstruct_00364730(BfmeCopy_00364730 *where, const BfmeCopy_00364730 *value);	// retail 0x00003193

__forceinline void bfmeUninitCopy_00364730(BfmeCopy_00364730 *result, const BfmeCopy_00364730 *first, const BfmeCopy_00364730 *last)
{
	for (; first != last; ++first, ++result)
		bfmeConstruct_00364730(result, first);
}

struct BfmeCopy_003B3D20 { char m_bfmeBytes[0x20]; };

void __cdecl bfmeConstruct_003B3D20(BfmeCopy_003B3D20 *where, const BfmeCopy_003B3D20 *value);	// retail 0x0000F9A2

__forceinline void bfmeUninitCopy_003B3D20(BfmeCopy_003B3D20 *result, const BfmeCopy_003B3D20 *first, const BfmeCopy_003B3D20 *last)
{
	for (; first != last; ++first, ++result)
		bfmeConstruct_003B3D20(result, first);
}

struct BfmeCopy_003B3FF0 { char m_bfmeBytes[0x10]; };

void __cdecl bfmeConstruct_003B3FF0(BfmeCopy_003B3FF0 *where, const BfmeCopy_003B3FF0 *value);	// retail 0x00013B79

__forceinline void bfmeUninitCopy_003B3FF0(BfmeCopy_003B3FF0 *result, const BfmeCopy_003B3FF0 *first, const BfmeCopy_003B3FF0 *last)
{
	for (; first != last; ++first, ++result)
		bfmeConstruct_003B3FF0(result, first);
}

struct BfmeCopy_003B4E00 { char m_bfmeBytes[0x20]; };

void __cdecl bfmeConstruct_003B4E00(BfmeCopy_003B4E00 *where, const BfmeCopy_003B4E00 *value);	// retail 0x0003CA24

__forceinline void bfmeUninitCopy_003B4E00(BfmeCopy_003B4E00 *result, const BfmeCopy_003B4E00 *first, const BfmeCopy_003B4E00 *last)
{
	for (; first != last; ++first, ++result)
		bfmeConstruct_003B4E00(result, first);
}

struct BfmeCopy_003B68A0 { char m_bfmeBytes[0xDC]; };

void __cdecl bfmeConstruct_003B68A0(BfmeCopy_003B68A0 *where, const BfmeCopy_003B68A0 *value);	// retail 0x00015C85

__forceinline void bfmeUninitCopy_003B68A0(BfmeCopy_003B68A0 *result, const BfmeCopy_003B68A0 *first, const BfmeCopy_003B68A0 *last)
{
	for (; first != last; ++first, ++result)
		bfmeConstruct_003B68A0(result, first);
}

struct BfmeCopy_00426140 { char m_bfmeBytes[0x1C]; };

void __cdecl bfmeConstruct_00426140(BfmeCopy_00426140 *where, const BfmeCopy_00426140 *value);	// retail 0x000339A1

__forceinline void bfmeUninitCopy_00426140(BfmeCopy_00426140 *result, const BfmeCopy_00426140 *first, const BfmeCopy_00426140 *last)
{
	for (; first != last; ++first, ++result)
		bfmeConstruct_00426140(result, first);
}

struct BfmeCopy_0049F580 { char m_bfmeBytes[0x70]; };

void __cdecl bfmeConstruct_0049F580(BfmeCopy_0049F580 *where, const BfmeCopy_0049F580 *value);	// retail 0x0000A97A

__forceinline void bfmeUninitCopy_0049F580(BfmeCopy_0049F580 *result, const BfmeCopy_0049F580 *first, const BfmeCopy_0049F580 *last)
{
	for (; first != last; ++first, ++result)
		bfmeConstruct_0049F580(result, first);
}

struct BfmeCopy_0069F080 { char m_bfmeBytes[0x4]; };

void __cdecl bfmeConstruct_0069F080(BfmeCopy_0069F080 *where, const BfmeCopy_0069F080 *value);	// retail 0x00026503

__forceinline void bfmeUninitCopy_0069F080(BfmeCopy_0069F080 *result, const BfmeCopy_0069F080 *first, const BfmeCopy_0069F080 *last)
{
	for (; first != last; ++first, ++result)
		bfmeConstruct_0069F080(result, first);
}

struct BfmeCopy_007653C0 { char m_bfmeBytes[0x3C]; };

void __cdecl bfmeConstruct_007653C0(BfmeCopy_007653C0 *where, const BfmeCopy_007653C0 *value);	// retail 0x0003B7E6

__forceinline void bfmeUninitCopy_007653C0(BfmeCopy_007653C0 *result, const BfmeCopy_007653C0 *first, const BfmeCopy_007653C0 *last)
{
	for (; first != last; ++first, ++result)
		bfmeConstruct_007653C0(result, first);
}

struct BfmeCopy_007690F0 { char m_bfmeBytes[0x38]; };

void __cdecl bfmeConstruct_007690F0(BfmeCopy_007690F0 *where, const BfmeCopy_007690F0 *value);	// retail 0x0002B7AB

__forceinline void bfmeUninitCopy_007690F0(BfmeCopy_007690F0 *result, const BfmeCopy_007690F0 *first, const BfmeCopy_007690F0 *last)
{
	for (; first != last; ++first, ++result)
		bfmeConstruct_007690F0(result, first);
}

// ?bfmeMake_000656F0@@YGPAUBfmeCopy_000656F0@@IPBU1@0@Z
BfmeCopy_000656F0 * __stdcall bfmeMake_000656F0(unsigned int count,
	const BfmeCopy_000656F0 *first, const BfmeCopy_000656F0 *last)
{
	BfmeCopy_000656F0 *block;

	if (count)
		block = (BfmeCopy_000656F0 *)bfmeAllocate(count * sizeof(BfmeCopy_000656F0));
	else
		block = 0;

	bfmeUninitCopy_000656F0(block, first, last);

	return block;
}

// ?bfmeMake_00095760@@YGPAUBfmeCopy_00095760@@IPBU1@0@Z
BfmeCopy_00095760 * __stdcall bfmeMake_00095760(unsigned int count,
	const BfmeCopy_00095760 *first, const BfmeCopy_00095760 *last)
{
	BfmeCopy_00095760 *block;

	if (count)
		block = (BfmeCopy_00095760 *)bfmeAllocate(count * sizeof(BfmeCopy_00095760));
	else
		block = 0;

	bfmeUninitCopy_00095760(block, first, last);

	return block;
}

// ?bfmeMake_000B06B0@@YGPAUBfmeCopy_000B06B0@@IPBU1@0@Z
BfmeCopy_000B06B0 * __stdcall bfmeMake_000B06B0(unsigned int count,
	const BfmeCopy_000B06B0 *first, const BfmeCopy_000B06B0 *last)
{
	BfmeCopy_000B06B0 *block;

	if (count)
		block = (BfmeCopy_000B06B0 *)bfmeAllocate(count * sizeof(BfmeCopy_000B06B0));
	else
		block = 0;

	bfmeUninitCopy_000B06B0(block, first, last);

	return block;
}

// ?bfmeMake_000DE0E0@@YGPAUBfmeCopy_000DE0E0@@IPBU1@0@Z
BfmeCopy_000DE0E0 * __stdcall bfmeMake_000DE0E0(unsigned int count,
	const BfmeCopy_000DE0E0 *first, const BfmeCopy_000DE0E0 *last)
{
	BfmeCopy_000DE0E0 *block;

	if (count)
		block = (BfmeCopy_000DE0E0 *)bfmeAllocate(count * sizeof(BfmeCopy_000DE0E0));
	else
		block = 0;

	bfmeUninitCopy_000DE0E0(block, first, last);

	return block;
}

// ?bfmeMake_000DE5D0@@YGPAUBfmeCopy_000DE5D0@@IPBU1@0@Z
BfmeCopy_000DE5D0 * __stdcall bfmeMake_000DE5D0(unsigned int count,
	const BfmeCopy_000DE5D0 *first, const BfmeCopy_000DE5D0 *last)
{
	BfmeCopy_000DE5D0 *block;

	if (count)
		block = (BfmeCopy_000DE5D0 *)bfmeAllocate(count * sizeof(BfmeCopy_000DE5D0));
	else
		block = 0;

	bfmeUninitCopy_000DE5D0(block, first, last);

	return block;
}

// ?bfmeMake_000FD9E0@@YGPAUBfmeCopy_000FD9E0@@IPBU1@0@Z
BfmeCopy_000FD9E0 * __stdcall bfmeMake_000FD9E0(unsigned int count,
	const BfmeCopy_000FD9E0 *first, const BfmeCopy_000FD9E0 *last)
{
	BfmeCopy_000FD9E0 *block;

	if (count)
		block = (BfmeCopy_000FD9E0 *)bfmeAllocate(count * sizeof(BfmeCopy_000FD9E0));
	else
		block = 0;

	bfmeUninitCopy_000FD9E0(block, first, last);

	return block;
}

// ?bfmeMake_00138C40@@YGPAUBfmeCopy_00138C40@@IPBU1@0@Z
BfmeCopy_00138C40 * __stdcall bfmeMake_00138C40(unsigned int count,
	const BfmeCopy_00138C40 *first, const BfmeCopy_00138C40 *last)
{
	BfmeCopy_00138C40 *block;

	if (count)
		block = (BfmeCopy_00138C40 *)bfmeAllocate(count * sizeof(BfmeCopy_00138C40));
	else
		block = 0;

	bfmeUninitCopy_00138C40(block, first, last);

	return block;
}

// ?bfmeMake_001E3D20@@YGPAUBfmeCopy_001E3D20@@IPBU1@0@Z
BfmeCopy_001E3D20 * __stdcall bfmeMake_001E3D20(unsigned int count,
	const BfmeCopy_001E3D20 *first, const BfmeCopy_001E3D20 *last)
{
	BfmeCopy_001E3D20 *block;

	if (count)
		block = (BfmeCopy_001E3D20 *)bfmeAllocate(count * sizeof(BfmeCopy_001E3D20));
	else
		block = 0;

	bfmeUninitCopy_001E3D20(block, first, last);

	return block;
}

// ?bfmeMake_00233960@@YGPAUBfmeCopy_00233960@@IPBU1@0@Z
BfmeCopy_00233960 * __stdcall bfmeMake_00233960(unsigned int count,
	const BfmeCopy_00233960 *first, const BfmeCopy_00233960 *last)
{
	BfmeCopy_00233960 *block;

	if (count)
		block = (BfmeCopy_00233960 *)bfmeAllocate(count * sizeof(BfmeCopy_00233960));
	else
		block = 0;

	bfmeUninitCopy_00233960(block, first, last);

	return block;
}

// ?bfmeMake_002349D0@@YGPAUBfmeCopy_002349D0@@IPBU1@0@Z
BfmeCopy_002349D0 * __stdcall bfmeMake_002349D0(unsigned int count,
	const BfmeCopy_002349D0 *first, const BfmeCopy_002349D0 *last)
{
	BfmeCopy_002349D0 *block;

	if (count)
		block = (BfmeCopy_002349D0 *)bfmeAllocate(count * sizeof(BfmeCopy_002349D0));
	else
		block = 0;

	bfmeUninitCopy_002349D0(block, first, last);

	return block;
}

// ?bfmeMake_00364730@@YGPAUBfmeCopy_00364730@@IPBU1@0@Z
BfmeCopy_00364730 * __stdcall bfmeMake_00364730(unsigned int count,
	const BfmeCopy_00364730 *first, const BfmeCopy_00364730 *last)
{
	BfmeCopy_00364730 *block;

	if (count)
		block = (BfmeCopy_00364730 *)bfmeAllocate(count * sizeof(BfmeCopy_00364730));
	else
		block = 0;

	bfmeUninitCopy_00364730(block, first, last);

	return block;
}

// ?bfmeMake_003B3D20@@YGPAUBfmeCopy_003B3D20@@IPBU1@0@Z
BfmeCopy_003B3D20 * __stdcall bfmeMake_003B3D20(unsigned int count,
	const BfmeCopy_003B3D20 *first, const BfmeCopy_003B3D20 *last)
{
	BfmeCopy_003B3D20 *block;

	if (count)
		block = (BfmeCopy_003B3D20 *)bfmeAllocate(count * sizeof(BfmeCopy_003B3D20));
	else
		block = 0;

	bfmeUninitCopy_003B3D20(block, first, last);

	return block;
}

// ?bfmeMake_003B3FF0@@YGPAUBfmeCopy_003B3FF0@@IPBU1@0@Z
BfmeCopy_003B3FF0 * __stdcall bfmeMake_003B3FF0(unsigned int count,
	const BfmeCopy_003B3FF0 *first, const BfmeCopy_003B3FF0 *last)
{
	BfmeCopy_003B3FF0 *block;

	if (count)
		block = (BfmeCopy_003B3FF0 *)bfmeAllocate(count * sizeof(BfmeCopy_003B3FF0));
	else
		block = 0;

	bfmeUninitCopy_003B3FF0(block, first, last);

	return block;
}

// ?bfmeMake_003B4E00@@YGPAUBfmeCopy_003B4E00@@IPBU1@0@Z
BfmeCopy_003B4E00 * __stdcall bfmeMake_003B4E00(unsigned int count,
	const BfmeCopy_003B4E00 *first, const BfmeCopy_003B4E00 *last)
{
	BfmeCopy_003B4E00 *block;

	if (count)
		block = (BfmeCopy_003B4E00 *)bfmeAllocate(count * sizeof(BfmeCopy_003B4E00));
	else
		block = 0;

	bfmeUninitCopy_003B4E00(block, first, last);

	return block;
}

// ?bfmeMake_003B68A0@@YGPAUBfmeCopy_003B68A0@@IPBU1@0@Z
BfmeCopy_003B68A0 * __stdcall bfmeMake_003B68A0(unsigned int count,
	const BfmeCopy_003B68A0 *first, const BfmeCopy_003B68A0 *last)
{
	BfmeCopy_003B68A0 *block;

	if (count)
		block = (BfmeCopy_003B68A0 *)bfmeAllocate(count * sizeof(BfmeCopy_003B68A0));
	else
		block = 0;

	bfmeUninitCopy_003B68A0(block, first, last);

	return block;
}

// ?bfmeMake_00426140@@YGPAUBfmeCopy_00426140@@IPBU1@0@Z
BfmeCopy_00426140 * __stdcall bfmeMake_00426140(unsigned int count,
	const BfmeCopy_00426140 *first, const BfmeCopy_00426140 *last)
{
	BfmeCopy_00426140 *block;

	if (count)
		block = (BfmeCopy_00426140 *)bfmeAllocate(count * sizeof(BfmeCopy_00426140));
	else
		block = 0;

	bfmeUninitCopy_00426140(block, first, last);

	return block;
}

// ?bfmeMake_0049F580@@YGPAUBfmeCopy_0049F580@@IPBU1@0@Z
BfmeCopy_0049F580 * __stdcall bfmeMake_0049F580(unsigned int count,
	const BfmeCopy_0049F580 *first, const BfmeCopy_0049F580 *last)
{
	BfmeCopy_0049F580 *block;

	if (count)
		block = (BfmeCopy_0049F580 *)bfmeAllocate(count * sizeof(BfmeCopy_0049F580));
	else
		block = 0;

	bfmeUninitCopy_0049F580(block, first, last);

	return block;
}

// ?bfmeMake_0069F080@@YGPAUBfmeCopy_0069F080@@IPBU1@0@Z
BfmeCopy_0069F080 * __stdcall bfmeMake_0069F080(unsigned int count,
	const BfmeCopy_0069F080 *first, const BfmeCopy_0069F080 *last)
{
	BfmeCopy_0069F080 *block;

	if (count)
		block = (BfmeCopy_0069F080 *)bfmeAllocate(count * sizeof(BfmeCopy_0069F080));
	else
		block = 0;

	bfmeUninitCopy_0069F080(block, first, last);

	return block;
}

// ?bfmeMake_007653C0@@YGPAUBfmeCopy_007653C0@@IPBU1@0@Z
BfmeCopy_007653C0 * __stdcall bfmeMake_007653C0(unsigned int count,
	const BfmeCopy_007653C0 *first, const BfmeCopy_007653C0 *last)
{
	BfmeCopy_007653C0 *block;

	if (count)
		block = (BfmeCopy_007653C0 *)bfmeAllocate(count * sizeof(BfmeCopy_007653C0));
	else
		block = 0;

	bfmeUninitCopy_007653C0(block, first, last);

	return block;
}

// ?bfmeMake_007690F0@@YGPAUBfmeCopy_007690F0@@IPBU1@0@Z
BfmeCopy_007690F0 * __stdcall bfmeMake_007690F0(unsigned int count,
	const BfmeCopy_007690F0 *first, const BfmeCopy_007690F0 *last)
{
	BfmeCopy_007690F0 *block;

	if (count)
		block = (BfmeCopy_007690F0 *)bfmeAllocate(count * sizeof(BfmeCopy_007690F0));
	else
		block = 0;

	bfmeUninitCopy_007690F0(block, first, last);

	return block;
}
