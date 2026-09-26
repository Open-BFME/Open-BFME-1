// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: three small-allocator bodies out of d_0005b6c0.asm.
//
// 0x0005E1A0 is a singly-chained arena block allocator: it asks the CRT for
// eight bytes MORE than the caller wanted, links the block onto the list head at
// this+0, and hands back the payload eight bytes in. malloc is reached through
// `ff 15 [__imp__malloc]`, the dllimport form the real vendored <stdlib.h> emits
// under /MD -- a direct five-byte REL32 would be the /MT spelling.
//
// 0x0005E200 and 0x0005EEB0 are the same function BYTE FOR BYTE, relocations
// included: both test the requested size against 0x80, tail into the SAME
// out-of-line growth routine at 0x0005CBD0 for anything larger, and otherwise
// point the cursor at the inline buffer at this+4. The compiler did not fold
// them, so they are two distinct types over one shared implementation, which is
// why the growth routine is declared once in a common base here rather than
// twice. The call is thiscall with ecx untouched from the caller's own `this`
// and the pushed size never cleaned off the stack -- both of which say the
// callee cleans, i.e. a member function, not a free helper.
//
// Identity is address-derived.

#include <stdlib.h>

typedef unsigned int UnsignedInt;

class Rva0005CBD0Buffer
{
protected:
	void grow(UnsignedInt size);

	char *m_cursor;										///< retail this+0x00
	char m_buffer[0x80];								///< retail this+0x04
};

class Rva0005E200Buffer : public Rva0005CBD0Buffer
{
public:
	char *reserve(UnsignedInt size);
};

class Rva0005EEB0Buffer : public Rva0005CBD0Buffer
{
public:
	char *reserve(UnsignedInt size);
};

// ?reserve@Rva0005E200Buffer@@QAEPADI@Z
char *Rva0005E200Buffer::reserve(UnsignedInt size)
{
	if (size > 0x80)
	{
		grow(size);
		return m_cursor;
	}

	m_cursor = m_buffer;
	return m_buffer;
}

// ?reserve@Rva0005EEB0Buffer@@QAEPADI@Z
char *Rva0005EEB0Buffer::reserve(UnsignedInt size)
{
	if (size > 0x80)
	{
		grow(size);
		return m_cursor;
	}

	m_cursor = m_buffer;
	return m_buffer;
}

// ---------------------------------------------------------------------------

struct Rva0005E1A0Block
{
	Rva0005E1A0Block *m_next;							///< block+0x00
	UnsignedInt m_unreconstructed_04;					///< block+0x04
};

class Rva0005E1A0Arena
{
public:
	void *allocate(UnsignedInt size);

private:
	Rva0005E1A0Block *m_head;							///< retail this+0x00
};

// ?allocate@Rva0005E1A0Arena@@QAEPAXI@Z
void *Rva0005E1A0Arena::allocate(UnsignedInt size)
{
	Rva0005E1A0Block *block = (Rva0005E1A0Block *)malloc(size + 8);

	if (block == 0)
	{
		return block;
	}

	block->m_next = m_head;
	m_head = block;

	return block + 1;
}
