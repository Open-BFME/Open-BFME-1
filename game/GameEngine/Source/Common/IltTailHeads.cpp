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

// The bodies below never reach an ILT tail jump, but their later instructions
// had been claimed as separate functions at addresses nothing enters.

// Lowers the +0x3C float to the argument when the argument is smaller.
class Rva001B49A0
{
public:
	void invoke( float value );
	char m_padding[0x3c];
	float m_value;
};
void Rva001B49A0::invoke( float value )
{
	if ( m_value > value )
		m_value = value;
}

// Copies the Coord3D argument to +0x14 only when the +0x00 tag is 0x10.
struct Rva0034FF20Coord
{
	float x, y, z;
};
class Rva0034FF20
{
public:
	void invoke( const Rva0034FF20Coord *coord );
	int m_tag;
	char m_padding[0x10];
	Rva0034FF20Coord m_coord;
};
void Rva0034FF20::invoke( const Rva0034FF20Coord *coord )
{
	if ( m_tag == 0x10 )
		m_coord = *coord;
}

// A __thiscall member that ignores `this`: forwards its argument to the
// virtual at +0xC8 of TheGameSpyInfo, or answers false when there is none.
#define BFME_SLOT( N ) virtual void slot##N();
class Rva00537A10View
{
public:
	BFME_SLOT( 00 ) BFME_SLOT( 01 ) BFME_SLOT( 02 ) BFME_SLOT( 03 ) BFME_SLOT( 04 )
	BFME_SLOT( 05 ) BFME_SLOT( 06 ) BFME_SLOT( 07 ) BFME_SLOT( 08 ) BFME_SLOT( 09 )
	BFME_SLOT( 10 ) BFME_SLOT( 11 ) BFME_SLOT( 12 ) BFME_SLOT( 13 ) BFME_SLOT( 14 )
	BFME_SLOT( 15 ) BFME_SLOT( 16 ) BFME_SLOT( 17 ) BFME_SLOT( 18 ) BFME_SLOT( 19 )
	BFME_SLOT( 20 ) BFME_SLOT( 21 ) BFME_SLOT( 22 ) BFME_SLOT( 23 ) BFME_SLOT( 24 )
	BFME_SLOT( 25 ) BFME_SLOT( 26 ) BFME_SLOT( 27 ) BFME_SLOT( 28 ) BFME_SLOT( 29 )
	BFME_SLOT( 30 ) BFME_SLOT( 31 ) BFME_SLOT( 32 ) BFME_SLOT( 33 ) BFME_SLOT( 34 )
	BFME_SLOT( 35 ) BFME_SLOT( 36 ) BFME_SLOT( 37 ) BFME_SLOT( 38 ) BFME_SLOT( 39 )
	BFME_SLOT( 40 ) BFME_SLOT( 41 ) BFME_SLOT( 42 ) BFME_SLOT( 43 ) BFME_SLOT( 44 )
	BFME_SLOT( 45 ) BFME_SLOT( 46 ) BFME_SLOT( 47 ) BFME_SLOT( 48 ) BFME_SLOT( 49 )
	virtual bool slotC8( void *argument );
};
#undef BFME_SLOT
class GameSpyInfo;
extern GameSpyInfo *TheGameSpyInfo;
class Rva00537A10
{
public:
	bool invoke( void *argument );
};
bool Rva00537A10::invoke( void *argument )
{
	Rva00537A10View *info = (Rva00537A10View *)TheGameSpyInfo;
	if ( info )
		return info->slotC8( argument );
	return false;
}

// Deletes the polymorphic object held at +0x00 through its virtual
// destructor (slot 0, flag 1).
class Rva005BE810Object
{
public:
	virtual ~Rva005BE810Object();
};
class Rva005BE810
{
public:
	void invoke();
	Rva005BE810Object *m_object;
};
void Rva005BE810::invoke()
{
	delete m_object;
}
