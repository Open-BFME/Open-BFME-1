// Twenty-two tiny bodies that read ONE dword (or byte) out of an object or out
// of a global, test it, and -- only when it is non-zero -- leave through a tail
// `jmp`:
//
//     mov <reg>,<slot> / test <reg>,<reg> / jz .out / jmp <REL32> / .out: ret
//
// WHAT THE BYTES SHOW.  The `jz` always lands exactly on the trailing `ret`, so
// nothing follows the guarded call: the whole body is one `if`.  Control leaves
// through a `jmp`, so the callee's `ret` returns to OUR caller and its stack pop
// is this function's -- a bare `ret` at the callee makes both sides take no
// stack arguments.  Arity is therefore invisible across the jump and is not
// asserted here.
//
// THE REGISTER SPLITS THE FAMILY IN TWO, and that is the whole finding: the
// mnemonic sequence mov/test/jz/jmp/ret put all twenty-two together, but they
// are not one shape.
//
//   * `mov ecx,...` -- the loaded dword BECOMES the receiver.  It is a stored
//     pointer and the callee is a __thiscall member of what it points at.
//   * `mov eax,...` / `mov al,...` -- the loaded value is only TESTED.  eax is
//     dead across the jump, so the callee receives it nowhere: it is a plain
//     flag guarding a call to a free function.  A byte-sized load (`mov al`)
//     proves the flag is one byte wide; a dword load proves it is not.
//
// A third spelling appears once, at 0x005376D0: `test dword ptr [ecx+8],eax`
// tests TWO members against each other, which is an `&` of two fields, not a
// null check.
//
// The receiver/flag is held either in the object (`mov ecx,[ecx+K]`) or in a
// global (`mov ecx,ds:[G]`).  A global spelling touches no `this` at all, so
// those rows are free functions here; nothing in the bytes says otherwise.
//
// IDENTITY IS NOT RECOVERED, except where the ledger already names the body the
// REL32 reaches -- PartitionData::makeDirty, ControlBarScheme::update,
// BFMEConnectionManager::sendLoadCompleteCommand, TextureClass::Release_Ref and
// five `d_`-named free bodies are the real symbols at those addresses and need
// no pin.  Every other name here is derived from an address: `RvaXXXXXXXX` for a
// row, `GenXXXXXXXX` for a callee's class, `GloXXXXXXXX` for a global's type.
// The callee pins are address-derived and additive.
//
// TWO ROWS SHARE ONE GLOBAL.  0x00514D60 and 0x00514D80 both read the pointer at
// 0x012F4988 and jump to DIFFERENT callees, so that address gets ONE type with
// TWO members rather than two types at one address.

// ---------------------------------------------------------------- shape (a)
// member-held pointer, __thiscall callee

#define BFME_GUARDED_CALLEE( ADDR )                                       \
	class Gen##ADDR                                                       \
	{                                                                     \
	public:                                                               \
		void handle();                                                    \
	};

#define BFME_GUARDED_MEMBER_CALL( NAME, CALLEE, OFFSET )                  \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void go();                                                        \
		char m_lead[ OFFSET ];                                            \
		CALLEE *m_receiver;                                               \
	};                                                                    \
	void NAME::go()                                                       \
	{                                                                     \
		if( m_receiver )                                                  \
			m_receiver->handle();                                         \
	}

#define BFME_GUARDED_MEMBER_CALL_HEAD( NAME, CALLEE )                     \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void go();                                                        \
		CALLEE *m_receiver;                                               \
	};                                                                    \
	void NAME::go()                                                       \
	{                                                                     \
		if( m_receiver )                                                  \
			m_receiver->handle();                                         \
	}

#define BFME_GUARDED_MEMBER_DTOR_HEAD( NAME, CALLEE )                    \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		~NAME();                                                           \
		CALLEE *m_receiver;                                                \
	};                                                                    \
	NAME::~NAME()                                                         \
	{                                                                     \
		if( m_receiver )                                                   \
			m_receiver->handle();                                            \
	}

// Callees the ledger already names.
class PartitionData { public: void makeDirty(); };
class ControlBarScheme { public: void update(); };
class BFMEConnectionManager { public: void sendLoadCompleteCommand(); };
class TextureClass { public: void Release_Ref(); };

BFME_GUARDED_CALLEE( 003C7570 )
BFME_GUARDED_CALLEE( 0060CF20 )
BFME_GUARDED_CALLEE( 0060CBB0 )
BFME_GUARDED_CALLEE( 00663230 )
BFME_GUARDED_CALLEE( 006BA220 )
BFME_GUARDED_CALLEE( 006DEB70 )

class Rva001BF380 { public: void go(); char m_lead[ 0x3b0 ]; PartitionData *m_receiver; };
void Rva001BF380::go() { if( m_receiver ) m_receiver->makeDirty(); }

