// cl: /DNDEBUG /MD /EHsc
//
// Short __thiscall bodies that end in a tail jump through an ILT entry. Each
// was claimed only as its final 5-byte jmp by a generated thunk row; the ILT
// entry for the body lands on its first instruction (see
// targets/game/reverse/identity_evidence/ilt-tail-misanchored-offset-heads.md).
// The jump targets are spelled by the ILT symbol the REL32 names, called as a
// __thiscall member; the bodies behind them already carry other ledger names.
// Owners and fields are address-derived: no identity is claimed.

class BfmeIltTailReceiver {};
typedef void ( BfmeIltTailReceiver::*BfmeIltTailMember0 )();
typedef BfmeIltTailReceiver *( BfmeIltTailReceiver::*BfmeIltTailGetter )();

#define BFME_ILT_MEMBER( TYPE, ILT, VAR )                                  \
	union { void ( *raw )(); TYPE member; } VAR;                          \
	VAR.raw = ILT

void j_00027f2a(); void j_0001e344();
void j_00020824(); void j_00027746(); void j_000456e2();

// mov ecx,[ecx+0x2AC] / jmp ILT 0x00027F2A
class Rva00505780
{
public:
	void invoke();
	char m_padding[0x2ac];
	BfmeIltTailReceiver *m_target;
};
void Rva00505780::invoke()
{
	BFME_ILT_MEMBER( BfmeIltTailMember0, j_00027f2a, target );
	( m_target->*target.member )();
}

// mov ecx,[ecx+0x24C] / jmp ILT 0x0001E344
class Rva007AF700
{
public:
	void invoke();
	char m_padding[0x24c];
	BfmeIltTailReceiver *m_target;
};
void Rva007AF700::invoke()
{
	BFME_ILT_MEMBER( BfmeIltTailMember0, j_0001e344, target );
	( m_target->*target.member )();
}

// fld [ecx+0x18C] / jmp __ftol2: the float field truncated to int.
class Rva0026E460
{
public:
	int invoke();
	char m_padding[0x18c];
	float m_value;
};
int Rva0026E460::invoke()
{
	return (int)m_value;
}

// The owner pointer sits 0x18 bytes before `this`; ILT 0x00020824 returns an
// object whose +0x22C pointer receives the tail call.
struct Rva0022F110Object
{
	char m_padding[0x22c];
	BfmeIltTailReceiver *m_target;
};
static __forceinline Rva0022F110Object *ownerObject0022F110( void *self )
{
	BfmeIltTailReceiver *owner = *(BfmeIltTailReceiver **)( (char *)self - 0x18 );
	BFME_ILT_MEMBER( BfmeIltTailGetter, j_00020824, get );
	return (Rva0022F110Object *)( owner->*get.member )();
}
class Rva0022F110
{
public:
	void invoke();
};
void Rva0022F110::invoke()
{
	BFME_ILT_MEMBER( BfmeIltTailMember0, j_00027746, target );
	( ownerObject0022F110( this )->m_target->*target.member )();
}
class Rva0022F2C0
{
public:
	void invoke();
};
void Rva0022F2C0::invoke()
{
	BFME_ILT_MEMBER( BfmeIltTailMember0, j_000456e2, target );
	( ownerObject0022F110( this )->m_target->*target.member )();
}
