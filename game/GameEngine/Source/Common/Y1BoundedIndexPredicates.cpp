// One 23-byte __cdecl predicate over a single int argument, in the shape the
// tree's BoundedIndexPredicates.cpp already documents:
//
//     0x003D5170
//         mov eax,[esp+4] / cmp eax,0x11 / jl false / cmp eax,0x40 / jg false
//         mov eax,1 / ret / false: xor eax,eax / ret
//
// WHAT THE BYTES SHOW.  No `this`, no stack cleanup, one dword read: __cdecl
// taking one int.  The literal 1 and the zeroed eax are MSVC 7.1's `bool`, and
// the signed branches (`jl`/`jg`) say the argument is signed.  The tested
// interval is the closed range [17,64].
//
// It sits in its own translation unit rather than joining
// BoundedIndexPredicates.cpp because it is a THIRD family: that file's two
// families test [2,15] and its near-complement, and this one shares neither
// bound.  Nothing in the image pairs 0x003D5170 with them beyond the shape.
//
// IDENTITY IS NOT RECOVERED.  No caller names it and no string describes what
// the range means, so the name is address-derived.

bool rva3d5170( int value )
{
	return value >= 17 && value <= 64;
}
