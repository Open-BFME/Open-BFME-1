// Twenty-one __cdecl free functions that walk a half-open pointer range and
// call one member on every element:
//
//   push esi / mov esi,[esp+8]      ; first
//   push edi / mov edi,[esp+0x10]   ; last
//   cmp esi,edi / je done
//   mov edi,edi                     ; MSVC's 2-byte loop-alignment pad
//  body:
//   ...call...
//   add esi,<STRIDE> / cmp esi,edi / jne body
//  done:
//   pop edi / pop esi / ret
//
// WHAT THE BYTES SHOW.  Two stack arguments and no `ret n`, so these are
// __cdecl free functions, not members -- ecx is never read on entry.  The
// pre-test `cmp/je` in front of the aligned loop head is what MSVC emits for a
// `while (first != last)`; the loop exits on EQUALITY, not on `<`, so the
// source compares the pointers for inequality.  `add esi,<STRIDE>` is a `++p`
// on a typed pointer, which makes STRIDE sizeof(element) exactly.
//
// TWO CALL FORMS, WHICH IS THE ONLY REAL SPLIT IN THE GROUP:
//
//   37-byte rows:  mov eax,[esi] / push 0 / mov ecx,esi / call [eax]
//       The receiver's first dword is loaded and called through -- a VIRTUAL
//       call on the element's own vptr, first slot, with one int-width
//       argument whose value is 0.  These rows carry NO relocation at all;
//       all 37 bytes are compared against retail.  The stride includes the
//       vptr.
//
//   36-byte rows:  mov ecx,esi / call <REL32>
//       A direct __thiscall on the element with no arguments.  32 of the 36
//       bytes are concrete; only the displacement is resolved from a pin.
//
// WHAT THE BYTES DO NOT DECIDE.  The virtual rows' `push 0` is a plain
// int-width zero: a scalar-deleting destructor invoked as `p->~T()` and an
// ordinary `virtual void f(int)` called with 0 produce the same bytes, and the
// less-asserting spelling is used here.  Nothing says the elements of the
// three rows that share a stride and a callee are one type rather than three
// look-alikes -- they are spelled as one because a shared callee is the
// simplest reading, and only the three FUNCTIONS are forced apart, because one
// source function cannot occupy three addresses.  Element layout beyond the
// size is not recovered.
//
// IDENTITY IS NOT RECOVERED.  The loop names are derived from their own
// addresses.  The direct callees are named for the body address their REL32
// resolves through -- the call sites encode an incremental-link thunk, and
// targets/game/reverse/symbols.csv already pins those names at those bodies.

// ---------------------------------------------------------------- virtual form

#define Q2_VIRTUAL_ELEMENT( STRIDE )                                      \
	class Q2VirtualElem##STRIDE                                           \
	{                                                                     \
	public:                                                               \
		virtual void act( int flag );                                     \
	private:                                                              \
		char m_unreconstructed_04[ 0x##STRIDE - 4 ];                      \
	};

#define Q2_VIRTUAL_RANGE_LOOP( NAME, ELEM )                               \
	void NAME( ELEM *first, ELEM *last )                                  \
	{                                                                     \
		while ( first != last )                                           \
		{                                                                 \
			first->act( 0 );                                              \
			++first;                                                      \
		}                                                                 \
	}

Q2_VIRTUAL_ELEMENT( 8C )
Q2_VIRTUAL_ELEMENT( B4 )
Q2_VIRTUAL_ELEMENT( DC )

Q2_VIRTUAL_RANGE_LOOP( Rva00193B90, Q2VirtualElem8C )
Q2_VIRTUAL_RANGE_LOOP( Rva00195420, Q2VirtualElem8C )
Q2_VIRTUAL_RANGE_LOOP( Rva00195B20, Q2VirtualElem8C )
Q2_VIRTUAL_RANGE_LOOP( Rva003621D0, Q2VirtualElemB4 )
Q2_VIRTUAL_RANGE_LOOP( Rva00360E00, Q2VirtualElemB4 )
Q2_VIRTUAL_RANGE_LOOP( Rva00361850, Q2VirtualElemB4 )
Q2_VIRTUAL_RANGE_LOOP( Rva003A6F10, Q2VirtualElemDC )
Q2_VIRTUAL_RANGE_LOOP( Rva003A8310, Q2VirtualElemDC )
Q2_VIRTUAL_RANGE_LOOP( Rva003A8DC0, Q2VirtualElemDC )

// ----------------------------------------------------------------- direct form

#define Q2_DIRECT_ELEMENT( BODY, STRIDE )                                 \
	class Gen##BODY                                                       \
	{                                                                     \
	public:                                                               \
		void handle();                                                    \
	private:                                                              \
		char m_unreconstructed_00[ STRIDE ];                              \
	};

#define Q2_DIRECT_RANGE_LOOP( NAME, ELEM )                                \
	void NAME( ELEM *first, ELEM *last )                                  \
	{                                                                     \
		while ( first != last )                                           \
		{                                                                 \
			first->handle();                                              \
			++first;                                                      \
		}                                                                 \
	}

Q2_DIRECT_ELEMENT( 00774D40, 0xBC )
Q2_DIRECT_ELEMENT( 0039DCC0, 0x88 )
Q2_DIRECT_ELEMENT( 00606F70, 0x1F0 )
Q2_DIRECT_ELEMENT( 00608480, 0x210 )

Q2_DIRECT_RANGE_LOOP( Rva0013B8B0, Gen00774D40 )
Q2_DIRECT_RANGE_LOOP( Rva0013BDB0, Gen00774D40 )
Q2_DIRECT_RANGE_LOOP( Rva0013BF50, Gen00774D40 )
Q2_DIRECT_RANGE_LOOP( Rva0039EA00, Gen0039DCC0 )
Q2_DIRECT_RANGE_LOOP( Rva0039EA30, Gen0039DCC0 )
Q2_DIRECT_RANGE_LOOP( Rva0039EA60, Gen0039DCC0 )
Q2_DIRECT_RANGE_LOOP( Rva00607360, Gen00606F70 )
Q2_DIRECT_RANGE_LOOP( Rva00607390, Gen00606F70 )
Q2_DIRECT_RANGE_LOOP( Rva006073C0, Gen00606F70 )
Q2_DIRECT_RANGE_LOOP( Rva00608BD0, Gen00608480 )
Q2_DIRECT_RANGE_LOOP( Rva00608C00, Gen00608480 )
Q2_DIRECT_RANGE_LOOP( Rva00608C30, Gen00608480 )
