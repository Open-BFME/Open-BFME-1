// Seven bodies of GNU gperf's generated `in_word_set` lookup, verbatim down to
// the order of its two length tests:
//
//     if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH) {
//         int key = hash (str, len);
//         if (key <= MAX_HASH_VALUE && key >= 0) {
//             const char *s = wordlist[key].name;
//             if (*str == *s && !strcmp (str + 1, s + 1))
//                 return &wordlist[key];
//         }
//     }
//     return 0;
//
// WHY GPERF AND NOT SOME OTHER TABLE LOOKUP.  Four details together leave very
// little room.  The length window is tested with an UNSIGNED pair (ja/jb) while
// the key window is tested SIGNED (jg/jl) -- that is gperf's `unsigned int len`
// against its `register int key`, and hand-written code would not mix them.
// The first character is compared SEPARATELY before the rest of the string,
// which is gperf's `*str == *s && !strcmp (str + 1, s + 1)` and nobody else's
// idea.  The successful return is the ELEMENT ADDRESS, not the element, so the
// table is gperf's `wordlist` of structs whose first field is the key string.
// And the whole compare is the MSVC strcmp INTRINSIC expanded inline -- the
// unrolled two-bytes-per-iteration loop ending `sbb ecx,ecx / sbb ecx,-1` --
// so `!strcmp(...)` is in the source and the call was never emitted.
//
// FOUR AXES, ALL READ OFF IMMEDIATES OR RELOCATIONS: MAX_WORD_LENGTH (0x08 to
// 0x14), MIN_WORD_LENGTH (2, 3 or 4), MAX_HASH_VALUE (0x0B to 0xD3) and the
// hash function's REL32.  Every row has its own hash function, and each hash
// function sits a fixed distance below its lookup, which is what a single gperf
// run per table produces.  The wordlist base is a DIR32 operand and so costs no
// pin; its stride is 8 in every row, so every table is an array of
// {const char *, four bytes}.
//
// The 132-byte row at 0x008D48F0 is not a second shape: its MAX_HASH_VALUE is
// 0xD3, which no longer fits in a signed byte, so `cmp eax,imm8` grows to
// `cmp eax,imm32`.
//
// IDENTITY IS NOT RECOVERED.  Names are derived from addresses.  The VALUE
// field of the table entries is never read here, so its type is not recovered
// either -- only that it is four bytes wide.

#include <string.h>

struct R4Word { const char *name; int value; };

#define R4_GPERF( NAME, HASHFN, WORDLIST, MINLEN, MAXLEN, MAXHASH )           \
	int HASHFN( const char *str, unsigned int len );                          \
	extern const R4Word WORDLIST[];                                           \
	const R4Word *NAME( const char *str, unsigned int len );                  \
	const R4Word *NAME( const char *str, unsigned int len )                   \
	{                                                                         \
		if ( len <= MAXLEN && len >= MINLEN )                                 \
		{                                                                     \
			register int key = HASHFN( str, len );                            \
			if ( key <= MAXHASH && key >= 0 )                                 \
			{                                                                 \
				register const char *s = WORDLIST[ key ].name;                \
				if ( *str == *s && !strcmp( str + 1, s + 1 ) )                \
					return &WORDLIST[ key ];                                  \
			}                                                                 \
		}                                                                     \
		return 0;                                                             \
	}

R4_GPERF( Rva008A44A0, Gen008A3EE0, g008A44A0, 4, 0x0E, 0x10 )
R4_GPERF( Rva008ABF40, Gen008AB970, g008ABF40, 4, 0x11, 0x1D )
R4_GPERF( Rva008B5610, Gen008B5050, g008B5610, 4, 0x0B, 0x0B )
R4_GPERF( Rva008B8AD0, Gen008B8510, g008B8AD0, 3, 0x08, 0x1B )
R4_GPERF( Rva008D48F0, Gen008D42C0, g008D48F0, 2, 0x14, 0xD3 )
R4_GPERF( Rva008D4F80, Gen008D4980, g008D4F80, 3, 0x0B, 0x24 )
R4_GPERF( Rva008D5DC0, Gen008D57B0, g008D5DC0, 4, 0x0F, 0x4C )
