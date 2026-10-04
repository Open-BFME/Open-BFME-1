// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// STLport __pop_heap over the sixteen-byte record used by the neighbouring
// heap helpers. Retail 0x004748F0 copies three scalar words and an
// AsciiString, then calls __adjust_heap at 0x00474330 with the element count.

#include "string_base.h"

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString(void) {}
	AsciiString &operator=(const AsciiString &other)
	{
		set(other);
		return *this;
	}
};

struct Rva004748F0Element
{
	int m_key;
	int m_second;
	int m_third;
	AsciiString m_name;
};

struct Rva004748F0Compare
{
	int m_state;
};

// Both retail call sites go through ILT thunks that are 5-byte jumps with
// no argument handling of their own: 0x0047441F calls ?j_00049657@@YAXXZ
// (push_heap) and 0x0047496E calls ?j_00018abb@@YAXXZ (adjust_heap, which
// jumps straight back into the body defined below). The cdecl cleanup
// stays with the caller, so reach the thunks through a cdecl pointer
// carrying the helper's own signature; that keeps the pushed arguments
// and the trailing `add esp, 0x20` identical to retail.
extern void j_00049657();
extern void j_00018abb();

typedef void (__cdecl *PushHeapFn)(Rva004748F0Element *first,
	int holeIndex, int topIndex, Rva004748F0Element value,
	Rva004748F0Compare comp);

void bfmeAdjustHeap00474330(Rva004748F0Element *first, int holeIndex,
	int len, Rva004748F0Element value, Rva004748F0Compare comp)
{
	int topIndex = holeIndex;
	int secondChild = 2 * holeIndex + 2;
	while (secondChild < len)
	{
		if (first[secondChild].m_key < first[secondChild - 1].m_key)
			--secondChild;
		first[holeIndex] = first[secondChild];
		holeIndex = secondChild;
		secondChild = 2 * (secondChild + 1);
	}
	if (secondChild == len)
	{
		first[holeIndex] = first[secondChild - 1];
		holeIndex = secondChild - 1;
	}
	union { void (*fn)(); PushHeapFn call; } push = { j_00049657 };
	push.call(first, holeIndex, topIndex, value, comp);
}

void Rva004748F0PopHeap(Rva004748F0Element *first,
	Rva004748F0Element *last, Rva004748F0Element *result,
	Rva004748F0Element value, Rva004748F0Compare comp, int *)
{
	*result = *first;
	union { void (*fn)(); PushHeapFn call; } adjust = { j_00018abb };
	adjust.call(first, 0, last - first, value, comp);
}
