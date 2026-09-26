// The twenty-one byte-identical 34-byte range destroyers spread over
// 0x003A7110-0x003B3FC0 and 0x00619690-0x00619F30.  Three families, identical
// except for one immediate byte -- the element stride.  Retail (stride 0x20):
//
//     push esi / mov esi,[esp+8] / push edi / mov edi,[esp+0x10]
//     cmp esi,edi / je done / npad 2
//     loop: mov eax,[esi] / push 0 / mov ecx,esi / call dword ptr [eax]
//           add esi,0x20 / cmp esi,edi / jne loop
//     done: pop edi / pop esi / ret
//
// WHAT THE BYTES SHOW.  No `this` in ecx on entry and a plain `ret`: __cdecl,
// two pointer arguments.  The first is walked forward by a constant stride
// until it equals the second, so the pair is a half-open [first,last) range
// over an array of objects, not over pointers -- the loop steps by the object
// size, and nothing in the body dereferences an element for anything except
// its vftable.
//
// `mov eax,[esi] / push 0 / mov ecx,esi / call dword ptr [eax]` is the exact
// shape MSVC emits for an explicit `p->~T()` on a type with a virtual
// destructor: vftable slot 0 holds the scalar deleting destructor, and the
// pushed 0 is its "do not free" flag.  So this is destroy-a-range, and the
// element type is polymorphic.
//
// THE ONLY AXIS IS THE STRIDE.  0x20, 0x24 and 0x14 -- 32, 36 and 20 bytes.
// Every other byte of all twenty-one bodies is the same, including the two-byte
// `mov edi,edi` that pads the loop head to a 16-byte boundary; that padding is
// the compiler's own loop alignment and needs nothing from the source.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Four different strides cannot be one
// COMDAT, and within a stride the copies are separate instantiations over
// different element types that merely compile identically.  They are written
// here as distinct bodies for that reason.
//
// IDENTITY IS NOT RECOVERED.  Nothing in the image names either the element
// types or the helper, so the names are address-derived and disclaim identity.

#define BFME_RANGE_DESTROYER( NAME, PADWORDS )                                \
	class NAME##Element                                                       \
	{                                                                         \
	public:                                                                   \
		virtual ~NAME##Element();                                             \
		int m_pad[ PADWORDS ];                                                \
	};                                                                        \
	void NAME( NAME##Element *first, NAME##Element *last );                   \
	void NAME( NAME##Element *first, NAME##Element *last )                    \
	{                                                                         \
		for ( ; first != last; ++first )                                      \
		{                                                                     \
			first->~NAME##Element();                                          \
		}                                                                     \
	}

// Stride 0x20 -- vftable pointer plus seven dwords.
BFME_RANGE_DESTROYER( Rva003A7110Destroy, 7 )
BFME_RANGE_DESTROYER( Rva003A71D0Destroy, 7 )
BFME_RANGE_DESTROYER( Rva003A8420Destroy, 7 )
BFME_RANGE_DESTROYER( Rva003A8530Destroy, 7 )
BFME_RANGE_DESTROYER( Rva003A8EE0Destroy, 7 )
BFME_RANGE_DESTROYER( Rva003A8FE0Destroy, 7 )
BFME_RANGE_DESTROYER( Rva003B3220Destroy, 7 )
BFME_RANGE_DESTROYER( Rva003B3BD0Destroy, 7 )
BFME_RANGE_DESTROYER( Rva003B3FC0Destroy, 7 )

// Stride 0x24 -- vftable pointer plus eight dwords.
BFME_RANGE_DESTROYER( Rva003A7170Destroy, 8 )
BFME_RANGE_DESTROYER( Rva003A8480Destroy, 8 )
BFME_RANGE_DESTROYER( Rva003A8F40Destroy, 8 )
BFME_RANGE_DESTROYER( Rva00619690Destroy, 8 )
BFME_RANGE_DESTROYER( Rva00619B50Destroy, 8 )
BFME_RANGE_DESTROYER( Rva00619F30Destroy, 8 )

// Stride 0x14 -- vftable pointer plus four dwords.
BFME_RANGE_DESTROYER( Rva003A71A0Destroy, 4 )
BFME_RANGE_DESTROYER( Rva003A7230Destroy, 4 )
BFME_RANGE_DESTROYER( Rva003A84B0Destroy, 4 )
BFME_RANGE_DESTROYER( Rva003A8590Destroy, 4 )
BFME_RANGE_DESTROYER( Rva003A8F70Destroy, 4 )
BFME_RANGE_DESTROYER( Rva003A9040Destroy, 4 )

// Stride 0x10 -- vftable pointer plus three dwords.
BFME_RANGE_DESTROYER( Rva003A7260Destroy, 3 )
BFME_RANGE_DESTROYER( Rva003A7290Destroy, 3 )
BFME_RANGE_DESTROYER( Rva003A8610Destroy, 3 )
BFME_RANGE_DESTROYER( Rva003A8640Destroy, 3 )
BFME_RANGE_DESTROYER( Rva003A90B0Destroy, 3 )
BFME_RANGE_DESTROYER( Rva003A90E0Destroy, 3 )
