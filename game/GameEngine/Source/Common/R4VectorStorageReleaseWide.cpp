// Six 67-byte bodies of the SAME shape already landed at 62 and 64 bytes in
// Q3VectorStorageRelease.cpp -- the deallocation half of a three-pointer
// vector-like container -- differing only in that the element width no longer
// fits in a signed byte.
//
// WHAT THE BYTES SHOW.  A __thiscall with no stack arguments and a bare `ret`.
// It loads the dword at offset 0, returns immediately when it is null, then
// takes the POINTER DIFFERENCE between offset 8 and offset 0, divides it by
// the element width with a magic multiply, and multiplies the count straight
// back up by that same width.  The divide-then-multiply round trip is what
// makes the width legible: the object holds `T*`, not `char*`.  The byte count
// then picks a deallocator by an UNSIGNED compare against 128 -- above it a
// one-argument cdecl call to `operator delete` at 0x00881EB0, at or below it a
// two-argument (pointer, size) cdecl call to the STLport node allocator's
// `_M_deallocate` at 0x0082E5F0, 128 being STLport's `_MAX_BYTES`.
//
// WHY 67 AND NOT 64.  Exactly one instruction changes size.  Q3's widths were
// all under 0x80, so the reconstruction multiply assembled as `imul eax,eax,imm8`
// (3 bytes); every width here is 0x80 or more, so it assembles as
// `imul eax,eax,imm32` (6 bytes).  64 + 3 = 67.  The body length is therefore
// NOT a second axis and these are not a different source shape from Q3's.
//
// ONE AXIS: the element width, which shows up three times -- in the magic
// constant, in the shift, and in the `imul`.  0x128, 0xBC, 0x8C, 0xB8, 0xB4,
// 0x1F0.  All six widths are distinct, so no two rows here even share a width.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address, and the
// element TYPE is not recovered either -- only its width.
//
// WHAT THE BYTES CANNOT DECIDE.  Whether the second member (offset 4, never
// read here) is a finish pointer, and whether the allocator is a base or a
// member of the container: nothing in this body touches either.

void Gen0082E5F0( void *p, unsigned int n );

#define R4_VECTOR_RELEASE_WIDE( NAME, WIDTH )                                 \
	struct NAME                                                               \
	{                                                                         \
		char *m_start;                                                        \
		char *m_finish;                                                       \
		char *m_endOfStorage;                                                 \
		void release();                                                       \
	};                                                                        \
	void NAME::release()                                                      \
	{                                                                         \
		if ( m_start != 0 )                                                   \
		{                                                                     \
			unsigned int n = (unsigned int)                                   \
				( ( m_endOfStorage - m_start ) / WIDTH ) * WIDTH;             \
			if ( n > 128 )                                                    \
				::operator delete( m_start );                                 \
			else                                                              \
				Gen0082E5F0( m_start, n );                                    \
		}                                                                     \
	}

R4_VECTOR_RELEASE_WIDE( Rva0013B1A0, 0x128 );
R4_VECTOR_RELEASE_WIDE( Rva0013B290, 0xBC );
R4_VECTOR_RELEASE_WIDE( Rva00194BD0, 0x8C );
R4_VECTOR_RELEASE_WIDE( Rva002BCF80, 0xB8 );
R4_VECTOR_RELEASE_WIDE( Rva00362000, 0xB4 );
R4_VECTOR_RELEASE_WIDE( Rva00606B90, 0x1F0 );