class Rva004AD970 { public: void go(); ControlBarScheme *m_receiver; };
void Rva004AD970::go() { if( m_receiver ) m_receiver->update(); }

class Rva00681A80 { public: void go(); char m_lead[ 8 ]; BFMEConnectionManager *m_receiver; };
void Rva00681A80::go() { if( m_receiver ) m_receiver->sendLoadCompleteCommand(); }

class Rva007D2340 { public: void go(); char m_lead[ 8 ]; TextureClass *m_receiver; };
void Rva007D2340::go() { if( m_receiver ) m_receiver->Release_Ref(); }

BFME_GUARDED_MEMBER_CALL( Rva003BCA20, Gen003C7570, 0x28 )
BFME_GUARDED_MEMBER_CALL( Rva0060D5E0, Gen0060CF20, 0x28c )
BFME_GUARDED_MEMBER_CALL( Rva0060D620, Gen0060CBB0, 0x28c )
BFME_GUARDED_MEMBER_CALL( Rva006819B0, Gen00663230, 8 )
BFME_GUARDED_MEMBER_DTOR_HEAD( Rva00690FF0Handle, Gen006BA220 )
BFME_GUARDED_MEMBER_DTOR_HEAD( Rva006910F0Handle, Gen006BA220 )
BFME_GUARDED_MEMBER_CALL( Rva006C8BE0, Gen006DEB70, 0x30b4 )

// ---------------------------------------------------------------- shape (b)
// global-held pointer, __thiscall callee

#define BFME_GUARDED_GLOBAL_CALL( NAME, CALLEE, GLOBAL )                  \
	extern CALLEE *GLOBAL;                                                \
	void NAME()                                                           \
	{                                                                     \
		if( GLOBAL )                                                      \
			GLOBAL->handle();                                             \
	}

BFME_GUARDED_CALLEE( 005847F0 )
BFME_GUARDED_CALLEE( 0072F080 )
BFME_GUARDED_CALLEE( 00754850 )

// The pointer at 0x012F3330 is also read by 0x00382960 (see
// R1GuardedReleaseHelpers.cpp), which calls a DIFFERENT member of it, so this
// address gets one type with two members.
class Glo00EF3330
{
public:
	void h00489410();
	void h004893E0();
};
extern Glo00EF3330 *g_Glo00EF3330;
void Rva00382980() { if( g_Glo00EF3330 ) g_Glo00EF3330->h00489410(); }

BFME_GUARDED_GLOBAL_CALL( Rva0050D3B0, Gen005847F0, g_Glo00EF4B70 )
BFME_GUARDED_GLOBAL_CALL( Rva00730FE0, Gen0072F080, g_Glo00EF9D98 )
BFME_GUARDED_GLOBAL_CALL( Rva00754A10, Gen00754850, g_Glo00F04B64 )

class Glo00EF4988
{
public:
	void h005143D0();
	void h00514560();
};
extern Glo00EF4988 *g_Glo00EF4988;
void Rva00514D60() { if( g_Glo00EF4988 ) g_Glo00EF4988->h005143D0(); }
void Rva00514D80() { if( g_Glo00EF4988 ) g_Glo00EF4988->h00514560(); }

// ---------------------------------------------------------------- shape (c/d)
// flag guard, free callee.  The five callees keep their ledger names.

void d_003f9140();
void d_0076cb10();
void d_00609710();
void registerAptLivingWorldUICallbacks();
void d_0083e8f0();

class Rva003D5780 { public: void go(); char m_lead[ 0x10 ]; int m_flag; };
void Rva003D5780::go() { if( m_flag ) d_003f9140(); }

class Rva0076EFE0 { public: void go(); char m_lead[ 0x34 ]; int m_flag; };
void Rva0076EFE0::go() { if( m_flag ) d_0076cb10(); }

class Rva00609850 { public: void go(); char m_lead[ 0x60 ]; bool m_flag; };
void Rva00609850::go() { if( m_flag ) d_00609710(); }

// 0x0046B3B0 (see R1ForwardToStoredObject.cpp) calls a __thiscall member
// through this same global, so it is typed as a pointer here rather than as a
// plain int flag; the test compiles identically either way and the pointer
// spelling is the one the other reader forces.
class Glo00EF19E8
{
public:
	void h0046B2B0( int value );
};
extern Glo00EF19E8 *g_Glo00EF19E8;
void Rva00584E20() { if( g_Glo00EF19E8 ) registerAptLivingWorldUICallbacks(); }

// ---------------------------------------------------------------- shape (f)
// two members ANDed together, free callee

class Rva005376D0
{
public:
	void go();
	char m_lead[ 8 ];
	int m_mask;
	char m_mid[ 8 ];
	int m_bits;
};
void Rva005376D0::go() { if( m_mask & m_bits ) d_0083e8f0(); }
