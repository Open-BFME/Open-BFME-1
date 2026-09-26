// Seventeen guarded bodies whose surviving path leaves through a REL32 -- the
// half of the mnemonic-only families anchored at 0x000C9580 and 0x0007C530
// that the byte comparison cannot settle on its own, because four of every
// body's bytes are the branch displacement.  Every callee here is pinned by
// ADDRESS in targets/game/reverse/symbols.csv under an address-derived name; twelve of the
// thirteen distinct targets are five-byte ILT entries, which is what the REL32
// actually encodes and therefore what is pinned.
//
// (A) EIGHT GUARDED TAIL CALLS ON A HELD POINTER (family 0x000C9580):
//
//     mov ecx,[ecx+<OFF>] / test ecx,ecx / je zero / jmp <REL32>
//     zero: xor eax,eax / ret      (or xor al,al)
//
// ecx is REPLACED by a pointer read out of the object and control leaves
// through `jmp`, so the callee's `ret` is this function's: both sides are
// __thiscall with no stack arguments and THE CALLEE'S RESULT IS THIS
// FUNCTION'S RESULT.  The zero arm decides the width -- `xor al,al` for two of
// the eight, `xor eax,eax` for six -- and the callee is declared to match.
// One member (0x006E17A0) reads its receiver from a GLOBAL rather than from
// `this`; it is otherwise identical.
//
// TWO OF THE PINS ARE CORROBORATED BY THE LEDGER.  0x0002162A and 0x000374B1
// forward to ILT entries whose ultimate targets are already-matched
// __thiscall accessors returning a four-byte value and taking no arguments,
// which is exactly the shape asserted here.  The rest are unnamed.
//
// (B) FIVE GUARDED CALLS ON A SECOND GLOBAL (family 0x0007C530):
//
//     mov eax,[<GUARD>] / test eax,eax / je out
//     mov ecx,[0x012F19E8] / jmp <REL32> / out: ret
//
// THE TESTED VALUE IS NOT THE RECEIVER.  eax holds a global that is only
// tested; ecx is loaded from a DIFFERENT global and that is what the callee
// gets.  Five distinct guard globals, one receiver, one callee.  Nothing is
// returned: the guarded path falls to a bare `ret` with no value materialised.
//
// (C) TWO GUARDED FORWARDS TO A HELD RECEIVER (0x00730CF0, 0x00730D10):
//
//     mov eax,[ecx+0x18] / test eax,eax / je out / mov ecx,[ecx+0x10]
//     jmp <REL32> / out: ret
//
// Again the tested field and the receiver are DIFFERENT fields of the same
// object.  The two differ only in callee.
//
// (D) ONE CLEAR-THEN-CALL (0x00417240):
//
//     mov al,[ecx+0x3AC] / test al,al / je out
//     mov byte ptr [ecx+0x3AC],0 / jmp <REL32> / out: ret
//
// ecx is NEVER TOUCHED before the jump, so the callee's `this` is this object:
// the target is a non-virtual member of the same class, and the flag it tests
// is cleared first.
//
// (E) ONE GUARDED RELEASE THROUGH A GLOBAL (0x006FCE10):
//
//     push esi / mov esi,ecx / mov eax,[esi+0x148] / test eax,eax / je out
//     mov ecx,[0x01306EEC] / push eax / call <REL32>
//     mov [esi+0x148],0 / out: pop esi / ret
//
// A __thiscall call, not a tail jump: the receiver comes from a global and the
// owned pointer is the single stack argument.  The `je` lands PAST the store of
// 0, so the clear is inside the source's own `if`.
//
// IDENTITY IS NOT RECOVERED.  Every class, member and extern name here is
// derived from an address, and so is every pin.

// ---------------------------------------------------------------------------
// (A)

#define R2_TAIL_CALLEE( ADDR, TYPE )                                      \
	class Gen##ADDR                                                       \
	{                                                                     \
	public:                                                               \
		TYPE handle();                                                    \
	};

