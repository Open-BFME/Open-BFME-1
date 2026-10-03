// Open-BFME5: retail RVA 0x00618740, 111 bytes.
//
// This is the byte-identical sibling of the matched 0x006187D0
// Rva00618600Poly operation.  The two bodies have the same ECX/ret-4 ABI,
// state/source gate, state-location virtual call, and message construction.
// This sibling's proven state field is at +0x1c (the matched 0x006187D0
// sibling has its corresponding field at +0x20), so it is kept in its own
// address-derived member view.  The destructor at 0x00618600 and constructor
// at 0x00618890 establish the Rva00618600Poly owner and vtable boundary.

// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	float x;
	float y;
	float z;
};

// Retail's own call here is `call 0x00014858` (?j_00014858@@YAXXZ, defined in
// game/gen_small/thunks_009.cpp), whose body is the 5-byte
// ?dup_0060d5a0@@YAXXZ at 0x0060D5A0 (`mov al,1; ret 4`).  Nothing defines a
// BfmeGameCW method at that address, so the call is named by the ledger's ILT
// stub and reached through the usual thiscall union cast.
extern void j_00014858();

// The singleton receiver view; only the gate call is made on it.
class BfmeGameCW
{
public:
	char m_bfmeHead[0x288];
	Bool m_bfmeOver;
};

// 0x012F706C is retail's `LivingWorldManager *TheLivingWorldManager`
// (?TheLivingWorldManager@@3PAVLivingWorldManager@@A, defined in
// game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldManager.cpp); the
// BfmeGameCW view is reached from it by reinterpret_cast, the convention
// Rva006FD090Projection.cpp already uses.
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

class BfmeStateDF
{
public:
	virtual ~BfmeStateDF();
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0C(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1C(void) = 0;
	virtual void buildFramePoint(void *source, Coord3D *point) = 0;
};

// Retail global at 0x012F7048 is Rva006092D0State *
// g_rva012F7048LivingWorld (defined once in LivingWorld.cpp).  This TU calls it
// through the local BfmeStateDF view, so the view stays and the global uses the
// canonical spelling.
class Rva006092D0State;
extern Rva006092D0State *g_rva012F7048LivingWorld;

static inline BfmeStateDF *localGlo012F7048(void)
{
	return reinterpret_cast<BfmeStateDF *>(g_rva012F7048LivingWorld);
}

struct BfmeSubENE;

// The type-6 helper this body calls is already matched at RVA 0x0008AC10 as
// ?bfmeGoENE@BfmeThingENE@@QAEPAUBfmeSubENE@@PAX@Z; declare it under that
// owner so the call resolves at link time.
struct BfmeThingENE
{
	BfmeSubENE *bfmeGoENE(void *opaqueBits);
};

class GameMessage
{
public:
	virtual ~GameMessage();
	void appendLocationArgument(const Coord3D &arg);

private:
	GameMessage *m_next;
	GameMessage *m_prev;
	void *m_list;
	int m_type;
	int m_playerIndex;
	unsigned char m_argCount;
	unsigned char m_padding[3];
	void *m_argList;
	void *m_argTail;
};

class MessageStream
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0C(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1C(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot2C(void) = 0;
	virtual void slot30(void) = 0;
	virtual GameMessage *appendMessage(UnsignedInt type) = 0;
};

extern MessageStream *TheMessageStream;

class Rva00618600Poly
{
public:
	virtual ~Rva00618600Poly();
	Bool rva00618740(UnsignedInt source);

private:
	unsigned char m_unmodelled04[4];
	void *m_source;
	unsigned char m_unmodelled0c[0x10];
	int m_state;
};

// ?rva00618740@Rva00618600Poly@@QAE_NI@Z
Bool Rva00618600Poly::rva00618740(UnsignedInt source)
{
	UnsignedInt sourceArg = source;
	union { void (*plain)(void); Bool (BfmeGameCW::*gate)(UnsignedInt); } gateCall;
	gateCall.plain = j_00014858;
	if (m_state != 5 || !(reinterpret_cast<BfmeGameCW *>(TheLivingWorldManager)->*gateCall.gate)(sourceArg))
		return false;

	Coord3D location;
	localGlo012F7048()->buildFramePoint(reinterpret_cast<void *>(sourceArg), &location);
	GameMessage *message = TheMessageStream->appendMessage(1103);
	reinterpret_cast<BfmeThingENE *>(message)->bfmeGoENE(m_source);
	message->appendLocationArgument(location);
	return true;
}
