// Seventeen 29-byte __thiscall const members that return a POINTER DIFFERENCE:
//
//     mov edx,[ecx] / push esi / mov esi,[ecx+DISP] / sub esi,edx
//     mov eax,MAGIC / imul esi / add edx,esi / sar edx,SHIFT
//     mov eax,edx / shr eax,31 / add eax,edx / pop esi / ret
//
// WHAT THE BYTES SHOW.  `imul` (signed), the `add edx,esi` correction for a
// negative magic, and the `shr 31 / add` round-toward-zero fixup are MSVC's
// signed division by a compile-time constant.  Solving each (MAGIC, SHIFT)
// pair for the divisor it implements gives the element size, and every one is
// a plausible object size: 28, 56, 92, 112, 120, 140, 180, 184, 188, 496.  So
// the body is `m_last - m_first` over a pointer pair, i.e. an element COUNT,
// and the divisor is sizeof(element) -- it is never written in the source.
//
// TWO AXES: the element size, and whether the second pointer sits at +4 or at
// +8.  Twelve members read +4 and four read +8.  A +8 pair with a pointer also
// at +0 is the std::vector layout {first, last, end_of_storage}: +4 is the
// size, +8 the capacity.  That reading is offered, not asserted -- the bytes
// only say "a pointer at 0 and a pointer at DISP".
//
// THESE BODIES CARRY NO RELOCATIONS AT ALL, so all twenty-nine bytes of each
// are compared concretely; nothing here is masked.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived and the element types
// are opaque byte blocks of the recovered size.

#define WIDE_ELEMENT( SIZE )                                              	class WideElem##SIZE                                                  	{                                                                     		char m_bytes[ SIZE ];                                             	};

#define WIDE_COUNT_2( NAME, SIZE )                                        	class Rva##NAME                                                       	{                                                                     	public:                                                               		int count() const;                                                		WideElem##SIZE *m_first;                                          		WideElem##SIZE *m_last;                                           	};                                                                    	int Rva##NAME::count() const { return m_last - m_first; }

#define WIDE_COUNT_3( NAME, SIZE )                                        	class Rva##NAME                                                       	{                                                                     	public:                                                               		int count() const;                                                		WideElem##SIZE *m_first;                                          		WideElem##SIZE *m_mid;                                            		WideElem##SIZE *m_last;                                           	};                                                                    	int Rva##NAME::count() const { return m_last - m_first; }

WIDE_ELEMENT( 28 )
WIDE_ELEMENT( 56 )
WIDE_ELEMENT( 92 )
WIDE_ELEMENT( 112 )
WIDE_ELEMENT( 120 )
WIDE_ELEMENT( 140 )
WIDE_ELEMENT( 180 )
WIDE_ELEMENT( 184 )
WIDE_ELEMENT( 188 )
WIDE_ELEMENT( 496 )
WIDE_ELEMENT( 296 )

WIDE_COUNT_2( 000B93F0, 112 )
WIDE_COUNT_2( 00133150, 92 )
WIDE_COUNT_3( 00133300, 92 )
WIDE_COUNT_2( 0013A320, 296 )
WIDE_COUNT_2( 0013A360, 188 )
WIDE_COUNT_2( 00191970, 140 )
WIDE_COUNT_2( 001C01C0, 92 )
WIDE_COUNT_3( 00233890, 28 )
WIDE_COUNT_2( 00360A70, 180 )
WIDE_COUNT_3( 00360D20, 180 )
WIDE_COUNT_2( 003A1320, 184 )
WIDE_COUNT_3( 004228F0, 28 )
WIDE_COUNT_2( 00606920, 496 )
WIDE_COUNT_2( 00697410, 120 )
WIDE_COUNT_2( 006EAC40, 56 )
WIDE_COUNT_2( 0075CFA0, 56 )
WIDE_COUNT_3( 0075E550, 56 )
