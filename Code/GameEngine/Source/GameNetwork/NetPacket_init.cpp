// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ??0NetPacket@@: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?init@NetPacket@@QAEXXZ: Code/GameEngine/Source/GameNetwork/NetPacket.cpp

// NetPacket::init, 0x00677700, 82 bytes.
//
// Named without guessing: Connection::doSend constructs a NetPacket and then
// calls this, and the reference has two candidates for that slot. reset() is
// ruled out because it deletes m_lastCommand before delegating, and this body
// makes no calls at all -- it is a flat run of stores. So it is init().
//
// The stores also pin BFME's whole NetPacket layout, and it is the reference's
// field set in the reference's init order, with one rearrangement that matters:
//
//   0x000  vptr                (the constructor at 0x00679650 stores one)
//   0x004  m_packet[0x1DC]     0x1DC == 476 == MAX_PACKET_SIZE
//   0x1E0  m_packetLen
//   0x1E4  m_addr        <-- these two are adjacent in BFME and separated in
//   0x1E8  m_port        <-- the reference
//   0x1EC  m_numCommands
//   0x1F0  m_lastCommand
//   0x1F4  m_lastFrame
//   0x1F8  m_lastCommandID     (word)
//   0x1FA  m_lastPlayerID      (byte)
//   0x1FB  m_lastCommandType   (byte)
//   0x1FC  m_lastRelay         (byte)
//
// sizeof is 0x200, which is what doSend hands operator new.
//
// m_addr and m_port sitting adjacent is the confirmation that the six-byte
// { UnsignedInt ip; UnsignedShort port; } inferred from Transport::queueSend is
// real: doSend passes &packet->m_addr as that argument, so the pair IS the
// address struct, embedded in the packet rather than built on the stack.
//
// Declared here rather than through a shim header: any file under
// reference/shims/ forces the full gate, and nothing outside this file needs it.

#include <string.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

class NetCommandMsg;

// BFME's header is four bytes, not six: the reference's TransportMessageHeader
// carries a CRC and a magic number, and retail's data run starts at +4. The
// three trailing fields land at +0x404, +0x408 and +0x40C, which is what pins
// the payload at 0x400 bytes.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetworkDefs.h
struct TransportMessageHeader
{
	UnsignedInt crc;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetworkDefs.h
struct TransportMessage
{
	TransportMessageHeader header;					// +0x000
	UnsignedByte data[0x400];						// +0x004
	Int length;										// +0x404
	UnsignedInt addr;								// +0x408
	UnsignedShort port;								// +0x40C
};

void __cdecl operator delete(void *block) throw();

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
public:
	~NetCommandRef();
};

// The zeroing is a member constructor, not something either NetPacket
// constructor writes: both of them emit the vptr store, then ip = 0 and a word
// port = 0, before anything of their own. That is member construction order,
// and it is what puts the vptr first in each.
//
// Spelling it as a real constructor is what closes both NetPacket constructors.
// With the pair zeroed in the constructor bodies instead, MSVC schedules the
// inlined init()'s eight-byte stack temp to the top of the frame and sinks the
// vptr store below the whole run of zero stores; retail does the opposite, and
// member construction order is the only thing that pins it. init() keeps its
// matched shape either way -- `NetPacketAddress dest;` and `= { 0, 0 }` compile
// to the same word store plus dword reload, because the low half is constant
// propagated and only the padded high half has to go through memory.
struct NetPacketAddress
{
	NetPacketAddress() { ip = 0; port = 0; }

	UnsignedInt ip;
	UnsignedShort port;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
class NetPacket
{
public:
	virtual ~NetPacket();

	NetPacket();
	NetPacket(TransportMessage *msg);
	void init();

	UnsignedByte m_packet[0x1DC];					// this+0x004
	Int m_packetLen;								// this+0x1E0
	// Eight bytes, not six: init assigns this as a whole struct (dword at +0x1E4
	// and dword at +0x1E8 out of an eight-byte stack temp), so the trailing two
	// bytes of padding are real and the type is NOT packed. The Transport shim's
	// pack(1) TransportAddress is wrong on that point.
	NetPacketAddress m_dest;						// this+0x1E4 (ip), +0x1E8 (port)
	Int m_numCommands;								// this+0x1EC
	// A ref, not a message: the destructor deletes it through the
	// NetCommandRef destructor ??1NetCommandRef@@QAE@XZ. (Kept on one line:
	// a comment line that OPENS with a mangled name binds to the next
	// definition as an annotation, and this one sits directly above the
	// default constructor.)
	NetCommandRef *m_lastCommand;					// this+0x1F0
	UnsignedInt m_lastFrame;						// this+0x1F4
	UnsignedShort m_lastCommandID;					// this+0x1F8
	UnsignedByte m_lastPlayerID;					// this+0x1FA
	UnsignedByte m_lastCommandType;					// this+0x1FB
	UnsignedByte m_lastRelay;						// this+0x1FC
};

// 0x00679650, 103 bytes. The address pair is zeroed field-wise -- dword at
// +0x1E4 then a word at +0x1E8 -- before init() assigns the same pair as a
// whole struct, so both shapes are in retail one after the other. The
// field-wise half is NetPacketAddress's own constructor, which is why it sits
// between the vptr store and anything this body writes.
NetPacket::NetPacket() {
	init();
}

// 0x00679730, 174 bytes. Same prefix as the default constructor above; what
// follows is the address pair lifted out of the transport message, the
// 476-byte payload copy and the -1 command count. The reference runs those in
// the other order -- length and copy first, address last -- and retail's
// schedule is source order, so the assignments are written the way retail
// emits them. The message layout the offsets pin is the interesting part:
// BFME's header is four bytes where the reference's carries a CRC and a magic
// number.
NetPacket::NetPacket(TransportMessage *msg) {
	init();
	m_dest.ip = msg->addr;
	m_dest.port = msg->port;
	m_packetLen = msg->length;
	memcpy(m_packet, msg->data, sizeof(m_packet));
	m_numCommands = -1;
}

NetPacket::~NetPacket() {
	if (m_lastCommand != 0) {
		delete m_lastCommand;
		m_lastCommand = 0;
	}
}

void NetPacket::init() {
	NetPacketAddress dest;
	m_dest = dest;
	m_numCommands = 0;
	m_packetLen = 0;
	m_packet[0] = 0;

	m_lastPlayerID = 0;
	m_lastFrame = 0;
	m_lastCommandID = 0;
	m_lastCommandType = 0;
	m_lastRelay = 0;

	m_lastCommand = 0;
}
