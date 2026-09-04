// cl: /GX-
// jabba util.cpp arena append @ 0x00800460 (135B).

#include <string.h>

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
	char *append( const char *text );

	char *m_base;
	unsigned m_cap;
	unsigned m_used;
};

char *Rva00800460Arena::append( const char *text )
{
	if( text == 0 )
		return 0;

	unsigned len = (unsigned)strlen( text );
	unsigned used = m_used;
	unsigned next = used + len + 1;
	char *dest;

	if( next > m_cap )
	{
		Rva007EB810Get()->fail(
			"false",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\util.cpp",
			0xd1 );
		dest = 0;
	}
	else
	{
		dest = m_base + used;
		m_used = next;
	}
	if( dest == 0 )
	{
		Rva007EB810Get()->fail(
			"false",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\util.cpp",
			0xeb );
		return 0;
	}
	strcpy( dest, text );
	return dest;
}
