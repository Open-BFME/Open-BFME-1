// ?rva68d9c0@@YAPADPAD00@Z
// partial score=0.95 date=2026-09-04
// ?rva68d9c0@@YAPADPAD00@Z
// partial score=0.95 date=2026-09-02
// The three byte-identical 33-byte bodies at 0x0068D990, 0x0068D9C0 and
// 0x0068D9F0 -- the reading counterpart of BoundedByteCursorWrites.cpp.
//
// Same three-pointer cdecl shape and the same unsigned limit guard; the store
// is reversed so one byte is copied out of the cursor instead of into it.

#define BFME_BOUNDED_BYTE_READ( NAME )                                        \
	char *NAME( char *cursor, char *out, char *limit )                        \
	{                                                                         \
		if ( limit != 0 && ( cursor > limit || cursor + 1 > limit ) )         \
		{                                                                     \
			return cursor;                                                    \
		}                                                                     \
                                                                              \
		*out = *cursor;                                                       \
                                                                              \
		return cursor + 1;                                                    \
	}

BFME_BOUNDED_BYTE_READ( rva68d990 )
BFME_BOUNDED_BYTE_READ( rva68d9c0 )
BFME_BOUNDED_BYTE_READ( rva68d9f0 )
