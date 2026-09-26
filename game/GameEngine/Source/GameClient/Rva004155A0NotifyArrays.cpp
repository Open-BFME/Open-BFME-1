// ?notifyArrays@Rva004155A0Owner@@QAEXHHH@Z
// Retail 0x004155A0 has two callback arrays and stores the current state
// before it loads the primary array.

struct Rva004155A0Primary
{
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
	virtual void notify(int a, int b, int c);
};

struct Rva004155A0Secondary
{
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8();
	virtual void notify(int a, int b, int c);
};

struct Rva004155A0Owner
{
	char m_pad[0x150];
	Rva004155A0Primary ** volatile m_primary;
	int m_154;
	Rva004155A0Secondary **m_secondary;
	char m_pad2[0x23c - 0x15c];
	volatile int m_current;
	char m_pad3[0x319 - 0x240];
	volatile bool m_dirty;
	void notifyArrays(int a, int b, int c);
};

void Rva004155A0Owner::notifyArrays(int a, int b, int c)
{
	m_current = -1;
	m_dirty = true;
	for (Rva004155A0Primary **p = m_primary; *p; ++p)
		(*p)->notify(a, b, c);
	for (Rva004155A0Secondary **s = m_secondary; s; ++s) {
		if (!*s)
			break;
		(*s)->notify(a, b, c);
	}
}
