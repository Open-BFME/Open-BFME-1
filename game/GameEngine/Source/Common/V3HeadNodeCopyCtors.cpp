// cl: /EHs-c-
// Nine __thiscall copy constructors, 59 or 73 bytes, of the class that sits at
// offset 0 of everything else in this translation unit.  Retail:
//
//     push esi ; push edi ; mov edi,[esp+0xC] ; mov esi,ecx
//     lea eax,[edi+4] ; push eax ; lea ecx,[esi+4]
//     mov [esi],0x0111126C                  ; the head's own vptr
//     call 0x005C2170                       ; the list node's copy constructor
//     mov ecx,[edi+0x10] ; mov [esi+0x10],ecx    ; the head's int
//     mov [esi+0x14],<SECOND BASE VFTABLE>
//   [ mov [esi+0x18],<THIRD BASE VFTABLE> ]      ; 73-byte rows only
//     pop edi
//     mov [esi],     <DERIVED VFTABLE 0>
//     mov [esi+0x14],<DERIVED VFTABLE 0x14>
//   [ mov [esi+0x18],<DERIVED VFTABLE 0x18> ]    ; 73-byte rows only
//     mov eax,esi ; pop esi ; ret 4
//
// THE HEAD IS THE SAME CLASS ALREADY LANDED IN V3MiDtorsWithListNode.cpp: vptr
// 0x0111126C at offset 0, a twelve-byte intrusive list subobject at +4, an int
// at +0x10, total width 0x14 -- which is exactly where the second base starts
// here.  There the head's destructor tail-called the node's unlink; here the
// head's copy constructor copy-constructs the node and then copies the int.  The
// two bodies are independent readings of one layout and they agree.
//
// THE NODE'S COPY CONSTRUCTOR IS 0x005C2170, reached through the incremental-
// link thunk 0x0002E70D.  Disassembled, it does `m_owner = o.m_owner` and then
// splices this onto the owner's list -- reading the tail at owner+0x9C, writing
// the head at owner+0x98, zeroing prev and next when the owner is null.  Those
// are the same two owner fields and the same three node fields that
// game/GameEngine/Source/Common/Gen_006fa270.cpp recovered from __copy and
// __destroy_aux, so this is that node's copy constructor.  Its body is defined
// here because these nine callers independently prove both its identity and
// its insertion semantics.
//
// TWO ROW SHAPES, ONE SOURCE SHAPE.  Six rows carry a third base at 0x18 and
// three do not; nothing else differs.  Both extra bases are DEFAULT-constructed,
// not copied -- see V3InlineTwoBaseCopyCtors.cpp, where a wide base makes the
// difference visible and settles it for the whole family; here every extra base
// is unobservably narrow, and this file follows the shape that file proved.
//
// THE SIX THIRD-BASE VFTABLES ARE Q2MultipleBaseVtableSetters.cpp'S SIX AGAIN --
// 0x0110F978, 0x01073760, 0x0110F9E4, 0x0110F9E8, 0x0110FA14, 0x0107375C, one
// per 73-byte row, in the same order the addresses ascend.  The six
// second-base vftables at 0x14 are all distinct too, so the nine rows are nine
// classes over one head.
//
// IDENTITY IS NOT RECOVERED beyond the node.  Every vftable dword is a DIR32
// site the gate takes from the target.

// The head's implicit copy constructor needs the node's destructor as its unwind
// action, so this TU emits that inline destructor out of line as well.  No ledger
// row claims it here.
// ??1GenNode_006fa270@@QAE@XZ present-unmatched

struct GenNode_006fa270;

struct GenOwner_006fa270
{
	char m_unreconstructed_00[ 0x98 ];
	GenNode_006fa270 *m_head;
	GenNode_006fa270 *m_tail;
};

struct GenNode_006fa270
{
	GenOwner_006fa270 *m_owner;	// +0
	GenNode_006fa270 *m_prev;	// +4
	GenNode_006fa270 *m_next;	// +8

