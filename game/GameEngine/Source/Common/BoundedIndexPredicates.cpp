// Nine 23-byte __cdecl predicates over one int argument, in two families that
// differ only in the bound they test.
//
//     0x001B4020 0x0026E660 0x003D5150 0x003F75F0 0x00402240   (five copies)
//         mov eax,[esp+4] / cmp eax,2 / jl false / cmp eax,0xF / jg false
//         mov eax,1 / ret / false: xor eax,eax / ret
//
//     0x003D5120 0x003FB930 0x003FCF70 0x00402220             (four copies)
//         mov eax,[esp+4] / cmp eax,1 / je true / cmp eax,0x10 / jge true
//         xor eax,eax / ret / true: mov eax,1 / ret
//
// WHAT THE BYTES SHOW.  No `this`, no stack cleanup, one dword read: __cdecl
// taking a single int.  Both return a literal 1 or a zeroed eax and nothing
// wider, which is MSVC 7.1's `bool` -- an `int`-returning predicate would
// propagate a comparison result rather than materialise 1, and the signed
// branches (`jl`/`jg`/`jge`, not `jb`/`ja`/`jae`) say the argument is signed.
//
// The first tests the closed interval [2,15]; the second is its near-complement
// with a hole, `x == 1 || x >= 16`.  Together they read as the two halves of an
// enumeration or index classification -- one asking "is this one of the fourteen
// in the middle", the other "is this the distinguished first value or one of the
// ones past the end".  The bytes fix the constants exactly and say nothing about
// what is being classified.
//
// The pairing is what makes them one piece of work rather than two coincidences:
// 0x003D5120 and 0x003D5150 are adjacent, and so are 0x00402220 and 0x00402240.
// Two translation units emit BOTH predicates, back to back, in the same order.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  The adjacency above is consistent with one
// header's pair of helpers landing out of line once per translation unit, which
// would make each family a single COMDAT -- but it is equally consistent with
// several modules each carrying their own copy of a small range check, and
// nothing in the image decides between the two.  An alias row would assert the
// first reading as fact; separate bodies claim only the bytes at each address,
// which is all that is established.
//
// IDENTITY IS NOT RECOVERED.  No caller names either predicate and no string in
// the image describes what the range means, so both names are address-derived.

#define BFME_BOUNDED_INDEX_MIDDLE( NAME )                                     \
	bool NAME( int value )                                                    \
	{                                                                         \
		return value >= 2 && value <= 15;                                     \
	}

#define BFME_BOUNDED_INDEX_OUTSIDE( NAME )                                    \
	bool NAME( int value )                                                    \
	{                                                                         \
		return value == 1 || value >= 16;                                     \
	}

BFME_BOUNDED_INDEX_MIDDLE( rva1b4020 )
BFME_BOUNDED_INDEX_MIDDLE( rva26e660 )
BFME_BOUNDED_INDEX_MIDDLE( rva3d5150 )
BFME_BOUNDED_INDEX_MIDDLE( rva3f75f0 )
BFME_BOUNDED_INDEX_MIDDLE( rva402240 )

BFME_BOUNDED_INDEX_OUTSIDE( rva3d5120 )
BFME_BOUNDED_INDEX_OUTSIDE( rva3fb930 )
BFME_BOUNDED_INDEX_OUTSIDE( rva3fcf70 )
BFME_BOUNDED_INDEX_OUTSIDE( rva402220 )
