// cl: /EHs-c-
// Four __thiscall copy constructors, 126 to 156 bytes, one level below
// V3HeadNodeCopyCtors.cpp with the head INLINED instead of called.  Retail
// (the four differ only in one vftable and in how many trailing dwords they
// copy):
//
//     push esi ; push edi ; mov edi,[esp+0xC] ; mov esi,ecx
//     lea eax,[edi+4] ; push eax ; lea ecx,[esi+4]
//     mov [esi],     0x0111126C          ; the head's own vptr
//     call 0x005C2170                    ; the list node's copy constructor
//     mov ecx,[edi+0x10] ; mov [esi+0x10],ecx     ; the head's int
//     mov [esi+0x14],0x0110F9AC          ; second base's own vptr
//     mov [esi+0x18],0x011106F4          ; third base's own vptr
//     mov [esi],     0x0111182C          ; the MIDDLE class's three
//     mov [esi+0x14],0x01111828
//     mov [esi+0x18],0x01111824
//     mov [esi+0x1C],0x0110F980          ; fourth base's own vptr
//     mov dl,[edi+0x20] ; mov [esi+0x20],dl       ; its one byte
//     mov [esi+0x1C],<FOURTH BASE VFTABLE>        ; the varying one
//     <N dwords copied from edi+0x24 to esi+0x24>
//     pop edi
//     mov [esi],     <DERIVED VFTABLE 0>
//     mov [esi+0x14],<DERIVED VFTABLE 0x14>
//     mov [esi+0x18],<DERIVED VFTABLE 0x18>
//     mov [esi+0x1C],<DERIVED VFTABLE 0x1C>
//     mov eax,esi ; pop esi ; ret 4
//
// WHAT THE BYTES SHOW.  Four polymorphic slots -- 0, 0x14, 0x18 and 0x1C -- and
// each is written THREE times: once by the subobject that owns it, once by a
// middle class, once by the class being constructed.  The first three writes of
// the middle round land together; the 0x1C one lands later, after the byte copy,
// because the subobject at 0x1C is constructed after the ones below it and
// carries its own two-level chain.
//
// THE HEAD IS INLINED HERE.  V3HeadNodeCopyCtors.cpp landed nine bodies that
// call this head's copy constructor out of line; these four contain it: the
// same vptr 0x0111126C, the same call to the node's copy constructor at
// 0x005C2170, the same int at +0x10, and the same 0x14 width.  Its second base
// is that file's V3Vt0110F9AC.  So the two readings agree and this one sees one
// level deeper.
//
// THE SUBOBJECT AT 0x1C IS A BASE AND ITS FIELDS ARE SCALARS.  Its address is
// never materialised -- the byte comes from a bare [edi+0x20] with no
// null-propagating test/je/lea/jmp/xor -- because every field it copies is a
// scalar and MSVC folds the base adjustment into each displacement.  That check
// only survives when the converted pointer has to exist, which is what happens
// when the base's own members are class types (V3ThirdBaseInlineCopyCtors.cpp)
// or when it is passed to a call (V3ChainedCopyCtorsWithSecondBase.cpp).  Its
// vptr being re-stamped at the end by the most derived class is what makes it a
// base rather than a member: a member's vptr is written once, by the member.
//
// FOUR VARYING FIELDS PICK OUT FOUR CLASSES: the 0x1C vftable of the inner
// class and the derived quadruple both differ per row, and the trailing dword
// count runs 6, 3, 1 and 5 -- so no two rows are the same type.
//
// IDENTITY IS NOT RECOVERED.  Names come from addresses; the vftable dwords are
// DIR32 sites the gate takes from the target.

typedef int Int;

// ---- the head, landed in V3HeadNodeCopyCtors.cpp; the node call survives ----

struct GenNode_006fa270
{
	void *m_owner;
	GenNode_006fa270 *m_prev;
	GenNode_006fa270 *m_next;

	GenNode_006fa270( const GenNode_006fa270 & );
	~GenNode_006fa270(void);
};

class V3NodeHead
{
public:
	virtual ~V3NodeHead() {}
	GenNode_006fa270 m_node;		// +4
	Int m_unreconstructed_10;		// +0x10
};

class V3Vt0110F9AC
{
public:
	virtual void s0();
	virtual ~V3Vt0110F9AC() {}
};

class V3Vt011106F4
{
public:
	virtual void s0();
	virtual ~V3Vt011106F4() {}
};

// the middle class: the round that rewrites 0, 0x14 and 0x18 together
class V3Mid0111182C
	: public V3NodeHead, public V3Vt0110F9AC, public V3Vt011106F4
{
};

// ---- the base at 0x1C: a vptr and a byte, then a derived level of dwords ----

class V3Vt0110F980
{
public:
	virtual void s0();
	virtual ~V3Vt0110F980() {}
	char m_field04;
};

#define V3_INNER_1( NAME )                                                \
	class NAME : public V3Vt0110F980                                      \
	{                                                                     \
	public:                                                               \
		Int m_field08;                                                    \
	};

#define V3_INNER_3( NAME )                                                \
	class NAME : public V3Vt0110F980                                      \
	{                                                                     \
	public:                                                               \
		Int m_field08, m_field0C, m_field10;                              \
	};

#define V3_INNER_5( NAME )                                                \
	class NAME : public V3Vt0110F980                                      \
	{                                                                     \
	public:                                                               \
		Int m_field08, m_field0C, m_field10, m_field14, m_field18;        \
	};

#define V3_INNER_6( NAME )                                                \
	class NAME : public V3Vt0110F980                                      \
	{                                                                     \
	public:                                                               \
		Int m_field08, m_field0C, m_field10;                              \
		Int m_field14, m_field18, m_field1C;                              \
	};

V3_INNER_6( V3Inner0111098C )
V3_INNER_3( V3Inner011109CC )
V3_INNER_1( V3Inner01110A0C )
V3_INNER_5( V3Inner01110A4C )

// -------------------------------------------------------------- the rows ----

#define V3_FOUR_SLOT_COPY_CTOR( NAME, INNER )                             \
	class NAME : public V3Mid0111182C, public INNER                       \
	{                                                                     \
	public:                                                               \
		NAME( const NAME & );                                             \
	};                                                                    \
	NAME::NAME( const NAME &o ) : V3Mid0111182C( o ), INNER( o ) {}

V3_FOUR_SLOT_COPY_CTOR( Rva005ED9C0, V3Inner0111098C )
V3_FOUR_SLOT_COPY_CTOR( Rva005EDB50, V3Inner011109CC )
V3_FOUR_SLOT_COPY_CTOR( Rva005EDCC0, V3Inner01110A0C )
V3_FOUR_SLOT_COPY_CTOR( Rva005EDE20, V3Inner01110A4C )
