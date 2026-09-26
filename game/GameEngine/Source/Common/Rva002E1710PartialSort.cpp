// cl: /DNDEBUG /MD /O2 /EHsc /Iinputs/reference/shims/stringinline

// Open-BFME: authored BFME reconstruction of the STLport-like partial-sort
// body at retail 0x002E1710, 129 bytes.  This is a neutral reconstruction,
// not a pristine third-party source or a vendored STLport claim.
//
// The body is the twelve-byte heap-select sibling of the already matched
// 0x002E0CD0 make-heap, 0x002E0BC0 pop-heap, and 0x002E11E0 sort-heap bodies.
// The record is proved by those three calls and by the inline copy at +4:
// an int, one narrow StringBase handle, and a byte.  Its ordering predicate
// is only observed here as the signed first-dword comparison; no semantic
// field name is assigned.

#include "StringInline.h"

// Keep this existing callee-facing type spelling: it is part of the matched
// gen002E0BC0 decorated ABI.  The type is only a proven 12-byte record layout;
// it carries no application-class identity.
struct Gen002E0D70Rec
{
	int m_first;
	AsciiString m_string;
	char m_byte;
};

void gen002E0CD0(void *first, void *last, void *compare, int zero,
	int alsoZero);

void gen002E0BC0(void *first, Gen002E0D70Rec *last,
	Gen002E0D70Rec *result, Gen002E0D70Rec value, void *compare, int zero);

void bfmeSortVOZ(void *first, void *middle, void *compare);

// ?rva002E1710PartialSort@@YAXPAX00H0@Z
void rva002E1710PartialSort(void *firstArgument, void *middleArgument,
	void *lastArgument, int, void *compareArgument)
{
	Gen002E0D70Rec *first = (Gen002E0D70Rec *)firstArgument;
	Gen002E0D70Rec *middle = (Gen002E0D70Rec *)middleArgument;
	Gen002E0D70Rec *last = (Gen002E0D70Rec *)lastArgument;
	void *compare = compareArgument;

	gen002E0CD0(first, middle, compare, 0, 0);
	for (Gen002E0D70Rec *i = middle; i < last; ++i)
	{
		if (i->m_first < first->m_first)
		{
			gen002E0BC0(first, middle, i, *i, compare, 0);
		}
	}
	bfmeSortVOZ(first, middle, compare);
}
