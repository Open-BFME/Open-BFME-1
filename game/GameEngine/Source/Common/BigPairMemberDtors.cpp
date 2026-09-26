// cl: /DNDEBUG /MD /EHsc
// Sixteen 76-byte __thiscall destructors, one shape.  Retail:
//
//     push -1 / push <ehdata> / fs:[0] frame ; EH state 0, `this` at [esp+4]
//     lea ecx,[esi+<OFFSET>] / call <REL32-A>   ; destroy the member at OFFSET
//     mov ecx,esi / EH state -1 / call <REL32-B>; destroy the member at 0
//
// WHAT THE BYTES SHOW.  No vptr store anywhere, so the owner is NOT
// polymorphic and neither subobject has an inlinable empty virtual destructor:
// both destructors are real out-of-line calls.  The higher offset is destroyed
// first, which is reverse declaration order for MEMBERS (and equally for
// BASES -- the bytes cannot separate those two here, and member declarations
// are the weaker claim, so that is what this file spells).  `mov ecx,esi` for
// the second call is offset zero.
//
// The EH state goes 0 before the first call and -1 before the second, which is
// the unwind funclet's record that after the first destructor returns only the
// offset-0 subobject is still alive.
//
// TWO AXES, BOTH READ DIRECTLY: the OFFSET (a disp8) and the two REL32
// destructors.  Sixteen members over eleven distinct callees; one member names
// the same callee for both subobjects.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.  The EH
// data is a DIR32 relocation site the byte gate takes from the target; both
// destructors are REL32 and are pinned in targets/game/reverse/symbols.csv.

#define BFME_SUBOBJECT_DTOR( ADDR )                                       \
	class Mem##ADDR                                                       \
	{                                                                     \
	public:                                                               \
		~Mem##ADDR();                                                     \
	};

#define BFME_PAIR_DTOR( NAME, HEAD, TAIL, PAD )                           \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		~NAME();                                                          \
		HEAD m_head;                                                      \
		char m_pad[ PAD ];                                                \
		TAIL m_tail;                                                      \
	};                                                                    \
	NAME::~NAME() {}

BFME_SUBOBJECT_DTOR( 000658A0 )
BFME_SUBOBJECT_DTOR( 00078B80 )
BFME_SUBOBJECT_DTOR( 00128C50 )
BFME_SUBOBJECT_DTOR( 00129C80 )
BFME_SUBOBJECT_DTOR( 00197BC0 )
BFME_SUBOBJECT_DTOR( 00197C60 )
BFME_SUBOBJECT_DTOR( 002360C0 )
BFME_SUBOBJECT_DTOR( 002DAB10 )
BFME_SUBOBJECT_DTOR( 002DBBF0 )
BFME_SUBOBJECT_DTOR( 002E1260 )
BFME_SUBOBJECT_DTOR( 0039D550 )
BFME_SUBOBJECT_DTOR( 00770380 )
BFME_SUBOBJECT_DTOR( 00887940 )
BFME_SUBOBJECT_DTOR( 009A1A40 )
BFME_SUBOBJECT_DTOR( 0090D090 )
BFME_SUBOBJECT_DTOR( 009DB7A0 )

BFME_PAIR_DTOR( Rva00078D90, Mem009A1A40, Mem00078B80, 7 )
BFME_PAIR_DTOR( Rva00129560, Mem00128C50, Mem00887940, 91 )
BFME_PAIR_DTOR( Rva00198550, Mem00197BC0, Mem00197C60, 11 )
BFME_PAIR_DTOR( Rva00212BB0, Mem00128C50, Mem0039D550, 91 )
BFME_PAIR_DTOR( Rva00212C70, Mem00128C50, Mem0039D550, 91 )
BFME_PAIR_DTOR( Rva00213220, Mem00128C50, Mem00129C80, 91 )
BFME_PAIR_DTOR( Rva002832C0, Mem00887940, Mem00887940, 47 )
BFME_PAIR_DTOR( Rva002DAC90, Mem002DAB10, Mem00887940, 87 )
BFME_PAIR_DTOR( Rva002DB120, Mem002DAB10, Mem00887940, 95 )
BFME_PAIR_DTOR( Rva002DC670, Mem002DAB10, Mem002DBBF0, 123 )
BFME_PAIR_DTOR( Rva002DD220, Mem002DAB10, Mem00887940, 87 )
BFME_PAIR_DTOR( Rva002DEE50, Mem002DAB10, Mem000658A0, 87 )
BFME_PAIR_DTOR( Rva002DF6D0, Mem002DAB10, Mem00887940, 91 )
BFME_PAIR_DTOR( Rva002E9E10, Mem00887940, Mem002E1260, 7 )
BFME_PAIR_DTOR( Rva003B9270, Mem00887940, Mem002360C0, 7 )
BFME_PAIR_DTOR( Rva00770F40, Mem00887940, Mem00770380, 15 )
BFME_PAIR_DTOR( Rva0090E520, Mem0090D090, Mem009DB7A0, 59 )
BFME_PAIR_DTOR( Rva0090E620, Mem0090D090, Mem009DB7A0, 59 )
