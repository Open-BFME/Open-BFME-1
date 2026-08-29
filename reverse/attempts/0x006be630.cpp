// ?d_006be630@@YAXXZ
// partial score=0.75 date=2026-08-29
// cl: /DNDEBUG /MD /EHsc
//
// A 2D bit-plane membership test, one of five identical copies in the image
// (0x006BE630, 0x006CB500, 0x0074B410, 0x0074BA50, 0x0074BAC0).
//
// Four range guards and an unsigned span check funnel into a single exit:
// reject a negative x, a negative y, a y past the height at +0x0c and an x past
// the width at +0x08, then index the plane at pitch*y + (x>>3) and test bit
// x&7 of that byte.
//
// Two things the bytes settle. The span check is UNSIGNED (jae, not jge), so a
// pitch*y product that overflows into a negative is rejected by the same test
// rather than indexing behind the buffer. And the mask is built in a 32-bit
// register but tested eight bits wide (test al,dl), which is what an unsigned
// char element against an int mask compiles to.
//
// The reason this body sat parked as "register allocation": retail keeps `this`
// in esi and RE-READS the begin pointer at the index (8b 4e 5c), while the
// earlier reconstruction cached begin in esi and kept `this` in ecx. That is not
// an allocation tie-break -- it follows from whether begin is ever put in a
// register at all. Retail never does: the span check consumes it as a memory
// operand of the subtraction (2b 56 5c), so nothing holds it, and the index
// loads it fresh. Writing `m_end - m_begin` and `m_begin[offset]` as separate
// reads, with NO local for begin, reproduces that -- a local is exactly what
// would make the compiler cache it and take esi for the value instead of `this`.

class Open2BitPlane6BE630
{
public:
	unsigned char m_beforeWidth[0x08];
	int m_width;						// retail this+0x08
	int m_height;						// retail this+0x0c
	unsigned char m_beforePitch[0x34 - 0x10];
	int m_pitch;						// retail this+0x34
	unsigned char m_beforeBegin[0x5c - 0x38];
	const unsigned char *m_begin;				// retail this+0x5c
	const unsigned char *m_end;				// retail this+0x60

	bool test(int x, int y) const;
};

// A second view of the same pointer, used only for the index. Reading begin
// through a distinct type is an attempt to stop the compiler treating the span
// check's read and the index's read as one common subexpression -- which is what
// puts begin in a register and takes esi away from `this`.
class Open2BitPlaneCells6BE630
{
public:
	unsigned char m_beforeCells[0x5c];
	const unsigned char *m_cells;				// retail this+0x5c
};

// @?test@Open2BitPlane6BE630@@QBE_NHH@Z 0x006BE630
bool Open2BitPlane6BE630::test(int x, int y) const
{
	// One combined guard, not four statements: retail funnels all four rejections
	// into a single exit that pops esi, which is also what makes it save esi up
	// front and keep `this` there for the whole body.
	if (x < 0 || y < 0 || y >= m_height || x >= m_width)
		return false;

	int xByte = x >> 3;
	int offset = m_pitch * y + xByte;
	if ((unsigned int)offset >= (unsigned int)(m_end - m_begin))
		return false;

	int mask = 1 << (x & 7);
	return (((const Open2BitPlaneCells6BE630 *)this)->m_cells[offset] & mask) != 0;
}
