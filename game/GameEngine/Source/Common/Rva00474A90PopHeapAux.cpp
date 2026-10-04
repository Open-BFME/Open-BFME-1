// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// STLport __pop_heap_aux over the sixteen-byte record of the neighbouring heap
// helpers. Retail 0x00474A90 steps back one element and forwards it by value to
// __pop_heap at 0x004748F0 through the 0x0000561E jump stub.

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

// Retail reaches __pop_heap (0x004748F0) through the 0x0000561E ILT stub, which
// carries the cdecl no-argument thunk signature. The body is called with the six
// stack arguments __pop_heap really takes, so the stub is entered through a
// function pointer of the callee's own prototype.
extern void j_0000561e();

typedef void (__cdecl *PopHeapFn)(Rva004748F0Element *first, Rva004748F0Element *last,
	Rva004748F0Element *result, Rva004748F0Element value,
	Rva004748F0Compare comp, int *);

void Rva00474A90PopHeapAux(Rva004748F0Element *first, Rva004748F0Element *last,
	Rva004748F0Element *, Rva004748F0Compare comp)
{
	((PopHeapFn)(void *)j_0000561e)(first, last - 1, last - 1, *(last - 1), comp, (int *)0);
}
