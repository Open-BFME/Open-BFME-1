// Nine 34-byte __cdecl functions that call one fixed helper on their first
// argument and then hand a pair of ADJUSTED pointers to a function pointer
// held in a global:
//
//   push esi / mov esi,[esp+8]          ; a
//   push esi / call <REL32>             ; helper( a )
//   mov eax,[esp+0x10] / add eax,8 / push eax
//   add esi,-8 / push esi
//   call dword ptr [<GLOBAL>]           ; (*g)( a - 8, b + 8 )
//   add esp,0xc / pop esi / ret
//
// WHAT THE BYTES SHOW.  One `add esp,0xc` at the end cleans all three pushes,
// so both callees are __cdecl and the caller merged the two cleanups: one
// argument to the helper, two to the indirect callee.  The indirect call goes
// through `ff 15 <abs>`, an absolute memory operand, so the callee lives in a
// global function pointer, not in a vtable and not in the object.  All nine
// rows use the SAME global and the SAME helper -- they differ only in the
// displacement each call site needs to reach that one helper, so every one of
// these bodies is otherwise byte-for-byte identical and NOTHING here tells the
// nine apart.  They get nine names because nine addresses need nine source
// functions.
//
// THE TWO ADJUSTMENTS ARE OPPOSITE AND EQUAL: the first argument goes down by
// 8 and the second up by 8.  The helper at 0x00897330 itself opens with
// `mov edx,[esp+4] / mov eax,[edx-8]`, so the pointers these functions receive
// already sit 8 bytes inside a block whose header is at -8.  That is a fact
// about the layout, not about these bodies.
//
// WHAT THE BYTES DO NOT DECIDE.  Nothing about the pointed-at types: `char *`
// with literal -8/+8 is used because any 8-byte element type with `p - 1` and
// `p + 1` encodes the same.  Nothing says the global is a plain function
// pointer rather than an import thunk slot; the address is 0x01337830 and its
// four bytes come from retail.  26 of the 34 bytes are concrete -- everything
// outside the REL32 and that one absolute operand.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

typedef void ( __cdecl *Q2PairDispatchFn )( char *first, char *second );

extern Q2PairDispatchFn g_Q2PairDispatch;			///< retail 0x01337830

void Gen00897330( char *block );

#define Q2_INDIRECT_PAIR_DISPATCH( NAME )                                 \
	void NAME( char *a, char *b )                                         \
	{                                                                     \
		Gen00897330( a );                                                 \
		g_Q2PairDispatch( a - 8, b + 8 );                                 \
	}

Q2_INDIRECT_PAIR_DISPATCH( Rva008B2B10 )
Q2_INDIRECT_PAIR_DISPATCH( Rva008B2B70 )
Q2_INDIRECT_PAIR_DISPATCH( Rva008C4620 )
Q2_INDIRECT_PAIR_DISPATCH( Rva008C4680 )
Q2_INDIRECT_PAIR_DISPATCH( Rva008C46E0 )
Q2_INDIRECT_PAIR_DISPATCH( Rva008C4740 )
Q2_INDIRECT_PAIR_DISPATCH( Rva008C47A0 )
Q2_INDIRECT_PAIR_DISPATCH( Rva008C4800 )
Q2_INDIRECT_PAIR_DISPATCH( Rva008C4860 )
