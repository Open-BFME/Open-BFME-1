// cl: /GX-
// jabba util.cpp string-array join @ 0x00800170 (261B).
// Clears dest; for each parts[i] ensures used+len+1 < destSize (else
// Rva007EB810 fail util.cpp:0x67); inserts sep before i>0; strcpy appends.

#include <string.h>

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail( const char *expr, const char *file, int line );
};

extern Rva007EB810Diag *Rva007EB810Get();
extern char g_bfmeMsgUVB[];
extern char g_bfmeFileUVB[];

void Rva00800170Join( const char **parts, unsigned count, char *dest, unsigned destSize, char sep )
{
	unsigned i;
	unsigned used;
	unsigned len;
	char sepStr[2];

	dest[0] = 0;
	if( count < 1 )
		return;

	used = 0;
	sepStr[0] = sep;
	sepStr[1] = 0;

	if( count <= 0 )
		return;

	for( i = 0; i < count; i++ )
	{
		len = (unsigned)strlen( parts[i] );
		if( used + len + 1 >= destSize )
		{
			Rva007EB810Get()->fail( g_bfmeMsgUVB, g_bfmeFileUVB, 0x67 );
			return;
		}
		if( i > 0 )
		{
			strcat( dest, sepStr );
			used++;
		}
		strcat( dest, parts[i] );
		used += len;
	}
}
