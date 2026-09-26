// Six __cdecl free functions that each pull the last element of a range out,
// move the first element into its place, and hand the pulled value to a
// six-argument helper.
//
//     mov  ecx,[esp+4]          ; first
//     mov  eax,[esp+8]          ; last
//     mov  edx,[eax-8]          ; value  = *(last-1), both dwords, BEFORE
//     mov  esi,[eax-4]          ;         the overwrite
//     mov  edi,[ecx]            ; *(last-1) = *first
//     mov  [eax-8],edi
//     mov  edi,[ecx+4]
//     mov  [eax-4],edi
//     mov  edi,[esp+0x18]       ; or [esp+0x14] -- see below
//     push edi / push esi / push edx / push eax / push 0 / push ecx
//     call <ADJUST> / add esp,0x18
//
// WHAT THE BYTES SHOW.
//
//  * THE ELEMENT IS EIGHT BYTES.  Two dwords are copied per element, the tail
//    element is addressed at -8, and the length is `((last - first) - 8) >> 3`.
//    Eight is the ONLY thing the bytes say about the element type.
//  * THE VALUE IS PASSED BY VALUE.  It occupies two of the six pushed dwords,
//    low dword at the lower address -- an 8-byte POD argument, not a pointer.
//  * SIX DWORDS PUSHED AND `add esp,0x18` AT THE CALLER makes ADJUST __cdecl
//    with the argument list (first, 0, len, value, comparator).  Counting the
//    pushes against the pop is the whole convention argument; the callee is
//    never read.
//  * THE COMPARATOR SLOT IS THE SECOND AXIS.  Three of these read it from
//    [esp+0x18] and three from [esp+0x14].  With two pushes live that is the
//    caller's fourth versus third argument, so the six split cleanly into a
//    four-parameter form (whose third parameter is never touched) and a
//    three-parameter form.  Nothing else in the six bodies differs.
//  * THE FIRST AXIS is the ADJUST target: 0x00260D80, 0x004379B0, 0x005757E0,
//    each reached through a low-RVA ILT thunk.  Each target is used by exactly
//    one four-parameter and one three-parameter body, so the 3x2 reading is
//    complete and no combination is doubled.
//
// IDENTITY IS NOT RECOVERED.  This is the shape of a heap "pop" helper -- pull
// the root out, move the tail into the root, sift the pulled value back down --
// but the bytes do not name it, and the unused third parameter of the longer
// form is exactly the kind of type-carrying dummy such helpers use.  The
// element struct is named for its SIZE, the comparator is spelled as a
// single-dword callable because one dword is what gets pushed, and the three
// helpers are declared-only functions named for their addresses so the pins are
// address-derived and additive.  One element type is used for all three groups:
// the bytes cannot distinguish three 8-byte element types from one.

struct Gen8ByteElement
{
	int m_00;
	int m_04;
};

typedef bool ( *Gen8ByteElementLess )( const Gen8ByteElement &, const Gen8ByteElement & );

void GenAdjust00260D80( Gen8ByteElement *first, int holeIndex, int len,
						Gen8ByteElement value, Gen8ByteElementLess comp );
void GenAdjust004379B0( Gen8ByteElement *first, int holeIndex, int len,
						Gen8ByteElement value, Gen8ByteElementLess comp );
void GenAdjust005757E0( Gen8ByteElement *first, int holeIndex, int len,
						Gen8ByteElement value, Gen8ByteElementLess comp );

// The third parameter is declared and never used -- that is what the bytes say.
#define BFME_HEAP_POP_4( NAME, ADJUST )                                   \
	void NAME( Gen8ByteElement *first, Gen8ByteElement *last,             \
			   Gen8ByteElement *, Gen8ByteElementLess comp )              \
	{                                                                     \
		Gen8ByteElement value = *( last - 1 );                            \
		*( last - 1 ) = *first;                                           \
		ADJUST( first, 0, ( last - 1 ) - first, value, comp );            \
	}

#define BFME_HEAP_POP_3( NAME, ADJUST )                                   \
	void NAME( Gen8ByteElement *first, Gen8ByteElement *last,             \
			   Gen8ByteElementLess comp )                                 \
	{                                                                     \
		Gen8ByteElement value = *( last - 1 );                            \
		*( last - 1 ) = *first;                                           \
		ADJUST( first, 0, ( last - 1 ) - first, value, comp );            \
	}

BFME_HEAP_POP_4( Rva00261210, GenAdjust00260D80 )
BFME_HEAP_POP_3( Rva00261390, GenAdjust00260D80 )
BFME_HEAP_POP_4( Rva00437E00, GenAdjust004379B0 )
BFME_HEAP_POP_3( Rva00437F10, GenAdjust004379B0 )
BFME_HEAP_POP_4( Rva00575B20, GenAdjust005757E0 )
BFME_HEAP_POP_3( Rva00577090, GenAdjust005757E0 )
