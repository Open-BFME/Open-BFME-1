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
extern const char g_rva0111C2A0[];

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
			Rva007EB810Get()->fail( g_rva0111C2A0, "\\views\\feslbuild_main\\jabba\\fesl\\source\\util.cpp", 0x48 );
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

// 0x007FFFB0 -- length of a present C string including its NUL, 0 for null.
// Same jabba util.cpp neighbourhood as the joins below the DirtySock text
// helpers. The goto-loop spelling selects retail's EDX cursor register; the
// while form mirrors into ECX. Identity is address-derived: no caller,
// string, or vtable names it.
unsigned int Rva007FFFB0Span( const char *text )
{
	const char *cursor;
	const char *afterStart;
	if( text == 0 )
		return 0;
	cursor = text;
	afterStart = text + 1;
loop:
	{
		char c = *cursor;
		++cursor;
		if( c != 0 )
			goto loop;
	}
	return (unsigned int)( cursor - afterStart ) + 1;
}
