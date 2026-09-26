// cl: /O2
// cdecl @ 0x00532020, 70 bytes. Twin of 0x005146F0 (Rva005146F0DibSplit.cpp):
// threshold split over a four-byte range with the first still-dumped callee
// at 0x005317B0 and the second the already-matched bfmeGoDID (0x00531800).
// Identity of the first callee is not recovered.

void Gen005317B0( void **first, void **last, void *arg );
void bfmeGoDID( void **begin, void **end, void *arg );

void Rva00532020( void **first, void **last, void *arg )
{
	if ( last - first > 16 )
	{
		Gen005317B0( first, first + 16, arg );
		bfmeGoDID( first + 16, last, arg );
	}
	else
		Gen005317B0( first, last, arg );
}
