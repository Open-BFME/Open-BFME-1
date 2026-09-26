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
	// Declared as a thiscall that returns `this` so the call site can keep the
	// pointer in eax across the call (same bytes as ??0Rva00412140@@QAE@XZ).
	Rva00412140 *construct();				///< ILT 0x00037475 -> 0x00412140

	char m_pad[0x38];
	char m_at38;							///< +0x38
	char m_tail[0x50 - 0x39];
};

class BfmeHost4164E0
{
public:
	void apply(int a, int b, int c, int d);	///< ILT 0x0003A2A1 -> 0x00416440
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
		apply(on, 0, 0, -2);
		m_flags |= 4;
		return;
	}
	if (!m_child)
	{
		Rva00412140 *p = (Rva00412140 *)operator new(sizeof(Rva00412140));
		if (p)
			p = p->construct();
		else
			p = 0;
		m_child = p;
	}
	m_child->m_at38 = 0;
	m_flags &= ~4u;
}
