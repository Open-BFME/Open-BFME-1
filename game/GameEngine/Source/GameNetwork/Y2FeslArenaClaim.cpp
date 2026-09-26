// cl: /GX-
// jabba util.cpp arena claim @ 0x008003F0 (87B).

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail( const char *expr, const char *file, int line );
};

extern Rva007EB810Diag *Rva007EB810Get();

class Rva00800460Arena
{
public:
	void *claim( int size, bool align );

	char *m_base;
	unsigned m_cap;
	unsigned m_used;
};

void *Rva00800460Arena::claim( int size, bool align )
{
	unsigned pad;
	if( align )
		pad = ( -(int)m_used ) & 3;
	else
		pad = 0;
	if( m_used + pad + (unsigned)size > m_cap )
	{
		Rva007EB810Get()->fail(
			"false",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\util.cpp",
			0xd1 );
		return 0;
	}
	char *result = m_base + m_used + pad;
	m_used = m_used + pad + (unsigned)size;
	return result;
}
