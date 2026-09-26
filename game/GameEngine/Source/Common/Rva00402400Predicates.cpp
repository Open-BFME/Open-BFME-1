// cl: /EHs-c-
// Eight __cdecl predicates in one 0x2C0-byte run, two shapes of four.  Retail
// (the four members of each shape differ only in one immediate, which runs
// 1, 3, 4, 2 down the addresses in BOTH shapes):
//
//   0x00402400, 64 bytes, two pointer arguments:
//     mov eax,[esp+4] ; push esi ; mov esi,[eax+0xC]
//     mov eax,esi ; and eax,7 ; jne + ; mov eax,<K>
//     mov ecx,[esp+0xC] ; mov ecx,[ecx+0xC]
//     mov edx,ecx ; and edx,7 ; jne + ; mov edx,<K>
//     cmp eax,edx ; jne fail
//     xor ecx,esi ; test ecx,0xFC0 ; jne fail
//     mov eax,1 ; pop esi ; ret
//   fail: xor eax,eax ; pop esi ; ret
//
//   0x004025C0, 60 bytes, one pointer argument:
//     mov ecx,[esp+4]
//     mov ax,[ecx]      ; test ax,ax ; mov edx,<K> ; je + ; movzx edx,ax
//     mov ax,[ecx+0x10] ; test ax,ax ; jne L ; mov eax,<K> ; jmp M ; L: movzx eax,ax
//     cmp edx,eax ; jne fail
//     mov eax,[ecx+4] ; cmp eax,[ecx+0x14] ; jne fail
//     mov eax,1 ; ret
//   fail: xor eax,eax ; ret
//
// WHAT THE BYTES SHOW.  No `ret N` and no `mov eax,ecx`, so both shapes are
// __cdecl free functions, not members; each returns 1 or 0 in a full dword, so
// the return type is the four-byte Bool, not `bool`.
//
// THE `? :` IS IN THE SOURCE, NOT THE CODEGEN, AND THE TWO SHAPES SPELL IT
// OPPOSITE WAYS.  `and eax,7` leaves the masked value in the register and the
// `jne` keeps it -- compute first, substitute the default only when it came out
// zero -- which is what `( f & 7 ) ? ( f & 7 ) : K` emits.  The second shape
// loads the default FIRST (`mov edx,K` ahead of the test) and overwrites it with
// the widened field, which is `f == 0 ? K : f`.  Writing either one the other
// way round inverts the branch and the row stops matching, so the asymmetry is
// two different source spellings and not scheduling.
//
// The second shape's operands then differ from each other again: the first is a
// conditional move around three bytes, the second a jump over the default.  That
// one IS scheduling -- the same spelling produces both.
//
// THE SECOND OPERAND'S FIELD IS LOADED LATE in the first shape -- after the
// first operand's default is resolved -- so the source evaluates one side
// completely before touching the other.
//
// 0xFC0 IS SIX BITS AT 6..11 compared for equality by XOR, so the dword at
// +0xC is a packed bitfield: a three-bit count at 0 and a six-bit field at 6.
// The second shape's structure is two 0x10-byte halves compared field for
// field, a sixteen-bit count at +0 and a dword at +4 in each.
//
// IDENTITY IS NOT RECOVERED.  Names come from addresses and the field names
// carry their offsets.  Nothing here relocates: all 64 and all 60 bytes of every
// row are concrete.

typedef int Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

struct Rva00402400Packed
{
	Int m_unreconstructed_00, m_unreconstructed_04, m_unreconstructed_08;
	UnsignedInt m_bits0C;
};

#define RVA_PACKED_MATCH( NAME, DEFAULT )                                 \
	Bool NAME( const Rva00402400Packed *a, const Rva00402400Packed *b )   \
	{                                                                     \
		UnsignedInt abits = a->m_bits0C;                                  \
		UnsignedInt acount = ( abits & 7 ) ? ( abits & 7 ) : DEFAULT;     \
		UnsignedInt bbits = b->m_bits0C;                                  \
		UnsignedInt bcount = ( bbits & 7 ) ? ( bbits & 7 ) : DEFAULT;     \
		return acount == bcount && ( ( abits ^ bbits ) & 0xfc0 ) == 0;    \
	}

RVA_PACKED_MATCH( Rva00402400, 1 )
RVA_PACKED_MATCH( Rva00402450, 3 )
RVA_PACKED_MATCH( Rva004024A0, 4 )
RVA_PACKED_MATCH( Rva004024F0, 2 )

struct Rva004025C0Half
{
	UnsignedShort m_count00;
	Int m_unreconstructed_04;
	Int m_unreconstructed_08, m_unreconstructed_0C;
};

struct Rva004025C0Pair
{
	Rva004025C0Half m_first;
	Rva004025C0Half m_second;
};

#define RVA_PAIR_MATCH( NAME, DEFAULT )                                   \
	Bool NAME( const Rva004025C0Pair *p )                                 \
	{                                                                     \
		UnsignedInt first = p->m_first.m_count00 == 0                     \
				? DEFAULT : p->m_first.m_count00;                         \
		UnsignedInt second = p->m_second.m_count00 == 0                   \
				? DEFAULT : p->m_second.m_count00;                        \
		return first == second                                            \
				&& p->m_first.m_unreconstructed_04                        \
					== p->m_second.m_unreconstructed_04;                  \
	}

RVA_PAIR_MATCH( Rva004025C0, 1 )
RVA_PAIR_MATCH( Rva00402610, 3 )
RVA_PAIR_MATCH( Rva00402660, 4 )
RVA_PAIR_MATCH( Rva004026B0, 2 )
