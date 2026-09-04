// ??0Rva004945E0Subsystem@@QAE@H@Z
// partial score=0.99 date=2026-09-04
// cl: /DNDEBUG /MD
// Address-derived subsystem constructor at retail 0x004945E0.

struct Rva004945E0Base
{
	Rva004945E0Base();

	void *m_vtable;
	char m_pad04[4];
	volatile int m_08;
	volatile int m_0c;
	volatile int m_10;
	volatile int m_14;
	volatile int m_18;
	volatile int m_1c;
	volatile unsigned char m_flags;
	char m_pad21[3];
	volatile int m_24;
	volatile int m_28;
	volatile int m_2c;
	volatile int m_30;
	volatile int m_34;
};

extern void *Rva004945E0Vtable[];

class Rva004945E0Subsystem
{
public:
	Rva004945E0Subsystem( int value );

private:
	Rva004945E0Base m_base;
};

Rva004945E0Subsystem::Rva004945E0Subsystem( int value )
{
	unsigned char flags = m_base.m_flags;
	int zero = 0;
	flags &= 0xf8;
	m_base.m_flags = flags;
	m_base.m_08 = zero;
	m_base.m_1c = zero;
	m_base.m_28 = zero;
	m_base.m_2c = zero;
	m_base.m_34 = zero;
	m_base.m_0c = zero;
	m_base.m_10 = zero;
	m_base.m_14 = zero;
	m_base.m_18 = zero;
	m_base.m_vtable = Rva004945E0Vtable;
	m_base.m_24 = -1;
	m_base.m_30 = value;
}
