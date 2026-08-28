// cl: /DNDEBUG /DWIN32 /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: the body U4ElementScanLoops.cpp calls once per element is not a
// filter object at all.  It is Zero Hour's BitFlags::testForAll, and the flag
// set is 304 bits wide.
//
//     BitFlags tmp = *this;
//     tmp.m_bits.flip();
//     tmp.m_bits &= that.m_bits;
//     return !tmp.m_bits.any();
//
// THE WIDTH IS NOT GUESSED, IT IS TWO INDEPENDENT READINGS THAT AGREE.  The
// `rep movsd` at the top copies exactly ten dwords, so the set is 289..320
// bits.  Near the end retail writes `mov word ptr [esp+0x36], 0` -- a plain
// 16-bit store clearing the TOP HALF of the tenth word.  That is STLport's
// _M_do_sanitize after flip(), and a clean 16-bit store (rather than an AND
// with a mask) can only mean the surviving bits end exactly at the halfway
// point: 9*32 + 16 = 304.
//
// The flip and the intersection are FUSED: retail never materialises the
// flipped copy, it emits `not` on each word of the copy and ANDs straight
// against the argument's matching word.  Writing the two statements separately
// is what produces that; hand-fusing them into one expression does not, and
// neither does `testForNone`, which is the same body without the flip.
//
// The double negative at the end is source, not noise.  `any()` answers a Bool
// and `!` of it compiles to `xor ecx,ecx / test al,al / sete cl / mov al,cl`;
// returning the loop's own flag inverted by hand gives a single `xor al,1`.
//
// The receiver is `const` and the argument a const reference, which is what
// makes the copy the FIRST thing in the body -- the source may not flip in
// place.
//
// WHAT THIS SETTLES ABOUT THE U4 SLICE.  The 0x1F0-wide element that
// U4ElementScanLoops.cpp walks begins with a BitFlags<304>: the scan hands the
// element pointer straight to this body as its `const BitFlags &`.  The
// element's `char m_pad[0x1DC]` therefore opens with 0x28 bytes of flag words.
// U4ElementScanLoops.cpp is left as it stands -- it byte-matches, and its
// address-derived pin is what keeps its call site resolving -- but the slice's
// "filter" is a flag mask and its "accepts" is a subset test.

#include <bitset>

typedef bool Bool;

template <size_t NUMBITS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	Bool testForAll( const BitFlags &that ) const;

private:
	_STL::bitset<NUMBITS> m_bits;
};

// ?testForAll@?$BitFlags@$0BDA@@@QBE_NABV1@@Z		retail 0x00606BF0
template <size_t NUMBITS>
Bool BitFlags<NUMBITS>::testForAll( const BitFlags &that ) const
{
	BitFlags tmp = *this;

	tmp.m_bits.flip();
	tmp.m_bits &= that.m_bits;

	return !tmp.m_bits.any();
}

template class BitFlags<304>;
