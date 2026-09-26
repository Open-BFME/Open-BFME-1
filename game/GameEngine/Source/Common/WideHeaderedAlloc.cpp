// Fifteen 33-byte __cdecl one-argument allocators, all fifteen byte-identical
// except for the one rel32 -- and even that encodes the SAME absolute target
// from fifteen different addresses:
//
//     mov eax,[esp+4] / add eax,8 / push esi / push eax
//     call [ALLOC_PTR] / mov esi,eax / add esi,8
//     push esi / call 0x00897300 / add esp,8 / mov eax,esi / pop esi / ret
//
// WHAT THE BYTES SHOW.  The single `add esp,8` cleans BOTH pushed arguments at
// once, so the imported callee is __cdecl too and its cleanup was merged with
// the second call's -- counting pushes against that one adjustment is what
// settles the import's convention without looking at the import.  The request
// is grown by 8 before the call and the returned block is advanced by 8 before
// being handed on and returned, so the eight bytes in FRONT of the returned
// pointer are a header.
//
// 0x00897300 confirms it: it reads a global list head, and writes the returned
// pointer's [-8] and [-4] words as the links before making it the new head.
// So these are per-site allocation entry points over one tracked free-store.
//
// NOTHING VARIES ACROSS THE FIFTEEN except their own addresses.  They are
// byte-identical bodies the linker did not fold, which is what a class-scoped
// `operator new` looks like when fifteen classes each declare one; but the
// bytes do not name a class, so each is written as a plain function.
//
// THE INDIRECT SLOT AT 0x01337828 IS NOT AN IAT ENTRY -- the import directory
// lives at RVA 0x00F58000 and 0x00F37828 is below it, in .rdata.  It is a
// plain GLOBAL FUNCTION POINTER, and that is how it is spelled here: calling
// through `extern void *(*p)(unsigned)` emits exactly `ff 15 <DIR32>`.  A
// previous attempt logged this family as blocked on the belief that a data
// address had to be pinned to reach that encoding; it does not.  The DIR32
// site is read from retail like any other, so the address is never asserted.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived.

extern void * (*WideAllocPtr)( unsigned int bytes );

void Gen00897300( void *block );

#define WIDE_ALLOC( NAME )                                                	void *Rva##NAME( unsigned int bytes )                                 	{                                                                     		char *block = (char *)WideAllocPtr( bytes + 8 ) + 8;                 		Gen00897300( block );                                             		return block;                                                     	}

WIDE_ALLOC( 00897640 )
WIDE_ALLOC( 008A3130 )
WIDE_ALLOC( 008A90F0 )
WIDE_ALLOC( 008AB840 )
WIDE_ALLOC( 008B2AE0 )
WIDE_ALLOC( 008B2B40 )
WIDE_ALLOC( 008BA7D0 )
WIDE_ALLOC( 008BA840 )
WIDE_ALLOC( 008C45F0 )
WIDE_ALLOC( 008C46B0 )
WIDE_ALLOC( 008C4710 )
WIDE_ALLOC( 008C4770 )
WIDE_ALLOC( 008C47D0 )
WIDE_ALLOC( 008C4830 )
WIDE_ALLOC( 008C4890 )

// The sixteenth member, from the pattern sweep.

WIDE_ALLOC( 00897560 )
