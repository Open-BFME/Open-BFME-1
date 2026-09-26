// cl: /EHsc
//
// Nine 106-byte virtual destructors that shut down and delete one owned
// pointer held at +0x24, then run a shared polymorphic base destructor:
//
//     mov [esi],<VFTABLE>                 (this class's vptr)
//     mov ecx,[esi+0x24] / test / je skip
//         mov eax,[ecx] / call [eax+0x3c]         ( ->shutdown() )
//         mov ecx,[esi+0x24] / test / je          ( delete's own null test )
//         mov edx,[ecx] / push 1 / call [edx]     ( scalar deleting dtor )
//         mov [esi+0x24],0
//   skip: mov ecx,esi / call <BASE DTOR at 0x000A1B30>
//
// WHAT THE BYTES SHOW.  The SECOND load of [esi+0x24] with its own null test is
// not written in the source -- it is `delete p` reloading the operand and
// applying the language's null guard, and it is why the pointer has to be
// re-read after the virtual call.  `push 1 / call [edx]` through vtable slot 0
// is MSVC's scalar deleting destructor with the "also free" flag: that spells
// `delete`, not a plain destructor call.  `call [eax+0x3c]` is slot 15 of the
// same vtable, entered with no arguments and no caller pop, so the pointee has
// a virtual destructor declared FIRST (it owns slot 0) and at least fifteen
// more virtuals.  Fourteen filler slots stand between them here purely to put
// `shutdown` at 0x3c; they are spacers, not fourteen recovered methods.
//
// THE OFFSET-0 CALLEE IS A POLYMORPHIC PRIMARY BASE, and unlike the sibling
// family in Q4PairSubobjectDtors.cpp the bytes force that reading: this
// destructor opens with a vptr store at [esi]+0, so offset 0 is the vptr slot
// and no MEMBER can live there.  0x000A1B30 receives ecx = this + 0, so it is
// a base sharing that slot.  0x000A1B30 stores a vptr of its own, so the base
// is polymorphic; vtable slot 0 of each retail vftable here holds a scalar
// deleting destructor that calls this body, so THIS destructor is virtual.
//
// ONE FIELD VARIES AND IT IS NOT EVIDENCE.  The nine bodies differ in exactly
// one dword: the vftable address stored at [esi].  That is a DIR32 operand,
// which build.py resolves by copying retail's four bytes, so it proves nothing
// on its own -- but it does force the data model.  NINE DISTINCT VFTABLE
// ADDRESSES AT THE SAME SITE MEANS NINE DISTINCT CLASSES; declaring one class
// nine times would gate green and be wrong, and would fail
// verify_dir32_consistency, which is the only thing that would catch it.  The
// base destructor's REL32 is identical in all nine, and that IS evidence: they
// really do share one base.
//
// The owned pointee is spelled as ONE type across all nine because nothing
// distinguishes them -- same offset, same slot, no relocation of its own.  That
// asserts less than minting nine unrelated pointee types, but it is a choice,
// not a finding: the bytes are equally consistent with nine.
//
// IDENTITY IS NOT RECOVERED.  Every name is address-derived; 0x000A1B30 is
// unnamed in the ledger and is pinned here under an address-derived alias.
// What the bytes cannot decide: the real class names, what `shutdown` is, the
// size of any class here (m_gap only places the pointer at +0x24), and whether
// anything else lives between the base and the pointer.

class Callee00171DB0
{
public:
	virtual ~Callee00171DB0();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void shutdown();
};

class Base000A1B30
{
public:
	virtual ~Base000A1B30();
};

#define Q4_OWNED_PTR_DTOR( NAME )                                         \
	class NAME : public Base000A1B30                                      \
	{                                                                     \
	public:                                                               \
		virtual ~NAME();                                                  \
		char m_gap[ 0x24 - 4 ];                                           \
		Callee00171DB0 *m_owned;                                          \
	};                                                                    \
	NAME::~NAME()                                                         \
	{                                                                     \
		if( m_owned )                                                     \
		{                                                                 \
			m_owned->shutdown();                                          \
			delete m_owned;                                               \
			m_owned = 0;                                                  \
		}                                                                 \
	}

Q4_OWNED_PTR_DTOR( Rva00171DB0 )
Q4_OWNED_PTR_DTOR( Rva0017D1F0 )
Q4_OWNED_PTR_DTOR( Rva0017D7A0 )
Q4_OWNED_PTR_DTOR( Rva0017D830 )
Q4_OWNED_PTR_DTOR( Rva0017E060 )
Q4_OWNED_PTR_DTOR( Rva0017E160 )
Q4_OWNED_PTR_DTOR( Rva0017E2F0 )
Q4_OWNED_PTR_DTOR( Rva0017E3F0 )
Q4_OWNED_PTR_DTOR( Rva0017E870 )
