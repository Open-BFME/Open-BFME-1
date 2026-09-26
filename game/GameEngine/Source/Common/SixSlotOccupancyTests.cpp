// The five byte-identical 20-byte "is any of six slots occupied" predicates at
// 0x000C9130, 0x000CA350, 0x000E9250, 0x001EB380 and 0x0020AC40.  Retail:
//
//     xor eax,eax
//     loop: cmp dword ptr [ecx+eax*4],0 / jne found
//           inc eax / cmp eax,6 / jb loop
//     xor al,al / ret
//     found: mov al,1 / ret
//
// WHAT THE BYTES SHOW.  `this` in ecx, a bare `ret`: __thiscall, no arguments.
// `mov al,1` / `xor al,al` is a bool return, not an int one -- MSVC 7.1 widens
// to eax for int.  The array being scanned is at offset 0 of the class and is
// indexed by a dword scaled by four, so its elements are four bytes wide; the
// only test applied to one is against zero, which the C++ below spells as a
// pointer test.  An int array with `!= 0` compiles to the same twenty bytes, so
// the element type is four bytes wide and nothing narrower is decidable.
//
// SIX IS A REAL ARRAY BOUND.  `cmp eax,6` is the loop's own trip count, not a
// sentinel: the compiler unrolled nothing and kept the literal, so the class
// really does hold six slots.
//
// THE COUNTER IS UNSIGNED.  `jb`, not `jl`.  A signed `int i` compiles this
// loop with `7c` (jl) at the same length -- probed, one byte different -- so
// the induction variable in the original source is an unsigned type.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Five distinct addresses spread over five
// unrelated gen_asm dumps at 0x000C9130 through 0x0020AC40; each is written as
// its own class below so the ledger claims five bodies, not one folded symbol.
//
// IDENTITY IS NOT RECOVERED.  Nothing in the image names the class or the slot
// type, so each name is derived from its own address and disclaims identity.
//
// A SIXTH OCCURRENCE IS NOT A FUNCTION.  These exact twenty bytes also occur at
// 0x001EB3A4, which is fourteen bytes into the body claimed at 0x001EB3A0 and
// is not preceded by padding.  It is a tail fragment of a longer function and
// is deliberately not claimed here.

#define BFME_SIX_SLOT_TEST( NAME )                                            	class NAME                                                                 	{                                                                          	public:                                                                    		void *m_slot[ 6 ];                                                      		bool anyOccupied() const;                                               	};                                                                         	bool NAME::anyOccupied() const                                             	{                                                                          		for ( unsigned int i = 0; i < 6; ++i )                                  		{                                                                        			if ( m_slot[ i ] )                                                    			{                                                                     				return true;                                                       			}                                                                     		}                                                                        		return false;                                                           	}

BFME_SIX_SLOT_TEST( Rva000C9130Slots )
BFME_SIX_SLOT_TEST( Rva000CA350Slots )
BFME_SIX_SLOT_TEST( Rva000E9250Slots )
BFME_SIX_SLOT_TEST( Rva001EB380Slots )
BFME_SIX_SLOT_TEST( Rva0020AC40Slots )
