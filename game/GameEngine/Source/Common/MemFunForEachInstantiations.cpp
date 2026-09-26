// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Include/Precompiled /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Source/Common /Igame/Libraries/Source/WWVegas/WWMath
// stlport
#include <algorithm>
#include <functional>

// Three ADJACENT PAIRS -- (0x0048EB20, 0x0048EB30), (0x0048EB80, 0x0048EB90)
// and (0x004B00D0, 0x004B00E0) -- that are STLport's `_STL::mem_fun` and
// `_STL::for_each`.  IDENTITY RECOVERED for both templates.
//
//   mem_fun (11 bytes)
//     mov eax,[esp+4] / mov ecx,[esp+8] / mov [eax],ecx / ret
//
//   for_each (53 bytes)
//     push ebx / mov ebx,[esp+0x10] / push esi / mov esi,[esp+0x10]
//     cmp esi,ebx / je empty / push edi / mov edi,[esp+0x1C]
//     loop: mov ecx,[esi] / call edi / add esi,4 / cmp esi,ebx / jne loop
//     mov eax,[esp+0x10] / mov [eax],edi / pop edi / pop esi / pop ebx / ret
//     empty: mov eax,[esp+0xC] / mov ecx,[esp+0x18] / pop esi / mov [eax],ecx
//            pop ebx / ret
//
// WHAT THE BYTES SHOW.  Both are __cdecl and both take a FIRST argument they
// only ever store through and then return in eax: the hidden return pointer of a
// class returned by value.  What is stored into it is, in for_each's case, the
// LAST argument unchanged on both the walked and the empty path -- and returning
// the functor untouched is for_each's entire distinguishing behaviour.
//
// The functor is FOUR BYTES and is invoked as `mov ecx,[esi] / call edi`.  That
// is not a free function pointer -- a free call would push its argument -- it is
// a POINTER TO MEMBER FUNCTION applied to the element: `this` in ecx, the
// pointer itself called directly, which is the layout of a pmf on a class with
// single non-virtual inheritance.  A four-byte functor holding a pmf and
// applying it to `*it` is exactly `mem_fun_t`, and the range is walked FOUR
// bytes at a time over values that are themselves dereferenced into ecx, so the
// elements are `_Tp *` and the range is `_Tp **`.
//
// The 11-byte partner does nothing but copy that same pmf into a returned
// object, which is `mem_fun` itself: `return mem_fun_t<_Ret,_Tp>(__f);`.  It
// sits immediately before its for_each in all three pairs.
//
// NOT RECOVERED: the element class, and the member function's return type -- the
// result of `call edi` is discarded, so `void` and `int` compile to these exact
// bytes alike.  `void` is written below.  The element names are address-derived
// and disclaim identity.
//
// THE APPLIED FUNCTOR ALSO SURVIVES OUT OF LINE.  `mem_fun_t::operator()` is
// inlined into for_each as the bare `call edi`, but MSVC also emits it as its
// own COMDAT, and those three copies are at 0x0048E910, 0x0048E930 and
// 0x004AFD40 -- the same two drawers, one per element type:
//
//     mov eax,ecx / mov ecx,[esp+4] / call dword ptr [eax] / ret 4
//
// eleven bytes that occur EXACTLY three times in the whole image, which is what
// makes them attributable at all.  Which of the two 0x0048E9xx copies belongs to
// which element type is not determinable and does not matter: the element types
// are address-derived placeholders with no recovered identity, so the pairing
// asserts nothing.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Duplicate COMDATs of one template symbol
// fold to a single address, so three addresses per shape mean three different
// `_Tp`.

class Rva0048EB20Element { public: void act(); };
class Rva0048EB80Element { public: void act(); };
class Rva004B00D0Element { public: void act(); };

#define BFME_MEM_FUN_FOR_EACH( ELEM )                                         \
	template _STL::mem_fun_t<void, ELEM> _STL::mem_fun<void, ELEM>(           \
		void ( ELEM::* )() );                                                 \
	template _STL::mem_fun_t<void, ELEM> _STL::for_each<                      \
		ELEM **, _STL::mem_fun_t<void, ELEM> >(                               \
		ELEM **, ELEM **, _STL::mem_fun_t<void, ELEM> );

BFME_MEM_FUN_FOR_EACH( Rva0048EB20Element )
BFME_MEM_FUN_FOR_EACH( Rva0048EB80Element )
BFME_MEM_FUN_FOR_EACH( Rva004B00D0Element )
