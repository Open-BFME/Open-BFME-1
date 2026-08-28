// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Transport::queueSend, 0x00683830, 164 bytes, and the pass it runs over every
// outgoing message.
//
// Both live here together because the second one is a file-static that retail
// calls with the message in ecx and the byte count in eax -- neither a thiscall
// nor a fastcall, but MSVC's custom calling convention for a static function
// whose call sites it can all see. That only happens if the two are compiled in
// the same translation unit.
//
// The pass itself is BFME's own; the reference sends the packet as-is. Each
// dword is XORed with a key that starts at 0x38D9B7D4 and walks by subtracting
// 0x7F39C50E, then byte-swapped. It covers the CRC as well as the payload --
// hence the length plus four.
//
// The message layout the loop stride pins is packed: 0x40E bytes per entry, so
// the trailing UnsignedShort port is not padded out to a dword.

#include <string.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

#define NULL 0
#define TRUE 1
#define FALSE 0

enum { MAX_PACKET_SIZE = 0x1DC };
enum { MAX_MESSAGES = 0x80 };

extern "C" __declspec(dllimport) unsigned long __stdcall htonl(unsigned long netlong);

UnsignedInt BFMEComputeCRC(const UnsignedByte *data, UnsignedInt length, UnsignedInt crc);

#pragma pack(push, 1)
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetworkDefs.h
struct TransportMessage
{
	UnsignedInt crc;								// +0x000
	UnsignedByte data[0x400];						// +0x004
	Int length;										// +0x404
	UnsignedInt addr;								// +0x408
	UnsignedShort port;								// +0x40C
};
#pragma pack(pop)

struct NetPacketAddress
{
	UnsignedInt ip;
	UnsignedShort port;
};

static void obfuscate(TransportMessage *msg, Int numBytes)
{
	UnsignedInt key = 0x38D9B7D4;
	UnsignedInt *p = (UnsignedInt *)msg;
	Int count = numBytes / 4;

	for (Int i = 0; i < count; ++i) {
		*p ^= key;
		*p = htonl(*p);
		++p;
		key -= 0x7F39C50E;
	}
}

class Transport
{
public:
	Bool queueSend(NetPacketAddress *addr, const UnsignedByte *data, Int len);

	TransportMessage m_outBuffer[MAX_MESSAGES];		// this+0x000
};

Bool Transport::queueSend(NetPacketAddress *addr, const UnsignedByte *data, Int len)
{
	if ((data == NULL) || ((UnsignedInt)len > MAX_PACKET_SIZE)) {
		return FALSE;
	}

	Int i = 0;
	do {
		if (m_outBuffer[i].length == 0) {
			goto found;
		}

		++i;
	} while (i < MAX_MESSAGES);

	return FALSE;

found:

	UnsignedInt crc = BFMEComputeCRC(data, len, 0);

	m_outBuffer[i].addr = addr->ip;
	m_outBuffer[i].port = addr->port;
	m_outBuffer[i].length = len;
	memcpy(m_outBuffer[i].data, data, len);
	m_outBuffer[i].crc = crc;

	obfuscate(&m_outBuffer[i], len + 4);

	return TRUE;
}
