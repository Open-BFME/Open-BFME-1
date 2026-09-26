// cl: /EHsc
//
// Eleven 79-byte __thiscall destructors that destroy exactly two subobjects,
// one at a fixed offset and one at offset zero:
//
//     mov esi,ecx / mov [esp+4],esi          (this, saved for the EH funclets)
//     lea ecx,[esi+<OFFSET>] / state 0  / call <TAIL DTOR>
//     mov ecx,esi            / state -1 / call <HEAD DTOR>
//
// WHAT THE BYTES SHOW.  Two destructor calls, the far one first and the one at
// offset zero second, with the EH state dropping from 0 to -1 between them --
// the state numbering is the unwind action still outstanding, so the offset-0
// subobject is the one that survives longest.  That is C++'s destruction order
// read straight off: later-declared subobjects die first.
//
// THE OFFSET-0 CALLEE IS A SUBOBJECT, NOT A BASE, AND THE BYTES SAY SO.  Three
// of these bodies call 0x00258730 at offset zero, and that address is a
// VIRTUAL destructor in the ledger (??1SpecialPowerModuleData@@UAE@XZ and
// ??1RiderChangeContainModuleData@@UAE@XZ are folded there).  A polymorphic
// BASE forces the deriving destructor to open with a vptr store; a polymorphic
// MEMBER at offset zero does not.  There is no vptr store anywhere in any of
// the eleven bodies, so the offset-0 subobject is a member.  Every member is
// therefore spelled as a member here, which is also the reading that asserts
// less: no inheritance is claimed anywhere in this file.
//
// The `char m_gap[OFFSET-1]` is the only way to place the second member at the
// observed offset given a size-1 opaque head; it is a spacer, not a claim that
// the head subobject is one byte or that the space between is untyped.  What
// the bytes fix is the OFFSET of the tail subobject and nothing else about
// layout.
//
// The fs:[0] frame is `-EHsc` (this file's `// cl:` directive), and the pushed
// handler address is a DIR32 operand copied from retail.
//
// THE VARYING AXIS IS THREE FIELDS: the tail offset and the two callee REL32s.
// Cross-checked and the reading holds: 0x00887940 appears as the tail dtor at
// four different offsets (0xb4, 0xb8, 0x210, 0x218), and 0x00258730 appears as
// the head dtor under three different tail dtors, so neither callee is a
// stand-in for the offset.  Six of the eleven share the identical signature
// (0xb4, tail 0x00887940, head 0x00427390) -- six distinct classes with the
// same two member types at the same places, not one class at six addresses:
// they are six separate function bodies with six separate EH handler stubs.
//
// IDENTITY IS NOT RECOVERED.  Every name is address-derived.  The subobject
// destructors are ICF folds carrying several recovered names each (0x00887940
// alone holds nine, among them ?releaseBuffer@AsciiString@@IAEXXZ), so no one
// of them can be chosen as THE identity and an address-derived alias is pinned
// instead.  What the bytes cannot decide: the real class names, the head
// subobject's size, whether the gap between the two holds further members that
// need no destruction, and whether these destructors are virtual (they are
// entered non-virtually here and nothing in the body distinguishes the two).

#define Q4_SUBOBJECT( ADDR )                                              \
	class Mem##ADDR                                                       \
	{                                                                     \
	public:                                                               \
		~Mem##ADDR();                                                     \
	};

Q4_SUBOBJECT( 000B31F0 )
Q4_SUBOBJECT( 0027E4E0 )
Q4_SUBOBJECT( 00887940 )
Q4_SUBOBJECT( 00258730 )
Q4_SUBOBJECT( 000658A0 )
Q4_SUBOBJECT( 00427390 )

#define Q4_PAIR_DTOR( NAME, HEAD, TAIL, OFFSET )                          \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		~NAME();                                                          \
		HEAD m_head;                                                      \
		char m_gap[ OFFSET - 1 ];                                         \
		TAIL m_tail;                                                      \
	};                                                                    \
	NAME::~NAME()                                                         \
	{                                                                     \
	}

Q4_PAIR_DTOR( Rva00124510, Mem0027E4E0, Mem000B31F0, 0x90 )
Q4_PAIR_DTOR( Rva00259320, Mem00258730, Mem00887940, 0x218 )
Q4_PAIR_DTOR( Rva002642C0, Mem00258730, Mem000658A0, 0x210 )
Q4_PAIR_DTOR( Rva0026B8E0, Mem00258730, Mem00887940, 0x210 )
Q4_PAIR_DTOR( Rva00428B50, Mem00427390, Mem00887940, 0xb4 )
Q4_PAIR_DTOR( Rva00428DA0, Mem00427390, Mem00887940, 0xb4 )
Q4_PAIR_DTOR( Rva004293F0, Mem00427390, Mem00887940, 0xb4 )
Q4_PAIR_DTOR( Rva004297D0, Mem00427390, Mem00887940, 0xb4 )
Q4_PAIR_DTOR( Rva00429B60, Mem00427390, Mem00887940, 0xb4 )
Q4_PAIR_DTOR( Rva00429EF0, Mem00427390, Mem00887940, 0xb8 )
Q4_PAIR_DTOR( Rva0042B460, Mem00427390, Mem00887940, 0xb4 )