#define R2_GUARDED_TAIL_CALL( NAME, OFF, CALLEE, TYPE )                   \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		char m_leading[ OFF ];                                            \
		CALLEE *m_receiver;                                               \
		TYPE call();                                                      \
	};                                                                    \
	TYPE NAME::call()                                                     \
	{                                                                     \
		if ( m_receiver )                                                 \
		{                                                                 \
			return m_receiver->handle();                                  \
		}                                                                 \
		return 0;                                                         \
	}

R2_TAIL_CALLEE( 0003C542, bool )
R2_TAIL_CALLEE( 00046AA6, int )
R2_TAIL_CALLEE( 0002162A, int )
R2_TAIL_CALLEE( 000374B1, int )
R2_TAIL_CALLEE( 00049FDA, bool )
R2_TAIL_CALLEE( 009794F0, int )
R2_TAIL_CALLEE( 0092C4B0, int )
R2_TAIL_CALLEE( 00980B60, int )

R2_GUARDED_TAIL_CALL( Rva000C9580, 0x220, Gen0003C542, bool )
R2_GUARDED_TAIL_CALL( Rva001BE3D0, 0x1EC, Gen00046AA6, int )
R2_GUARDED_TAIL_CALL( Rva006819E0, 0x08, Gen0002162A, int )
R2_GUARDED_TAIL_CALL( Rva00681B40, 0x08, Gen000374B1, int )
R2_GUARDED_TAIL_CALL( Rva00970690, 0x14, Gen009794F0, int )
R2_GUARDED_TAIL_CALL( Rva00970BE0, 0x14, Gen0092C4B0, int )
R2_GUARDED_TAIL_CALL( Rva00971B50, 0x14, Gen00980B60, int )

extern Gen00049FDA *R2Ptr012F0FE0;
bool Rva006E17A0()
{
	if ( R2Ptr012F0FE0 )
	{
		return R2Ptr012F0FE0->handle();
	}
	return false;
}

// ---------------------------------------------------------------------------
// (B)

class Gen000290D2
{
public:
	void handle();
};
extern Gen000290D2 *R2Ptr012F19E8;

#define R2_GUARDED_GLOBAL_FORWARD( NAME, GUARD )                          \
	extern void *GUARD;                                                   \
	void NAME()                                                           \
	{                                                                     \
		if ( GUARD )                                                      \
		{                                                                 \
			R2Ptr012F19E8->handle();                                       \
		}                                                                 \
	}

R2_GUARDED_GLOBAL_FORWARD( Rva0050D910, R2Glob012F495C )
R2_GUARDED_GLOBAL_FORWARD( Rva00516690, R2Glob012F4998 )
R2_GUARDED_GLOBAL_FORWARD( Rva0055BD40, R2Glob012F4ACC )
R2_GUARDED_GLOBAL_FORWARD( Rva0056A810, R2Glob012F4B44 )
R2_GUARDED_GLOBAL_FORWARD( Rva00579040, R2Glob012F4B54 )

// ---------------------------------------------------------------------------
// (C)

#define R2_GUARDED_FIELD_FORWARD( NAME, CALLEE )                          \
	class CALLEE                                                          \
	{                                                                     \
	public:                                                               \
		void handle();                                                    \
	};                                                                    \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		char m_leading[ 0x10 ];                                           \
		CALLEE *m_receiver;                                               \
		char m_padding[ 4 ];                                              \
		void *m_guard;                                                    \
		void run();                                                       \
	};                                                                    \
	void NAME::run()                                                      \
	{                                                                     \
		if ( m_guard )                                                    \
		{                                                                 \
			m_receiver->handle();                                         \
		}                                                                 \
	}

R2_GUARDED_FIELD_FORWARD( Rva00730CF0, Gen00010CF3 )
R2_GUARDED_FIELD_FORWARD( Rva00730D10, Gen0001D697 )

