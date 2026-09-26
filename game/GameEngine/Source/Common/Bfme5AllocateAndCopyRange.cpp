// Ten allocate-and-copy-range bodies with the copy loop inline.
//
// Each allocates room for the count through the size-dispatch helper, with the
// usual zero arm, then copies the range into it and returns the block, which
// never leaves the register the allocator left it in.
//
// The copy loop is one induction variable, not two: retail computes the block
// minus the source once and then recomputes the destination from the source on
// every pass. Which of the two pointers survives is decided by the parameter
// order of the copy helper -- taking the destination FIRST eliminates it and
// drives the loop on the source, which is what retail does; taking it last
// eliminates the source instead and produces the mirror image, same size,
// different registers. Writing the loop at the call site rather than in a
// helper does the same wrong thing.
//
// The null test on the destination inside the loop is placement new. The six
// four-byte bodies copy one word, the four eight-byte ones copy two.

void *bfmeNewAlloc(unsigned int bytes);				// retail 0x00881F30
void *bfmeAllocNode(unsigned int bytes);			// retail 0x0082E540

inline void *bfmeAllocate(unsigned int bytes)
{
	if (bytes > 0x80)
		return bfmeNewAlloc(bytes);

	return bfmeAllocNode(bytes);
}

inline void * __cdecl operator new(unsigned int, void *where) { return where; }

struct BfmeElem4 { int m_bfmeValue; };
struct BfmeElem8 { int m_bfmeA; int m_bfmeB; };

inline void bfmeUninitCopy4(BfmeElem4 *result, const BfmeElem4 *first, const BfmeElem4 *last)
{
	for (; first != last; ++first, ++result)
		new (result) BfmeElem4(*first);
}

inline void bfmeUninitCopy8(BfmeElem8 *result, const BfmeElem8 *first, const BfmeElem8 *last)
{
	for (; first != last; ++first, ++result)
		new (result) BfmeElem8(*first);
}

// ?bfmeMake_000A7820@@YGPAUBfmeElem4@@IPBU1@0@Z
BfmeElem4 * __stdcall bfmeMake_000A7820(unsigned int count,
	const BfmeElem4 *first, const BfmeElem4 *last)
{
	BfmeElem4 *block;

	if (count)
		block = (BfmeElem4 *)bfmeAllocate(count * sizeof(BfmeElem4));
	else
		block = 0;

	bfmeUninitCopy4(block, first, last);

	return block;
}

// ?bfmeMake_000BB620@@YGPAUBfmeElem4@@IPBU1@0@Z
BfmeElem4 * __stdcall bfmeMake_000BB620(unsigned int count,
	const BfmeElem4 *first, const BfmeElem4 *last)
{
	BfmeElem4 *block;

	if (count)
		block = (BfmeElem4 *)bfmeAllocate(count * sizeof(BfmeElem4));
	else
		block = 0;

	bfmeUninitCopy4(block, first, last);

	return block;
}

// ?bfmeMake_000CD450@@YGPAUBfmeElem4@@IPBU1@0@Z
BfmeElem4 * __stdcall bfmeMake_000CD450(unsigned int count,
	const BfmeElem4 *first, const BfmeElem4 *last)
{
	BfmeElem4 *block;

	if (count)
		block = (BfmeElem4 *)bfmeAllocate(count * sizeof(BfmeElem4));
	else
		block = 0;

	bfmeUninitCopy4(block, first, last);

	return block;
}

// ?bfmeMake_00134C90@@YGPAUBfmeElem4@@IPBU1@0@Z
BfmeElem4 * __stdcall bfmeMake_00134C90(unsigned int count,
	const BfmeElem4 *first, const BfmeElem4 *last)
{
	BfmeElem4 *block;

	if (count)
		block = (BfmeElem4 *)bfmeAllocate(count * sizeof(BfmeElem4));
	else
		block = 0;

	bfmeUninitCopy4(block, first, last);

	return block;
}

// ?bfmeMake_0016FF30@@YGPAUBfmeElem4@@IPBU1@0@Z
BfmeElem4 * __stdcall bfmeMake_0016FF30(unsigned int count,
	const BfmeElem4 *first, const BfmeElem4 *last)
{
	BfmeElem4 *block;

	if (count)
		block = (BfmeElem4 *)bfmeAllocate(count * sizeof(BfmeElem4));
	else
		block = 0;

	bfmeUninitCopy4(block, first, last);

	return block;
}

// ?bfmeMake_0036CA60@@YGPAUBfmeElem4@@IPBU1@0@Z
BfmeElem4 * __stdcall bfmeMake_0036CA60(unsigned int count,
	const BfmeElem4 *first, const BfmeElem4 *last)
{
	BfmeElem4 *block;

	if (count)
		block = (BfmeElem4 *)bfmeAllocate(count * sizeof(BfmeElem4));
	else
		block = 0;

	bfmeUninitCopy4(block, first, last);

	return block;
}

// ?bfmeMake_000B0200@@YGPAUBfmeElem8@@IPBU1@0@Z
BfmeElem8 * __stdcall bfmeMake_000B0200(unsigned int count,
	const BfmeElem8 *first, const BfmeElem8 *last)
{
	BfmeElem8 *block;

	if (count)
		block = (BfmeElem8 *)bfmeAllocate(count * sizeof(BfmeElem8));
	else
		block = 0;

	bfmeUninitCopy8(block, first, last);

	return block;
}

// ?bfmeMake_003CDA80@@YGPAUBfmeElem8@@IPBU1@0@Z
BfmeElem8 * __stdcall bfmeMake_003CDA80(unsigned int count,
	const BfmeElem8 *first, const BfmeElem8 *last)
{
	BfmeElem8 *block;

	if (count)
		block = (BfmeElem8 *)bfmeAllocate(count * sizeof(BfmeElem8));
	else
		block = 0;

	bfmeUninitCopy8(block, first, last);

	return block;
}

// ?bfmeMake_00698B50@@YGPAUBfmeElem8@@IPBU1@0@Z
BfmeElem8 * __stdcall bfmeMake_00698B50(unsigned int count,
	const BfmeElem8 *first, const BfmeElem8 *last)
{
	BfmeElem8 *block;

	if (count)
		block = (BfmeElem8 *)bfmeAllocate(count * sizeof(BfmeElem8));
	else
		block = 0;

	bfmeUninitCopy8(block, first, last);

	return block;
}

// ?bfmeMake_006BE9C0@@YGPAUBfmeElem8@@IPBU1@0@Z
BfmeElem8 * __stdcall bfmeMake_006BE9C0(unsigned int count,
	const BfmeElem8 *first, const BfmeElem8 *last)
{
	BfmeElem8 *block;

	if (count)
		block = (BfmeElem8 *)bfmeAllocate(count * sizeof(BfmeElem8));
	else
		block = 0;

	bfmeUninitCopy8(block, first, last);

	return block;
}
