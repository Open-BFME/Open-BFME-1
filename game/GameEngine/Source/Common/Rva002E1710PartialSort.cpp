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

// Retail's call sites reach both bodies through their own incremental-link
// ILTs, which are defined by the matched thunk rows: ILT 0x00024DD9 jumps to the
// make-heap body 0x002E0CD0 and ILT 0x0000C437 jumps to the pop-heap body
// 0x002E0BC0.  Referencing those thunks keeps the call displacements at the
// addresses retail actually encodes, and it keeps the observed stack shapes
// (five words for the make-heap call, the copied twelve-byte record plus six
// words for the pop-heap call) which the four leading zero words prove.
extern void j_00024dd9();
extern void j_0000c437();

typedef void (__cdecl *MakeHeapCall)(void *first, void *last, void *compare,
	int zero, int alsoZero);
typedef void (__cdecl *PopHeapCall)(void *first, Gen002E0D70Rec *last,
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

	MakeHeapCall makeHeap = (MakeHeapCall)j_00024dd9;
	makeHeap(first, middle, compare, 0, 0);
	PopHeapCall popHeap = (PopHeapCall)j_0000c437;
	for (Gen002E0D70Rec *i = middle; i < last; ++i)
	{
		if (i->m_first < first->m_first)
		{
			popHeap(first, middle, i, *i, compare, 0);
		}
	}
	bfmeSortVOZ(first, middle, compare);
}
