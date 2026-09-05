// ?bfmeDrop@Gen_008991E0@@UAEXXZ
// partial score=0.35 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Slot 1 of the 16-slot vtable at retail 0x01135D68 (Rva899F00Base, see
// ThreadClassCtorThunk.cpp).  Slot 0 of the same vtable is
// Gen_008991B0::bfmeBump (Bfme5FiftyFour.cpp), which increments the
// saturating twelve-bit counter packed into bits 16-27 of the dword at
// this+4 (the same field is readable as a 16-bit word at this+6).  This
// slot decrements it, and on the transition down to zero performs a
// one-time (guarded by bit30) self-registration into the fixed global
// registry array at retail 0x01337810 -- the same {capacity,count,data}
// record documented against 0x00899F00 in reverse/re_attempts.log --
// tail-calling this object's own vtable slot 2 if the registry is full.

class Gen_008991E0
{
public:
	virtual void unused0();
	virtual void bfmeDrop();
	virtual void bfmeGrow();

private:
	// vptr occupies +0x00. The count is read as the plain 16-bit field
	// m_bfmeCount (retail: mov ax,[this+6]) but stored back through a
	// full-dword read/modify/write of m_bfmeBits (retail: mov edx,[this+4]),
	// so both views of the same storage are declared here.
	union
	{
		unsigned int	m_bfmeBits;		// +0x04
		struct
		{
			unsigned short	m_bfmeLow;		// +0x04
			unsigned short	m_bfmeCount;	// +0x06
		};
	};
};

struct BfmeRegistryDX
{
	int		m_capacity;		// +0x00
	int		m_count;		// +0x04
	void	**m_data;		// +0x08
};

extern BfmeRegistryDX *g_bfmeRegistryDX;	// retail 0x01337810

// ?bfmeDrop@Gen_008991E0@@QAEXXZ
void Gen_008991E0::bfmeDrop()
{
	// Hand-masked, not a C bitfield: see Bfme5FiftyFour.cpp's note that a
	// bitfield store compiles to xor-and-xor instead of and-shift-or.
	unsigned int index = m_bfmeCount & 0xFFF;
	index--;

	unsigned int slot = index;
	if (index > 0xFFF)
		slot = 0xFFF;

	unsigned int bits = (m_bfmeBits & 0xF000FFFF) | (slot << 16);
	m_bfmeBits = bits;

	if (index != 0)
		return;

	if (bits & 0x40000000)
		return;

	bits |= 0x40000000;
	m_bfmeBits = bits;

	BfmeRegistryDX *registry = g_bfmeRegistryDX;
	int regCount = registry->m_count;

	if (regCount >= registry->m_capacity)
	{
		bfmeGrow();
		return;
	}

	if (regCount < registry->m_capacity)
	{
		registry->m_data[regCount] = this;
		registry->m_count = registry->m_count + 1;
		return;
	}

	bits &= ~0x40000000;
	m_bfmeBits = bits;
}
