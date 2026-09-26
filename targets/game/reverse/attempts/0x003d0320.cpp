// ?apply@Gen00006D20@@QAEXPAVY1RangeWrapper@@@Z
// partial score=0.28 date=2026-09-21
// The body at retail RVA 0x003D0320 is the element callee that
// Rva003D08F0::run(Y1RangeWrapper*) invokes as ( *it )->apply( wrapper ) --
// see Code/GameEngine/Source/Common/Y1GatedRangeDispatch.cpp, which already
// declares `class Gen00006D20 { void apply( Y1RangeWrapper *wrapper ); };`
// as a callee-only forward declaration (address-derived, IDENTITY IS NOT
// RECOVERED there).  This TU supplies the real definition.
//
// Retail: a predicate test through the object's own Rva003CDDB0Range base
// (0x003CDDB0, already landed) gates the whole body.  It then builds an
// 8-byte Coord out of the wrapper's context object (fields +0x38/+0x3c) and
// walks a fixed 4-entry Rva003D2B80Child* array at this+0x10, looking each
// child up with the pinned lookup at 0x003CCFA0 (Rva003D2B80Child::lookup),
// accumulating a 16-bit count from the wrapper's filter object (+4, then
// +0x1c) into the found element, and finally doing the same
// bfmeLowerRQ/bfmeInsertRQ sorted-vector insert already proven by
// Rva003D0190::ensure (this+0x30 BfmeVecRQ, same two ILT thunks
// 0x00016B21 / 0x00034D7E).
//
// No caller, vtable slot, or string names the wrapper's filter/context
// fields, so they keep raw offsets rather than invented member names.

class Y1RangeWrapper
{
public:
	char m_pad00[4];
	void *m_filter;   // +0x04, holds the range sub-object at +8 and a word count at +0x1c
	void *m_context;  // +0x08, holds two ints at +0x38/+0x3c
};

struct Rva003CDDB0Range
{
	const int *m_begin;
	const int *m_end;

	bool method(const Rva003CDDB0Range *other);
};

struct Rva003D2B80Coord
{
	int m_f0;
	int m_f4;
};

struct Rva003D1380Elem
{
	char m_pad00[0x30];
	int m_count; // +0x30
};

class Rva003D2B80Child
{
public:
	Rva003D1380Elem *lookup(Rva003D2B80Coord coord);
};

struct BfmeCmpRQ
{
	char m_bfmeRawRQ;
};

void ** __cdecl bfmeLowerRQ(void **begin, void **end, void **key, BfmeCmpRQ compare, int spare);

class BfmeVecRQ
{
public:
	void bfmeInsertRQ(void **where, void **key);

	void **m_bfmeBeginRQ;
	void **m_bfmeEndRQ;
};

class Gen00006D20 : public Rva003CDDB0Range
{
public:
	void apply(Y1RangeWrapper *wrapper);

	char m_pad08[8];
	Rva003D2B80Child *m_kids[4];   // +0x10
	char m_pad20[0x10];
	BfmeVecRQ m_vec;               // +0x30
};

void Gen00006D20::apply(Y1RangeWrapper *wrapper)
{
	if (!method((const Rva003CDDB0Range *)((char *)wrapper->m_filter + 8)))
		return;

	unsigned char *ctx = (unsigned char *)wrapper->m_context;
	Rva003D2B80Coord coord;
	coord.m_f0 = *(int *)(ctx + 0x38);
	coord.m_f4 = *(int *)(ctx + 0x3c);

	Rva003D2B80Child **it = m_kids;
	for (int count = 4; count != 0; --count, ++it)
	{
		Rva003D2B80Child *child = *it;
		if (child == 0)
			continue;

		Rva003D1380Elem *found = child->lookup(coord);
		if (found == 0)
			continue;

		unsigned short n = *(unsigned short *)((char *)wrapper->m_filter + 0x1c);
		found->m_count += n;

		BfmeCmpRQ compare;
		compare.m_bfmeRawRQ = 0;
		void *key = found;
		void **foundIt = bfmeLowerRQ((void **)m_vec.m_bfmeBeginRQ, (void **)m_vec.m_bfmeEndRQ, &key, compare, 0);
		if (foundIt == (void **)m_vec.m_bfmeEndRQ || *foundIt != key)
			m_vec.bfmeInsertRQ(foundIt, &key);
	}
}
