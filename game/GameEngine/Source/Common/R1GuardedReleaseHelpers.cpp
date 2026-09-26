// Eight bodies that all open with the same three instructions --
//
//     push esi / mov esi,ecx / mov ecx,<slot> / test ecx,ecx / jz ...
//
// -- and then diverge completely.  Mnemonic grouping put them together; they
// are FOUR different shapes, and the thing that separates them is where the
// `jz` lands and what follows the call.
//
//   * jz over the CALL ONLY, store after it        -> `if (p) p->f(); m_x = ...;`
//   * jz over the call AND the store               -> `if (p) { p->f(); m_x = 0; }`
//   * `call dword ptr [esi+4]` with ecx = [esi]    -> the callee is not a fixed
//     address at all: it is a second dword of the object, invoked with the
//     first dword as its receiver.  That is a pointer-to-member call, and the
//     result is written back over the receiver.
//   * a trailing `mov eax,esi`                     -> the object is the RETURN
//     VALUE.  A __thiscall body that hands `this` back for no other reason is
//     a constructor tail, so that row is spelled as a constructor.
//
// The `jz` distance is the whole evidence for the first two and is one byte
// apart (0x05 vs 0x0B); nothing else in the bytes distinguishes them.
//
// IDENTITY IS NOT RECOVERED, except for TextureClass::Release_Ref, which is the
// ledger's own name for the body one REL32 reaches.  Everything else is named
// from an address, and the callee pins are address-derived and additive.

class TextureClass { public: void Release_Ref(); };

#define BFME_RELEASE_CALLEE( ADDR )                                       \
	class Gen##ADDR                                                       \
	{                                                                     \
	public:                                                               \
		void handle();                                                    \
	};

BFME_RELEASE_CALLEE( 006BA220 )
BFME_RELEASE_CALLEE( 00958BF0 )
BFME_RELEASE_CALLEE( 0089C880 )

// -------------------------------------------------- pointer-to-member call

class GenC9EF0
{
public:
	GenC9EF0 *step();
};

#define BFME_MEMBER_POINTER_STEP( NAME )                                  \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void go();                                                        \
		GenC9EF0 *m_target;                                               \
		GenC9EF0 *( GenC9EF0::*m_step )();                                \
	};                                                                    \
	void NAME::go()                                                       \
	{                                                                     \
		if( m_target )                                                    \
			m_target = ( m_target->*m_step )();                           \
	}

BFME_MEMBER_POINTER_STEP( Rva000C9EF0 )
BFME_MEMBER_POINTER_STEP( Rva00161140 )

// -------------------------------------------------- call, then always clear

#define BFME_CALL_THEN_CLEAR( NAME, CALLEE )                              \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void go();                                                        \
		CALLEE *m_target;                                                 \
	};                                                                    \
	void NAME::go()                                                       \
	{                                                                     \
		if( m_target )                                                    \
			m_target->handle();                                           \
		m_target = 0;                                                     \
	}

BFME_CALL_THEN_CLEAR( Rva00691080, Gen006BA220 )
BFME_CALL_THEN_CLEAR( Rva00691180, Gen006BA220 )

// -------------------------------------------------- call and clear together

class Rva006C07A0
{
public:
	void go();
	TextureClass *m_target;
};
void Rva006C07A0::go()
{
	if( m_target )
	{
		m_target->Release_Ref();
		m_target = 0;
	}
}

class Rva00958C40
{
public:
	void go();
	Gen00958BF0 *m_target;
};
void Rva00958C40::go()
{
	if( m_target )
	{
		m_target->handle();
		m_target = 0;
	}
}

// -------------------------------------------------- call, then always flag

class Rva008A2C60
{
public:
	void go();
	char m_lead[ 0x10 ];
	Gen0089C880 *m_target;
	bool m_done;
};
void Rva008A2C60::go()
{
	if( m_target )
		m_target->handle();
	m_done = true;
}

// -------------------------------------------------- constructor tail

// Same global the guarded tail-jump at 0x00382980 reads; see
// R1GuardedPointerTailCalls.cpp for the shared type.
class Glo00EF3330
{
public:
	void h00489410();
	void h004893E0();
};
extern Glo00EF3330 *g_Glo00EF3330;

class Rva00382960
{
public:
	Rva00382960();
};
Rva00382960::Rva00382960()
{
	if( g_Glo00EF3330 )
		g_Glo00EF3330->h004893E0();
}
