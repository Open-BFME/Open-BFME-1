// Seven destructors that end -- do not begin -- with a vftable store, and the
// mnemonic family turned out to be TWO NESTING DEPTHS.
//
// WHAT THE BYTES SHOW.  A __thiscall with the standard fs:[0] frame, two
// `lea ecx,[esi+OFF]` / `call REL32` destructions at descending offsets, and
// then `mov dword ptr [esi], <vftable>` as the LAST thing before the epilogue.
//
// THE POSITION OF THAT STORE IS THE WHOLE ARGUMENT.  MSVC puts a class's own
// destructor vptr reset FIRST, before the body and before any member is
// destroyed.  A store that happens AFTER every member has been destroyed is not
// this class's reset at all: it is the INLINED destructor of a polymorphic
// subobject sitting at offset 0 whose destructor body is empty, so that all it
// leaves behind is its own vptr store.  It follows that the class ITSELF is not
// polymorphic -- there is no opening store -- and that the offset-0 subobject
// is destroyed last, i.e. declared first.  ALL SEVEN ROWS STORE THE SAME
// VFTABLE ADDRESS, so all seven contain the same offset-0 type; that is a
// DIR32 operand, so it costs no pin and one class covers all seven without
// tripping the one-class-one-address rule.
//
// THE SPLIT IS IN THE EH STATE NUMBERS, AND IT IS A REAL SOURCE DIFFERENCE.
// Four rows drive the state 1 then 0 (the second store shrinking to a byte
// form, hence 80 bytes); three drive it 0 then 1 (both stores full dwords,
// hence 83).  MSVC numbers destructor unwind states by how deeply the cleanup
// is nested, and probing settles it: a FLAT class {P; A; B} gives 1 then 0,
// while wrapping the first two in one subobject -- {{P; A}; B} -- gives 0 then
// 1 and exactly three more bytes.  So the 83-byte rows have the offset-0
// polymorphic object and the first destructible member packaged together one
// level down.  Whether that package is a BASE of the class or its first MEMBER
// is not decidable: both spellings emit these bytes to the byte, and the member
// spelling is used below because it posits no inheritance.
//
// AXES: the two member offsets (0x04/0x08 up to 0x08/0x78) and the two
// destructor REL32s, plus the nesting depth.  0x0012B8E0 and 0x0012BA10 are
// byte-identical apart from their EH funcinfo, so retail carries two copies and
// each address gets its own definition.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.
//
// WHAT THE BYTES CANNOT DECIDE.  The width of the LAST member destroyed, the
// class's own size, and -- in the nested rows -- how the padding is divided
// between the inner package and the outer class.  Only the first destroyed
// member's offset and the inner member's offset are pinned.

struct Gen01073744 { virtual ~Gen01073744() {} };

#define R4_VPTR_TAIL_ELEM( T, SZ )                                            \
	struct T                                                                  \
	{                                                                         \
		char m_body[ SZ ];                                                    \
		T();                                                                  \
		~T();                                                                 \
	};

// state 1 then 0 -- flat: the polymorphic object and both members are siblings.
#define R4_VPTR_TAIL_FLAT( NAME, LEAD, M1, M2 )                               \
	struct NAME                                                               \
	{                                                                         \
		Gen01073744 m_head;                                                   \
		char m_lead[ LEAD ];                                                  \
		M1 m_first;                                                           \
		M2 m_second;                                                          \
		~NAME();                                                              \
	};                                                                        \
	NAME::~NAME() {}

#define R4_VPTR_TAIL_FLAT_TIGHT( NAME, M1, M2 )                               \
	struct NAME                                                               \
	{                                                                         \
		Gen01073744 m_head;                                                   \
		M1 m_first;                                                           \
		M2 m_second;                                                          \
		~NAME();                                                              \
	};                                                                        \
	NAME::~NAME() {}

// state 0 then 1 -- nested: the polymorphic object and the first member are one
// subobject, and the last member is a sibling of THAT.
#define R4_VPTR_TAIL_NESTED( NAME, M1, TAIL, M2 )                             \
	struct NAME##_inner                                                       \
	{                                                                         \
		Gen01073744 m_head;                                                   \
		char m_lead[ 4 ];                                                     \
		M1 m_first;                                                           \
	};                                                                        \
	struct NAME                                                               \
	{                                                                         \
		NAME##_inner m_inner;                                                 \
		char m_tail[ TAIL ];                                                  \
		M2 m_second;                                                          \
		~NAME();                                                              \
	};                                                                        \
	NAME::~NAME() {}

R4_VPTR_TAIL_ELEM( Gen000FF700, 0xC )
R4_VPTR_TAIL_ELEM( Gen000FF7D0, 4 )
R4_VPTR_TAIL_ELEM( Gen00887940, 4 )
R4_VPTR_TAIL_ELEM( Gen000658A0, 4 )
R4_VPTR_TAIL_ELEM( Gen00129C80, 4 )

R4_VPTR_TAIL_FLAT( Rva000FFCA0, 0x28, Gen000FF700, Gen000FF7D0 )
R4_VPTR_TAIL_FLAT( Rva00126DD0, 4, Gen00887940, Gen00887940 )
R4_VPTR_TAIL_FLAT_TIGHT( Rva001DC400, Gen00887940, Gen000658A0 )
R4_VPTR_TAIL_FLAT( Rva0033B2A0, 8, Gen00887940, Gen00887940 )

R4_VPTR_TAIL_NESTED( Rva0012B8E0, Gen00129C80, 0x64, Gen00887940 )
R4_VPTR_TAIL_NESTED( Rva0012BA10, Gen00129C80, 0x64, Gen00887940 )
R4_VPTR_TAIL_NESTED( Rva002D79B0, Gen00129C80, 0x6C, Gen00887940 )
