// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Include/Precompiled /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Source/Common /Igame/Libraries/Source/WWVegas/WWMath
// stlport
#include <algorithm>

// The four byte-identical 55-byte bodies at 0x002DFB90, 0x00472D10, 0x00511690
// and 0x005718E0 are STLport's `_STL::__median` -- IDENTITY RECOVERED, not an
// address-derived guess.  Retail:
//
//     mov eax,[esp+4] / mov ecx,[eax] / push ebx / mov ebx,[esp+0xC]
//     mov edx,[ebx] / cmp ecx,edx / push esi / push edi / mov edi,[esp+0x18]
//     mov esi,[edi] / jge L39
//     cmp edx,esi / jl L49 / cmp ecx,esi / jge L51 / mov eax,edi / ret
//     L39: cmp ecx,esi / jl L51 / cmp edx,esi / mov eax,edi / jl L51
//     L49: mov eax,ebx / L51: ret
//
// WHY THIS IS __median AND NOT A GUESS.  Three arguments arrive by address and
// each is dereferenced exactly once; the function returns one of the three
// ADDRESSES unchanged, never a value.  The six-way branch lattice reproduces
// `inputs/vendor/stlport/stl/_algo.c` line for line: a<b ? (b<c ? b : (a<c ? c : a))
//                                                : (a<c ? a : (b<c ? c : b)).
// Every one of the six leaves lands on the arm the header names -- `mov eax,ebx`
// for b, `mov eax,edi` for c, and eax already holding a for the a arms.  The
// ledger already carries the COMPARATOR overload of the same template at
// 0x00094E30, which is the same function with the predicate argument.
//
// THE TYPE PARAMETER IS NOT RECOVERED.  Four distinct addresses cannot be four
// copies of ONE instantiation: duplicate COMDATs of a single template symbol are
// folded by the linker into a single address by definition, so four addresses
// mean four DIFFERENT symbols, hence four different `_Tp`.  All the bytes say
// about `_Tp` is that it is four bytes wide and compares with a SIGNED `jl/jge`,
// which rules out pointers and unsigned types.  The four placeholder enums below
// carry that much and no more; their names are address-derived and disclaim
// identity.  (`__median<int>` compiles to these same bytes and was checked, but
// nothing says which -- if any -- of the four it is.)

enum Rva002DFB90Key { Rva002DFB90KeyZero = 0 };
enum Rva00472D10Key { Rva00472D10KeyZero = 0 };
enum Rva00511690Key { Rva00511690KeyZero = 0 };
enum Rva005718E0Key { Rva005718E0KeyZero = 0 };

template const Rva002DFB90Key &_STL::__median<Rva002DFB90Key>(
	const Rva002DFB90Key &, const Rva002DFB90Key &, const Rva002DFB90Key & );
template const Rva00472D10Key &_STL::__median<Rva00472D10Key>(
	const Rva00472D10Key &, const Rva00472D10Key &, const Rva00472D10Key & );
template const Rva00511690Key &_STL::__median<Rva00511690Key>(
	const Rva00511690Key &, const Rva00511690Key &, const Rva00511690Key & );
template const Rva005718E0Key &_STL::__median<Rva005718E0Key>(
	const Rva005718E0Key &, const Rva005718E0Key &, const Rva005718E0Key & );
