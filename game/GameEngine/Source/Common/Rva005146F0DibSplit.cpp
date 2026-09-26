// cl: /O2
// cdecl @ 0x005146F0, 70 bytes. Threshold split over a four-byte range:
// `and ecx,-4; cmp ecx,0x40; lea esi,[eax+0x40]` is MSVC's rewrite of
// `last - first > 16` on void**. Over the threshold the first sixteen
// elements go to the still-dumped body at 0x005139E0 and the tail to the
// landed bfmeGoDIB; under it the whole range goes to 0x005139E0. The
// unguarded arm is three arguments (no STLport type-tag zero). Identity
// of the first callee is not recovered; the second is bfmeGoDIB.

void Gen005139E0( void **first, void **last, void *arg );
void bfmeGoDIB( void **begin, void **end, void *arg );

void Rva005146F0( void **first, void **last, void *arg )
{
	if ( last - first > 16 )
	{
		Gen005139E0( first, first + 16, arg );
		bfmeGoDIB( first + 16, last, arg );
	}
	else
		Gen005139E0( first, last, arg );
}
