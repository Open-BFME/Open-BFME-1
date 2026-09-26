// Open-BFME5: retail RVA 0x006187D0, 111 bytes.
//
// The constructor at 0x00618890 installs vtable 0x01116D64.  Its two
// destructor slots are already carried by the address-derived
// Rva00618600Poly owner, but no public BFME class/method spelling has been
// recovered for this slot.  Keep that neutral owner while expressing the
// observed data and calls in C++.
//
// The routine accepts one opaque four-byte source value.  It runs only for
// state 5, asks the data-bearing BfmeGameCW singleton whether the source is
// usable, obtains a location through BfmeStateDF's +0x20 virtual slot, and
// appends message 1103 with two existing GameMessage argument helpers.  The
// source's semantic identity (object pointer versus ID) is intentionally not
// asserted here.

// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	float x;
	float y;
	float z;
};

// The +0x288 flag is independently read by the matched
// Gen_00609320::bfmeDisabled body.  The method name is an address-derived
// direct-body view; retail ILT 0x00014858 reaches RVA 0x0060D5A0.
class BfmeGameCW
{
public:
	char m_bfmeHead[0x288];
	Bool m_bfmeOver;
	Bool rva0060d5a0(UnsignedInt source);
};

extern BfmeGameCW *g_bfmeGameCW;

// Existing matched layout: the destructor occupies vslot 0, and
// buildFramePoint is vslot 8 (+0x20).  The source argument remains opaque.
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

extern "C" BfmeStateDF *g_bfmeStateDF;

// This is the data-bearing BFME GameMessage view used by the matched
// message-stream and command-list TUs: vptr +0, list links at +4/+8, list,
// type and player fields at +0xC/+0x10/+0x14, and argument state at
// +0x18..+0x23.  The type-6 helper's public owner is not recovered, so its
// already matched 22-byte body is exposed through this neutral method name.
struct BfmeSubENE;

class GameMessage
{
public:
	virtual ~GameMessage();
	BfmeSubENE *rva0008ac10(void *opaqueBits);
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
	Bool rva006187d0(UnsignedInt source);

private:
	unsigned char m_unmodelled04[4];
	void *m_source;
	unsigned char m_unmodelled0c[0x14];
	int m_state;
};

// ?rva006187d0@Rva00618600Poly@@QAE_NI@Z
Bool Rva00618600Poly::rva006187d0(UnsignedInt source)
{
	UnsignedInt sourceArg = source;
	if (m_state != 5 || !g_bfmeGameCW->rva0060d5a0(sourceArg))
		goto failure;

	Coord3D location;
	g_bfmeStateDF->buildFramePoint(reinterpret_cast<void *>(sourceArg), &location);
	GameMessage *message = TheMessageStream->appendMessage(1103);
	message->rva0008ac10(m_source);
	message->appendLocationArgument(location);
	return true;

failure:
	return false;
}
