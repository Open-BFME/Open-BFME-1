// Two 25-byte constructors at 0x005E9430 and 0x005E9670:
//
//     mov eax,ecx                    ; a constructor returns this
//     mov [eax+4],<SECOND BASE VFTABLE>
//     mov [eax],  <DERIVED VFTABLE FOR BASE 1>
//     mov [eax+4],<DERIVED VFTABLE FOR BASE 2>
//     ret 4
//
// This is the shape Q2MultipleBaseVtableSetters.cpp documents as its shape A,
// with one difference that matters: `ret 4`, not a bare `ret`.  The
// constructor takes ONE dword parameter, and nothing in the body reads it --
// it is neither stored into the object nor forwarded to anything, because
// there is nothing to forward it to.  Both base constructors are inlined (no
// call anywhere) and both bases are four bytes wide, a bare vptr each.
//
// The rest reads exactly as it does there: a slot written twice with two
// different vftable addresses is a base writing its own vptr and the derived
// overwriting it, so this is multiple inheritance from two polymorphic bases;
// the FIRST base's own store is missing because MSVC 7.1 elides the primary
// base's store when the derived store to the same slot kills it, while the
// second base's store survives; and `mov eax,ecx` with the stores going
// through eax is the constructor's `return this`.
//
// THESE TWO ARE THE BOTTOM OF A CHAIN.  The 32-byte constructors at
// 0x005E9400 and 0x005E9640 (T1ChainedVtableCtors.cpp) forward their single
// argument to exactly these two addresses and then re-stamp the same two
// slots, which is what a directly-derived class does.  That is why the
// argument is spelled here even though this body ignores it: the parameter is
// real, it is just consumed further down.
//
// The two second bases are 0x0110F978 and 0x01073760 -- the same two vftable
// addresses Q2MultipleBaseVtableSetters.cpp already names, which is evidence
// that these rows belong to the same cluster of classes, and nothing more.
//
// IDENTITY IS NOT RECOVERED.  Derived names come from the body address, base
// names from the vftable address the bytes store.

#define T1_SECOND_BASE( VT )                                                  \
	class T1Vt##VT { public: virtual void s0(); };

#define T1_ARG_TAKING_CTOR( ROW, SECOND )                                     \
	class T1Primary_##ROW { public: virtual void s0(); };                     \
	class T1Ctor_##ROW : public T1Primary_##ROW, public SECOND                \
	{                                                                         \
	public:                                                                   \
		T1Ctor_##ROW( void *a );                                              \
	};                                                                        \
	T1Ctor_##ROW::T1Ctor_##ROW( void *a )                                     \
	{                                                                         \
	}

T1_SECOND_BASE( 0110F978 )
T1_SECOND_BASE( 01073760 )

T1_ARG_TAKING_CTOR( 005E9430, T1Vt0110F978 )
T1_ARG_TAKING_CTOR( 005E9670, T1Vt01073760 )
