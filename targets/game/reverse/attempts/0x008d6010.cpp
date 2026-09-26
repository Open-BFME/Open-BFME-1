// ?bfmeDrop@Rva008D6010Node@@QAEXXZ
// partial score=0.95 date=2026-09-11
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// Size is exactly 163 and every instruction matches retail except one adjacent
// pair. Retail zeroes esi at +0x57 and stores the null into m_valueBits at
// +0x59. This body stores first and zeroes esi second, which moves seven bytes.
// MSVC schedules the immediate store into the gap between the 16-bit load and
// the following full-register and, while retail put it between the xor and that
// load. Nothing in the source reaches that choice: /G5 /G6 /G7 /Ot /Os /Oy-
// /Oi- /Og /Ox /Gy /Ob1 /GF /Gs all leave it, and so do the read-before-store
// order, a _ReadBarrier at the store, and an explicit zero-extension union,
// which spills to the stack and costs 20 bytes.
//
// The volatile on m_valueBits makes the second read at +0x4A a real load.
// Without it MSVC reuses the pointer from the guard chain, which also steals
// the register that retail spends on the kind and shortens the body by 3 bytes.
// The _ReadWriteBarrier keeps the count reload below the null store. The union
// view of the packed dword is what produces retail and+or bitfield insert at
// +0x85; a 12-bit bitfield assignment emits MSVC xor/and/xor insert instead.
//
// Identity is address-derived. The evidence for the Apt family is the
// g_bfmeFallbackDB compare at VA 0x013379BC, the 12-bit reference count packed
// at bits 16 to 27 that both this node and its value share, and the named
// callee BfmeThing936F::bfmeGo936F at 0x008D1F80. No caller names this body.

extern "C" void _ReadWriteBarrier( void );
#pragma intrinsic( _ReadWriteBarrier )


class BfmeThing936F
{
public:
	void bfmeGo936F();
};

class Rva008D6010Value
{
public:
	virtual void bfmeSlot00();
	virtual void bfmeDropValue();

	unsigned int m_kind;
};

extern Rva008D6010Value *g_bfmeFallbackDB;

class Rva008D6010Node
{
public:
	virtual void bfmeSlot00();
	virtual void bfmeSlot04();
	virtual void bfmeFinish();

	void bfmeDrop();

private:
	union
	{
		struct
		{
			unsigned int m_low : 16;
			unsigned int m_count : 12;
			unsigned int m_high : 4;
		};
		unsigned int m_packed;
	};
	unsigned char m_pad08[ 0x14 - 8 ];
	unsigned int volatile m_valueBits;
	unsigned char m_pad18[ 0x2C - 0x18 ];
	BfmeThing936F *m_notify;
};

void Rva008D6010Node::bfmeDrop()
{
	unsigned int count = m_count;
	Rva008D6010Value *value = (Rva008D6010Value *)(m_valueBits & ~1u);
	if ( value != 0 && value != g_bfmeFallbackDB && count == 2 )
	{
		unsigned int kind = value->m_kind;
		if ( (kind & 0x3f) == 0x1c &&
			!((unsigned char)(~(kind >> 15)) & 1) &&
			(kind & 0x0fff0000) == 0x00010000 )
		{
			Rva008D6010Value *owned = (Rva008D6010Value *)(m_valueBits & ~1u);
			if ( owned != 0 )
				owned->bfmeDropValue();
			m_valueBits = 0;
			_ReadWriteBarrier();
			count = m_count;
		}
	}

	--count;
	m_notify->bfmeGo936F();

	unsigned int stored = count;
	if ( stored > 0xfff )
		stored = 0xfff;
	m_packed = (m_packed & 0xf000ffff) | (stored << 16);
	if ( count == 0 )
		bfmeFinish();
}
