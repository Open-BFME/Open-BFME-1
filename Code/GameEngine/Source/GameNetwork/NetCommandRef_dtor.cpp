// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ??0NetCommandRef@@QAE@PAVNetCommandMsg@@@Z: Code/GameEngine/Source/GameNetwork/NetCommandRef.cpp

// NetCommandRef::~NetCommandRef, 0x00676280, 12 bytes.
//
// Connection::doSend runs this on every command it drops -- destructor, then
// operator delete -- so it is one of the callees doSend needs named.
//
// The body is the reference's, and the whole of it: detach the message if there
// is one. Retail tail-jumps into NetCommandMsg::detach (already matched at
// 0x00673610) because that is the last statement and returns void. The
// reference's two DEBUG_ASSERTCRASH lines on m_next/m_prev compile out.
//
// m_msg is at +0, not +4: BFME's NetCommandRef is not a MemoryPoolObject, so it
// carries no vptr and every field sits four bytes lower than the reference
// header puts it. NetCommandList::removeMessage showed the same thing for
// m_next/m_prev at +4/+8.
//
// Declared locally: the real GameNetwork/NetCommandRef.h derives the class from
// MemoryPoolObject, and any file under reference/shims/ forces the full gate.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	void attach();
	void detach();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
public:
	NetCommandRef(NetCommandMsg *msg);
	~NetCommandRef();

private:
	NetCommandMsg *m_msg;							// this+0x00
	NetCommandRef *m_next;							// this+0x04
	NetCommandRef *m_prev;							// this+0x08
	UnsignedByte m_relay;							// this+0x0C
	UnsignedInt m_timeLastSent;						// this+0x10
};

// BFME's one addition to the reference's body: m_relay is zeroed here, between
// the attach and the timestamp. The reference has no relay on the ref at all.
NetCommandRef::NetCommandRef(NetCommandMsg *msg)
{
	m_msg = msg;
	m_next = 0;
	m_prev = 0;
	m_msg->attach();
	m_relay = 0;
	m_timeLastSent = -1;
}

NetCommandRef::~NetCommandRef()
{
	if (m_msg != 0)
	{
		m_msg->detach();
	}
}
