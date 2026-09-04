// ?claim@Rva008003F0Arena@@QAEPAXH_N@Z
// partial score=0.9 date=2026-09-04
// ?claim@Rva008003F0Arena@@QAEPAXH_N@Z
// partial score=0.90 date=2026-09-04
// cl: /GX-
// Arena bump claim: optional 4-byte pad; assert false util.cpp:209.
// Near-miss: 78/87 — add eax,edi vs retail add edi,eax for next=size+(used+pad).

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail( const char *expr, const char *file, int line );
};

extern Rva007EB810Diag *Rva007EB810Get();

class Rva008003F0Arena
{
public:
	void *claim( int size, bool align );

	char *m_base;
	unsigned m_cap;
	unsigned m_used;
};

void *Rva008003F0Arena::claim( int size, bool align )
{
	unsigned pad;
	if( align )
		pad = ( -(int)m_used ) & 3;
	else
		pad = 0;
	unsigned used = m_used;
	unsigned next = (unsigned)size + (used + pad);
	if( next > m_cap )
	{
		Rva007EB810Get()->fail(
			"false",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\util.cpp",
			0xd1 );
		return 0;
	}
	char *result = m_base + used + pad;
	m_used = next;
	return result;
}
