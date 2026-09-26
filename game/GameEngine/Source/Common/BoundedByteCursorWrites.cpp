// The three byte-identical 31-byte bodies at 0x0068D6A0, 0x0068D6D0 and
// 0x0068D700 -- three consecutive slots at a flat 0x30 stride.
//
//     mov ecx,[esp+0xC] / test ecx,ecx / mov eax,[esp+4] / je store
//     cmp eax,ecx / ja out / lea edx,[eax+1] / cmp edx,ecx / ja out
//     store: mov cl,byte ptr [esp+8] / mov [eax],cl / inc eax
//     out: ret
//
// WHAT THE BYTES SHOW.  Three dword arguments, no `this`, no stack cleanup:
// __cdecl.  The first and third are compared with UNSIGNED branches (`ja`), so
// both are pointers; the second is read one byte wide out of its stack slot, so
// its declared type is a byte.  eax carries the first argument in and out, and
// is incremented by exactly one on the path that stores -- so the function
// returns the advanced cursor, and returns it UNCHANGED when it declines to
// store.  That is a bounds-checked byte writer over a moving cursor.
//
// The guard reads exactly as written below: a null limit disables checking
// entirely (`test ecx,ecx / je store` jumps straight past both comparisons), and
// otherwise both the cursor and the cursor plus one must be within the limit.
// Testing `cursor + 1` separately rather than folding it into one comparison is
// what the source says, not an optimisation -- MSVC would have folded a single
// combined test.
//
// The three-consecutive-slots layout at one stride is a small family of writers
// emitted together, of which these three happen to write one byte; the
// neighbouring BoundedByteCursorReads.cpp holds the reading counterpart at
// 0x0068D990, whose guard is the same instruction sequence with the store
// reversed.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Three distinct addresses side by side in one
// table; nothing here defeats inlining, so there is no per-translation-unit
// COMDAT reading to justify asserting they are one function.
//
// IDENTITY IS NOT RECOVERED.  Nothing in the image names the writer or the
// stream it writes into, so the names are address-derived.

#define BFME_BOUNDED_BYTE_WRITE( NAME )                                       \
	char *NAME( char *cursor, char value, char *limit )                       \
	{                                                                         \
		if ( limit != 0 && ( cursor > limit || cursor + 1 > limit ) )         \
		{                                                                     \
			return cursor;                                                    \
		}                                                                     \
                                                                              \
		*cursor = value;                                                      \
                                                                              \
		return cursor + 1;                                                    \
	}

BFME_BOUNDED_BYTE_WRITE( rva68d6a0 )
BFME_BOUNDED_BYTE_WRITE( rva68d6d0 )
BFME_BOUNDED_BYTE_WRITE( rva68d700 )
