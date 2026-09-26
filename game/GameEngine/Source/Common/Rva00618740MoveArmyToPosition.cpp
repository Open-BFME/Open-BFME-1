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

class BfmeGameCW
{
public:
	char m_bfmeHead[0x288];
	Bool m_bfmeOver;
	Bool rva0060d5a0(UnsignedInt source);
};

extern BfmeGameCW *g_bfmeGameCW;

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
	if (m_state != 5 || !g_bfmeGameCW->rva0060d5a0(sourceArg))
		return false;

	Coord3D location;
	g_bfmeStateDF->buildFramePoint(reinterpret_cast<void *>(sourceArg), &location);
	GameMessage *message = TheMessageStream->appendMessage(1103);
	message->rva0008ac10(m_source);
	message->appendLocationArgument(location);
	return true;
}