// ---------------------------------------------------------------------------
// (D)

class R2RelationResult
{
public:
	#define R2_RELATION_SLOT(n) virtual void slot##n();
	R2_RELATION_SLOT(00) R2_RELATION_SLOT(01) R2_RELATION_SLOT(02) R2_RELATION_SLOT(03)
	R2_RELATION_SLOT(04) R2_RELATION_SLOT(05) R2_RELATION_SLOT(06) R2_RELATION_SLOT(07)
	R2_RELATION_SLOT(08) R2_RELATION_SLOT(09) R2_RELATION_SLOT(10) R2_RELATION_SLOT(11)
	R2_RELATION_SLOT(12) R2_RELATION_SLOT(13) R2_RELATION_SLOT(14) R2_RELATION_SLOT(15)
	R2_RELATION_SLOT(16) R2_RELATION_SLOT(17) R2_RELATION_SLOT(18) R2_RELATION_SLOT(19)
	R2_RELATION_SLOT(20) R2_RELATION_SLOT(21) R2_RELATION_SLOT(22) R2_RELATION_SLOT(23)
	R2_RELATION_SLOT(24) R2_RELATION_SLOT(25) R2_RELATION_SLOT(26) R2_RELATION_SLOT(27)
	R2_RELATION_SLOT(28) R2_RELATION_SLOT(29) R2_RELATION_SLOT(30) R2_RELATION_SLOT(31)
	R2_RELATION_SLOT(32) R2_RELATION_SLOT(33) R2_RELATION_SLOT(34) R2_RELATION_SLOT(35)
	R2_RELATION_SLOT(36) R2_RELATION_SLOT(37) R2_RELATION_SLOT(38) R2_RELATION_SLOT(39)
	R2_RELATION_SLOT(40) R2_RELATION_SLOT(41) R2_RELATION_SLOT(42) R2_RELATION_SLOT(43)
	R2_RELATION_SLOT(44) R2_RELATION_SLOT(45) R2_RELATION_SLOT(46) R2_RELATION_SLOT(47)
	R2_RELATION_SLOT(48) R2_RELATION_SLOT(49) R2_RELATION_SLOT(50) R2_RELATION_SLOT(51)
	#undef R2_RELATION_SLOT
};

class Object
{
public:
	bool isLocallyControlled() const;
	void *unidentified_001BFE20() const;
};

class Rva004141C0
{
public:
	void broadcast();
};

class R2GameClient
{
public:
	unsigned char m_padding[0xB4];
	unsigned int m_r2B4;
};

#define R2TheGameClient (*(R2GameClient **)0x012F1464)

class Rva00417240
{
public:
	char m_leading[ 0xFC ];
	Object *m_object;
	char m_middle[ 0x3AC - 0x100 ];
	bool m_flag;
	void handle();
	void run();
};
void Rva00417240::handle()
{
	Object *object = m_object;
	if (object && object->isLocallyControlled())
	{
		R2TheGameClient->m_r2B4 = 0;
		R2RelationResult *relation = (R2RelationResult *)object->unidentified_001BFE20();
		if (relation)
			relation->slot51();
		else if (object->isLocallyControlled())
			reinterpret_cast<Rva004141C0 *>(this)->broadcast();
	}
}

void Rva00417240::run()
{
	if ( m_flag )
	{
		m_flag = false;
		handle();
	}
}

// ---------------------------------------------------------------------------
// (E)

class Gen0003AC38
{
public:
	void handle( void *victim );
};
extern Gen0003AC38 *R2Ptr01306EEC;

class Rva006FCE10
{
public:
	char m_leading[ 0x148 ];
	void *m_owned;
	void release();
};
void Rva006FCE10::release()
{
	if ( m_owned )
	{
		R2Ptr01306EEC->handle( m_owned );
		m_owned = 0;
	}
}
