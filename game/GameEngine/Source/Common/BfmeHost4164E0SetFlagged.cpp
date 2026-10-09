// cl: /O2 /Ob1 /DNDEBUG /MD
//
// Retail 0x004164E0 (87B): when arg is non-zero, forward (arg,0,0,-2) into the
// sibling thiscall at ILT 0x0003A2A1 (body 0x00416440) then OR bit 2 on the
// dword at +0x110. When arg is zero, lazily operator-new(0x50) plus the
// Rva00412140 ctor (ILT 0x00037475) into +0x68, clear byte +0x38, AND-clear
// bit 2 on +0x110.

void *__cdecl operator new(unsigned int);

class Rva00412140
{
public:
	Rva00412140() throw();							///< ILT 0x00037475 -> 0x00412140

	char m_pad[0x38];
	char m_at38;							///< +0x38
	char m_tail[0x50 - 0x39];
};

struct RGBColor;

class Drawable
{
public:
	void colorFlash(const RGBColor *color, unsigned int decayFrames, unsigned int attackFrames, unsigned int sustainAtPeak);	///< ILT 0x0003A2A1 -> 0x00416440
};

class BfmeHost4164E0
{
public:
	void setFlagged(int on);

private:
	char m_pad00[0x68];
	Rva00412140 *m_child;					///< +0x68
	char m_pad6C[0x110 - 0x6C];
	unsigned m_flags;						///< +0x110
};

// ?setFlagged@BfmeHost4164E0@@QAEXH@Z
void BfmeHost4164E0::setFlagged(int on)
{
	if (on)
	{
		reinterpret_cast<Drawable *>(this)->colorFlash(reinterpret_cast<const RGBColor *>(on), 0, 0, (unsigned int)-2);
		m_flags |= 4;
		return;
	}
	if (!m_child)
	{
		m_child = new Rva00412140;
	}
	m_child->m_at38 = 0;
	m_flags &= ~4u;
}
