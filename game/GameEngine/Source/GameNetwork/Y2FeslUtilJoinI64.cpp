// cl: /GX- /GS
// jabba util.cpp int64-array join @ 0x00800040 (289B).
// Clears dest; sprintf each parts[i] as %I64d; ensures used+len+1 < destSize
// (else Rva007EB810 fail util.cpp:0x48); inserts sep before i>0; memcpy appends.

#include <stdio.h>
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

void Rva00800040JoinI64( const __int64 *parts, unsigned count, char *dest, unsigned destSize, char sep )
{
	unsigned i;
	unsigned used;
	unsigned len;
	char sepStr[2];
	char buf[0x24];

	dest[0] = 0;
	if( count < 1 )
		return;

	used = 0;
	sepStr[0] = sep;
	sepStr[1] = 0;
	i = 0;

	if( count <= 0 )
		return;

	for( ; i < count; i++ )
	{
		sprintf( buf, "%I64d", parts[i] );
		len = (unsigned)strlen( buf );
		if( used + len + 1 >= destSize )
		{
			Rva007EB810Get()->fail( g_bfmeMsgUVB, g_bfmeFileUVB, 0x48 );
			return;
		}
		if( i > 0 )
		{
			strcat( dest, sepStr );
			used++;
		}
		strcat( dest, buf );
		used += len;
	}
}
