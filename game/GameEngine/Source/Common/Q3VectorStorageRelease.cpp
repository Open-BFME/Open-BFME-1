// Nineteen bodies of ONE shape: the deallocation half of a three-pointer
// vector-like container.
//
// WHAT THE BYTES SHOW.  A __thiscall with no stack arguments and a bare `ret`.
// It loads the dword at offset 0, returns immediately when it is null, then
// loads the dword at offset 8, takes the POINTER DIFFERENCE against offset 0
// (a signed divide by the element width, magic-multiply and all), and
// multiplies the element count straight back up by that same width.  That
// divide-then-multiply round trip is the whole reason the element width is
// legible: the source handed an ELEMENT COUNT to something that reconverted it
// to BYTES, so the object holds `T*` and not `char*`.
//
// The byte count then picks one of two deallocators by an UNSIGNED compare
// against 128:  n > 128 goes to a one-argument cdecl call, n <= 128 to a
// two-argument (pointer, size) cdecl call.  Both targets are already identified
// in the ledger -- `operator delete` at 0x00881EB0 and the STLport node
// allocator's `_M_deallocate` at 0x0082E5F0 -- and 128 is STLport's `_MAX_BYTES`
// small-block threshold.  So the shape is STLport `__node_alloc::deallocate`
// inlined into a `_Vector_base` teardown; that is what the bytes say, and it is
// as far as they go.
//
// ONE AXIS.  Every one of the nineteen differs only in the element width baked
// into the magic constant, the shift, and the `imul` -- 0x2C, 0x38, 0x3C, 0x54,
// 0x58, 0x5C, 0x6C, 0x70, 0x78.  The two body LENGTHS (62 and 64) are not a
// second axis: they are the same source, and the extra two bytes are the
// `add edx,ecx` fixup the magic-multiply needs for some divisors and not
// others.  Widths repeat across addresses (0x5C four times, 0x3C four, 0x54
// three, 0x2C and 0x38 twice) because retail carries genuinely duplicate
// copies; each address gets its own definition here rather than one claim
// spread over several addresses.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.  The
// element TYPE is not recovered either -- only its width -- so two rows sharing
// a width are not thereby the same container.
//
// WHAT THE BYTES CANNOT DECIDE.  Whether the second member (offset 4, never
// touched here) is a finish pointer, and whether the allocator is a base or a
// member of the container: nothing in this body reads either.

void Gen0082E5F0( void *p, unsigned int n );

#define BFME_VECTOR_RELEASE( NAME, WIDTH )                                    \
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

BFME_VECTOR_RELEASE( Rva0013F020, 0x5C );
BFME_VECTOR_RELEASE( Rva001CFE20, 0x5C );
BFME_VECTOR_RELEASE( Rva001C2990, 0x5C );
BFME_VECTOR_RELEASE( Rva001CFEB0, 0x5C );
BFME_VECTOR_RELEASE( Rva003CE090, 0x3C );
BFME_VECTOR_RELEASE( Rva0076AAC0, 0x3C );
BFME_VECTOR_RELEASE( Rva00760DC0, 0x3C );
BFME_VECTOR_RELEASE( Rva0076A7C0, 0x3C );
BFME_VECTOR_RELEASE( Rva0049B7D0, 0x70 );
BFME_VECTOR_RELEASE( Rva0069B9E0, 0x78 );
BFME_VECTOR_RELEASE( Rva006ED1A0, 0x38 );
BFME_VECTOR_RELEASE( Rva00760D50, 0x38 );
BFME_VECTOR_RELEASE( Rva00252310, 0x2C );
BFME_VECTOR_RELEASE( Rva00760EA0, 0x2C );
BFME_VECTOR_RELEASE( Rva002E70D0, 0x54 );
BFME_VECTOR_RELEASE( Rva002E4ED0, 0x54 );
BFME_VECTOR_RELEASE( Rva002E7280, 0x54 );
BFME_VECTOR_RELEASE( Rva00362090, 0x58 );
BFME_VECTOR_RELEASE( Rva00760E50, 0x6C );
