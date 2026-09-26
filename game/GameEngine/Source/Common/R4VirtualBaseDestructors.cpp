// cl: /vd0
// Six destructors of classes that inherit a VIRTUAL BASE, entered with `this`
// already pointing AT that base.
//
// WHAT THE BYTES SHOW, AND WHY EVERY OFFSET IS NEGATIVE.  The body opens
// `mov eax,[ecx-NV] / mov edx,[eax+4] / mov [edx+ecx-NV], <vftable>`: it reads a
// pointer stored NV bytes BELOW `this`, follows it to entry 1 of what it points
// at, and uses that as a displacement back to `this`.  That is MSVC's virtual
// base table protocol -- vbptr at the top of the object, vbtable[1] = the offset
// from the vbptr to the first virtual base -- and it only reads that way if
// `this` IS the virtual base and NV is the size of the whole NON-VIRTUAL part
// above it.  MSVC lays virtual bases LAST, so a destructor compiled against the
// virtual-base pointer sees the vbptr at a negative offset and nothing else can
// produce this.  The displacement arithmetic then lands the store back on the
// virtual base's own vfptr at offset 0.
//
// The body then does exactly three things: store the DERIVED class's vftable
// into that vfptr, destroy ONE member (a __thiscall call with ecx = this - X),
// and store a SECOND, DIFFERENT vftable into the SAME slot.  The second store is
// the intermediate base's destructor inlined -- it resets the vfptr to its own
// table on the way out -- and its presence is what proves there IS an
// intermediate class between the derived one and the virtual base, with its own
// vftable and a destructor that does nothing else.  The EH state driven to 0
// around the member destruction and never back to -1 says the same thing from
// the other side: after the member is gone, one cleanup still remains.
//
// `/vd0` IS PART OF THE EVIDENCE.  Under the compiler's default, a class with a
// virtual base that overrides one of its virtual functions gets a vtordisp
// field, and the second vptr store turns into four instructions of displacement
// arithmetic instead of one store of a literal.  Retail stores a literal, so
// this translation unit was built with vtordisp suppressed.
//
// THREE AXES.  NV, the non-virtual size (0x70, 0x74, 0x90, 0x94, 0xB8, 0xBC);
// the member's offset within it (4 or 8); and the member destructor's REL32, of
// which there are three, each used by exactly one (NV, offset) pair per value.
// The four rows at 98 bytes rather than 89 are the ones whose displacements pass
// 0x7F and need imm32 forms -- not a fourth axis.
//
// THE SECOND VFTABLE REPEATS AND THAT IS THE CROSS-CHECK.  Four distinct
// addresses across six rows: 0x0112F2F4 for the two rows with the member at 8
// and 0x0112F304 for two of the rows with it at 4, plus one each for the other
// two.  Rows sharing a second vftable also share the member offset, so they get
// ONE intermediate class here rather than two -- which is what keeps a single
// class from being claimed at several data addresses.  The six DERIVED vftables
// are all distinct, so the six rows are six types.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.
//
// WHAT THE BYTES CANNOT DECIDE.  The virtual base's contents beyond "it starts
// with a vfptr", the member's width, and how the padding is split between the
// intermediate class and the derived one -- only the member's offset and the
// total non-virtual size are pinned.

struct GenVirtualBase
{
	virtual ~GenVirtualBase();
	virtual void handle();
};

#define R4_VBASE_MEMBER( T )                                                  \
	struct T                                                                  \
	{                                                                         \
		char m_body[ 4 ];                                                     \
		T();                                                                  \
		~T();                                                                 \
	};

// Intermediate class with the member at offset 8: vbptr, four bytes, then the
// derived class's member.
#define R4_VBASE_MID_GAP( T )                                                 \
	struct T : virtual GenVirtualBase                                         \
	{                                                                         \
		char m_lead[ 4 ];                                                     \
		virtual void handle();                                                \
		~T() {}                                                               \
	};

// Intermediate class with the member at offset 4: vbptr only.
#define R4_VBASE_MID_TIGHT( T )                                               \
	struct T : virtual GenVirtualBase                                         \
	{                                                                         \
		virtual void handle();                                                \
		~T() {}                                                               \
	};

#define R4_VBASE_DTOR( NAME, MID, MEMBER, TAIL )                              \
	struct NAME : public MID                                                  \
	{                                                                         \
		MEMBER m_member;                                                      \
		char m_tail[ TAIL ];                                                  \
		virtual void handle();                                                \
		~NAME();                                                              \
	};                                                                        \
	NAME::~NAME() {}

R4_VBASE_MEMBER( Gen0053AC40 )
R4_VBASE_MEMBER( Gen008427F0 )
R4_VBASE_MEMBER( Gen00842970 )

R4_VBASE_MID_GAP( Mid0112F2F4 )
R4_VBASE_MID_TIGHT( Mid0112F304 )
R4_VBASE_MID_GAP( Mid0112F2FC )
R4_VBASE_MID_TIGHT( Mid0112F30C )

R4_VBASE_DTOR( Rva0053ADC0, Mid0112F2F4, Gen0053AC40, 0x68 )
R4_VBASE_DTOR( Rva0084B3A0, Mid0112F2F4, Gen008427F0, 0xB0 )
R4_VBASE_DTOR( Rva005C7180, Mid0112F304, Gen0053AC40, 0x68 )
R4_VBASE_DTOR( Rva0084B410, Mid0112F304, Gen008427F0, 0xB0 )
R4_VBASE_DTOR( Rva0084B510, Mid0112F2FC, Gen00842970, 0x88 )
R4_VBASE_DTOR( Rva0084B580, Mid0112F30C, Gen00842970, 0x88 )
