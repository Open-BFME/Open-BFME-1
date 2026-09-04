// ?apply@Rva007F95A0Host@@QAEXPAVRva007F95A0Dest@@I@Z
// partial score=0.93 date=2026-09-04
// cl: /O2 /Ob0
// Converted from Code/gen_asm/d_007f2a50.asm (?d_007f95a0@@YAXXZ).
// Rva007E9B70Get vslot 2 (now) plus extra, stored at dest+0x14; shrink m_18.

struct Rva007E9B70Obj
{
	virtual void v0();
	virtual void v1();
	virtual unsigned now();
};

Rva007E9B70Obj *Rva007E9B70Get();

class Rva007F95A0Dest
{
public:
	unsigned m_00;
	unsigned m_04;
	unsigned m_08;
	unsigned m_0C;
	unsigned m_10;
	unsigned m_14;
};

class Rva007F95A0Host
{
public:
	void apply(Rva007F95A0Dest *dest, unsigned extra);

	unsigned m_00;
	unsigned m_04;
	unsigned m_08;
	unsigned m_0C;
	unsigned m_10;
	unsigned m_14;
	unsigned m_18;
};

void Rva007F95A0Host::apply(Rva007F95A0Dest *dest, unsigned extra)
{
	unsigned n = Rva007E9B70Get()->now();
	unsigned e = extra;
	Rva007F95A0Dest *d = dest;
	n = e + n;
	d->m_14 = n;
	unsigned cap = m_18;
	if (cap != 0 && n < cap)
		m_18 = n;
}
