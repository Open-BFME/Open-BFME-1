// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Open-BFME5: three near-twins of Rva008A9710 (twin 0x008A9710,
// Code/Libraries/Source/EA/Apt/AptStringMethodLookup.cpp). Same two-level
// gperf shape: a byte lookup table indexed by hash key either yields a
// direct wordlist index or (when negative, below -OVERN) an offset into an
// overflow run appended after the first OVERN wordlist entries, linearly
// scanned. Only the length window, MAXHASH, OVERN and the hash callee vary
// per table; the wordlist/lookup array addresses are DIR32 operands and
// cost no pin (masked like any other data relocation).

#include <string.h>

struct R4Word
{
	const char *name;
	int value;
};

#define R4_GPERF_OVERFLOW( NAME, HASHFN, WORDLIST, LOOKUP, MINLEN, MAXLEN, MAXHASH, OVERN ) \
	int HASHFN( const unsigned char *text, int length );                      \
	extern const R4Word WORDLIST[];                                           \
	extern const signed char LOOKUP[];                                        \
	const R4Word *NAME( const char *str, unsigned int len )                   \
	{                                                                         \
		if ( len <= MAXLEN && len >= MINLEN )                                 \
		{                                                                     \
			register int key = HASHFN( (const unsigned char *)str, (int)len ); \
			if ( key <= MAXHASH && key >= 0 )                                 \
			{                                                                 \
				register int index = LOOKUP[ key ];                          \
				if ( index >= 0 )                                             \
				{                                                             \
					register const char *s = WORDLIST[ index ].name;          \
					if ( *str == *s && !strcmp( str + 1, s + 1 ) )            \
						return &WORDLIST[ index ];                            \
				}                                                             \
				else if ( index < -OVERN )                                    \
				{                                                             \
					register int offset = -1 - OVERN - index;                 \
					register const R4Word *wordptr = ( WORDLIST + OVERN ) + LOOKUP[ offset ]; \
					register const R4Word *wordendptr = wordptr - LOOKUP[ offset + 1 ]; \
					while ( wordptr < wordendptr )                            \
					{                                                         \
						register const char *s = wordptr->name;               \
						if ( *str == *s && !strcmp( str + 1, s + 1 ) )        \
							return wordptr;                                   \
						wordptr++;                                            \
					}                                                         \
				}                                                             \
			}                                                                 \
		}                                                                     \
		return 0;                                                             \
	}

// retail 0x00897FD0: length [3,8], MAXHASH 0x25, overflow at 37
R4_GPERF_OVERFLOW( Rva00897FD0, bfmeSkipVF, g00897FD0words, g00897FD0lookup, 3, 8, 0x25, 37 )

// retail 0x008A3DC0: length [3,6], MAXHASH 0x31, overflow at 18
R4_GPERF_OVERFLOW( Rva008A3DC0, bfmeSkipVC, g008A3DC0words, g008A3DC0lookup, 3, 6, 0x31, 18 )

// retail 0x008B60B0: length [3,0x12], MAXHASH 0x39, overflow at 37
R4_GPERF_OVERFLOW( Rva008B60B0, bfmeSkipVH, g008B60B0words, g008B60B0lookup, 3, 0x12, 0x39, 37 )