	void unlink(void);

	// Retail's nine head constructors call this COMDAT instead of absorbing it.
	__declspec(noinline) GenNode_006fa270( const GenNode_006fa270 & );

	~GenNode_006fa270(void) { unlink(); }
};

GenNode_006fa270::GenNode_006fa270( const GenNode_006fa270 &other )
{
	m_owner = other.m_owner;
	if ( m_owner )
	{
		GenOwner_006fa270 *owner = m_owner;
		m_prev = owner->m_tail;
		m_next = 0;
		owner->m_tail = this;
		if ( m_prev )
			m_prev->m_next = this;
		else
			m_owner->m_head = this;
	}
	else
	{
		m_next = 0;
		m_prev = 0;
	}
}

class V3NodeHead
{
public:
	virtual ~V3NodeHead() {}
	GenNode_006fa270 m_node;		// +4
	int m_unreconstructed_10;		// +0x10
};

#define V3_VT_BASE( ADDR )                                                \
	class V3Vt##ADDR                                                      \
	{                                                                     \
	public:                                                               \
		virtual void s0();                                                \
		virtual ~V3Vt##ADDR() {}                                          \
	};

// second bases, at 0x14
V3_VT_BASE( 0110F97C )
V3_VT_BASE( 0110F9CC )
V3_VT_BASE( 0110F9AC )
V3_VT_BASE( 01110898 )
V3_VT_BASE( 0111081C )
V3_VT_BASE( 0111082C )
V3_VT_BASE( 0111089C )
V3_VT_BASE( 01110834 )
V3_VT_BASE( 01110830 )

// third bases, at 0x18 -- the six shared with Q2MultipleBaseVtableSetters.cpp
V3_VT_BASE( 0110F978 )
V3_VT_BASE( 01073760 )
V3_VT_BASE( 0110F9E4 )
V3_VT_BASE( 0110F9E8 )
V3_VT_BASE( 0110FA14 )

class V3Vt0107375C
{
public:
	virtual void s0();
	virtual ~V3Vt0107375C() {}
	int m_unreconstructed_04;
};

#define V3_HEAD_COPY_CTOR_2( NAME, SECOND )                               \
	class NAME : public V3NodeHead, public SECOND                         \
	{                                                                     \
	public:                                                               \
		NAME( const NAME & );                                             \
	};                                                                    \
	NAME::NAME( const NAME &o ) : V3NodeHead( o ) {}

#define V3_HEAD_COPY_CTOR_3( NAME, SECOND, THIRD )                        \
	class NAME : public V3NodeHead, public SECOND, public THIRD           \
	{                                                                     \
	public:                                                               \
		NAME( const NAME & );                                             \
	};                                                                    \
	NAME::NAME( const NAME &o ) : V3NodeHead( o ) {}

V3_HEAD_COPY_CTOR_2( Rva005EB7B0, V3Vt0110F97C )
V3_HEAD_COPY_CTOR_2( Rva005ED310, V3Vt0110F9CC )
V3_HEAD_COPY_CTOR_2( Rva005ED8B0, V3Vt0110F9AC )

V3_HEAD_COPY_CTOR_3( Rva005EC230, V3Vt01110898, V3Vt0110F978 )
V3_HEAD_COPY_CTOR_3( Rva005EC4C0, V3Vt0111081C, V3Vt01073760 )
V3_HEAD_COPY_CTOR_3( Rva005EC730, V3Vt0111082C, V3Vt0110F9E4 )
V3_HEAD_COPY_CTOR_3( Rva005EC930, V3Vt0111089C, V3Vt0110F9E8 )
V3_HEAD_COPY_CTOR_3( Rva005ECB80, V3Vt01110834, V3Vt0110FA14 )
V3_HEAD_COPY_CTOR_3( Rva005ECE20, V3Vt01110830, V3Vt0107375C )
