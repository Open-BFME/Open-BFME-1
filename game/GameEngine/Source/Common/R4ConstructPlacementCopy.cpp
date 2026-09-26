// stlport
//
// Six bodies of STLport's `_Construct(_T1 *p, const _T2 &val)` -- the
// placement-new copy-construct helper from stl/_construct.h -- instantiated
// over six two-part types.
//
// WHAT THE BYTES SHOW.  A __cdecl function with TWO stack arguments and a plain
// `ret` (the caller pops), wrapped in a full fs:[0] exception frame whose state
// is driven to 0 and never back to -1.  It stores arg0 into the frame's
// object slot, tests it for null, and only then constructs.  A NULL TEST ON A
// POINTER THE CALLER SUPPLIED IS THE TELL: it is the test MSVC always emits on
// the result of `operator new`, surviving here because the `new` is a PLACEMENT
// new whose result is the argument.  That, plus the cdecl (pointer, const
// reference) signature and the EH state with no visible cleanup, is what
// identifies this as _Construct rather than as a hand-written copy helper; the
// REAL STLport HEADER is what produced these bytes, and a replica was not
// needed nor trusted.
//
// The constructor is INLINED into the helper and has exactly two steps: a
// __thiscall call with ecx = p and the source pushed -- an out-of-line copy
// constructor for whatever sits at offset 0 -- followed by ONE scalar copy of
// a field just past it.  That is the implicit copy constructor of a two-field
// aggregate.
//
// TWO AXES.  (1) the offset-0 subobject's copy constructor, of which there are
// two: 0x00193760 (already in the ledger as an `_STL::pair` copy constructor,
// 8 bytes wide, so the scalar lands at +8) and 0x00887B60 (already in the
// ledger as `StringBase<char>` / AsciiString, 4 bytes wide, so the scalar lands
// at +4).  (2) the WIDTH of the trailing scalar: dword, byte or word, read
// straight off the mov.  Every (subobject, width) pair used here is distinct
// except dword-at-8, which occurs three times; those three rows push THREE
// DIFFERENT EH funcinfo addresses, so retail has three separate instantiations
// and they get three separate types here rather than one claim spread over
// three addresses.
//
// THE OFFSET-0 SUBOBJECT IS SPELLED AS A MEMBER, NOT A BASE.  `mov ecx,esi`
// is what both produce -- a base conversion at offset 0 is free, and so is a
// member at offset 0 -- so the bytes cannot separate them.  A member asserts
// less, and the known identity of both callees (a pair, a string) makes
// containment the reading that posits less.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the
// scalar's TYPE is not recovered either, only its width.

#include <memory>

#define R4_CTOR_CALLEE( T, SZ )                                               \
	struct T                                                                  \
	{                                                                         \
		char m_body[ SZ ];                                                    \
		T();                                                                  \
		T( const T & );                                                       \
		~T();                                                                 \
	};

#define R4_CONSTRUCT_PAIR( NAME, HEAD, SCALAR )                               \
	struct NAME                                                               \
	{                                                                         \
		HEAD m_head;                                                          \
		SCALAR m_tail;                                                        \
	};                                                                        \
	template void _STL::_Construct( NAME *, const NAME & );

R4_CTOR_CALLEE( Gen00193760, 8 )
R4_CTOR_CALLEE( Gen00887B60, 4 )

R4_CONSTRUCT_PAIR( Rva001954D0, Gen00193760, int )
R4_CONSTRUCT_PAIR( Rva0033BDE0, Gen00193760, char )
R4_CONSTRUCT_PAIR( Rva0033BE50, Gen00193760, int )
R4_CONSTRUCT_PAIR( Rva0033BEC0, Gen00193760, int )
R4_CONSTRUCT_PAIR( Rva003884B0, Gen00887B60, short )
R4_CONSTRUCT_PAIR( Rva00430840, Gen00887B60, short )
