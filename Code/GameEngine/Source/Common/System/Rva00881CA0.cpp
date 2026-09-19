// cl: /DNDEBUG /MD /EHs-c-

extern "C" void * ( * __cdecl __gameMemAllocPtr )( unsigned int size, int flags );

extern "C" void * __cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)

void * d_00881ca0( unsigned int count, unsigned int size )
{
	unsigned int total = count * size;
	void *ptr = __gameMemAllocPtr( total, 0 );
	if ( ptr )
	{
		memset( ptr, 0, total );
	}
	return ptr;
}

void * d_00881ce0( unsigned int count, unsigned int size )
{
	unsigned int total = count * size;
	void *ptr = __gameMemAllocPtr( total, 0 );
	if ( ptr )
	{
		memset( ptr, 0, total );
	}
	return ptr;
}
