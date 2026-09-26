// Fifteen 34-byte __cdecl two-pointer range walks:
//
//     push esi / mov esi,[esp+8] / push edi / mov edi,[esp+0x10]
//     cmp esi,edi / je out / mov edi,edi            <- 2-byte alignment nop
//   L: mov eax,[esi] / push 0 / mov ecx,esi / call [eax]
//     add esi,STRIDE / cmp esi,edi / jne L
//   out: pop edi / pop esi / ret
//
// WHAT THE BYTES SHOW.  Two __cdecl pointer parameters walked as [first,last)
// with a PRE-test (the `cmp/je` before the loop), the cursor advanced by a
// literal stride, and one call per element through vtable SLOT 0 with a single
// literal-zero stack argument that the callee pops.  `mov edi,edi` is MSVC's
// two-byte nop aligning the loop head, not code.
//
// THE STRIDE IS THE ONLY VARYING FIELD: 0x0C, 0x28, 0x30, 0x58, 0x5C, 0x70.
// It is sizeof(element), never written in the source; here it is produced by
// giving the element one vptr and a byte pad.
//
// WHAT THE BYTES CANNOT DECIDE.  `mov eax,[ecx] / push 0 / call [eax]` is
// equally the code for an explicit virtual-destructor call `p->~T()` (MSVC
// routes that through the scalar-deleting-destructor slot with flag 0) and for
// an ordinary virtual `p->act(0)` declared first in the class.  A virtual
// member asserts less than a destructor plus the ??_G convention, so that is
// what is written.  The two `for` and `while` spellings of the walk compile
// identically; the parameter is used directly as the cursor, and both forms
// were checked.
//
// THESE BODIES CARRY NO RELOCATIONS AT ALL -- all thirty-four bytes of each
// are compared concretely.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived.

#define WIDE_WALK( NAME, STRIDE )                                         	class WideItem##NAME                                                  	{                                                                     	public:                                                               		virtual void act( int flag );                                     		char m_pad[ STRIDE - 4 ];                                         	};                                                                    	void Rva##NAME( WideItem##NAME *first, WideItem##NAME *last )         	{                                                                     		for ( WideItem##NAME *p = first; p != last; ++p )                 			p->act( 0 );                                                  	}

WIDE_WALK( 000BA7B0, 0x70 )
WIDE_WALK( 000BB5A0, 0x70 )
WIDE_WALK( 000BB860, 0x70 )
WIDE_WALK( 00134760, 0x5C )
WIDE_WALK( 00134F20, 0x5C )
WIDE_WALK( 00135800, 0x5C )
WIDE_WALK( 003618D0, 0x58 )
WIDE_WALK( 003622C0, 0x58 )
WIDE_WALK( 00362A90, 0x58 )
WIDE_WALK( 003A70B0, 0x28 )
WIDE_WALK( 003A70E0, 0x30 )
WIDE_WALK( 003A7140, 0x0C )
WIDE_WALK( 003A83C0, 0x28 )
WIDE_WALK( 003A83F0, 0x30 )
WIDE_WALK( 003A8450, 0x0C )

// Three more, found by re-running the proven body as a pattern with the stride
// free.  They are byte-identical to three of the members above, so opcode
// grouping folded them out of the family listing entirely.

WIDE_WALK( 003A8E80, 0x28 )
WIDE_WALK( 003A8EB0, 0x30 )
WIDE_WALK( 003A8F10, 0x0C )
