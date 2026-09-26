// cl: /EHs-c-
//
// A FOURTH level of the constructor chain this slice is built out of.  Levels
// one to three are game/GameEngine/Source/Common/T4ForwardingCtorChainL1.cpp,
// L2 and L3 and their leaves are in T4VtableSetCtors.cpp and
// T4PlainFieldCtors.cpp; the same rule puts this row in its own translation
// unit, because MSVC 7.1 inlines a callee defined alongside its caller and
// retail keeps a `call` at every step of the chain.
//
// Retail, 0x00605100 (33 bytes):
//
//     push esi / push edi / mov edi,[esp+0xc] / push edi / mov esi,ecx
//     call 0x00604E90
//     mov [esi],  <VFT>
//     mov eax,[edi+8] / mov [esi+8],eax
//     pop edi / mov eax,esi / pop esi / ret 4
//
// WHAT THE BYTES SHOW.  `mov esi,ecx` ... `mov eax,esi` before `ret 4` is a
// __thiscall returning its receiver: a constructor.  Its single dword argument
// is pushed UNADJUSTED to the callee and then dereferenced at +8, so the
// argument is a pointer to an object that has this same layout -- a copy
// constructor taking its own class by reference, with the base subobject at
// offset 0 so no derived-to-base adjustment is emitted.
//
// THE CALLEE IS ALREADY IN THE LEDGER.  0x00604E90 is
// `??0T4Ctor00604E90@@QAE@ABV0@@Z`, the copy constructor
// T4PlainFieldCtors.cpp landed: a class with a vptr at 0 and one copied dword
// at +4.  Nothing here is fitted to it -- the REL32 resolves there, and the
// field this body copies is at +8, exactly past the end of that base.
//
// ORDER READS OUT THE STRUCTURE.  MSVC 7.1 runs a constructor as base
// subobjects, then vptrs, then members, and does not reorder straight-line
// stores.  The call comes first (the base), the constant store second (this
// class's OWN vftable, overwriting the one the base just installed), and the
// copied dword last (a member of this class, not of the base).  One surviving
// vptr store means one vptr, and it is at offset 0, which is the base's.
//
// IDENTITY IS NOT RECOVERED.  `U4Ctor00605100` is named after its address, and
// the vftable dword is a DIR32 operand copied from retail: it says this class
// differs from its base and nothing more.

// ------------------------------------------------------------- base, declared

// Defined at 0x00604E90 in
// game/GameEngine/Source/Common/T4PlainFieldCtors.cpp; declared and not
// included here so that MSVC cannot inline it, which retail's `call` forbids.
class T4Ctor00604E90
{
public:
	T4Ctor00604E90( const T4Ctor00604E90 &other );
	virtual void s0();
	void *m_field04;
};

// ---------------------------------------------------------------------- row

class U4Ctor00605100 : public T4Ctor00604E90
{
public:
	U4Ctor00605100( const U4Ctor00605100 &other );
	void *m_field08;
};

U4Ctor00605100::U4Ctor00605100( const U4Ctor00605100 &other )
	: T4Ctor00604E90( other ),
	  m_field08( other.m_field08 )
{
}
