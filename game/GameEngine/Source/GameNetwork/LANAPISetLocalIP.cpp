// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline
// BFME LANAPI::SetLocalIP(UnsignedInt), retail RVA 0x00686B10, 199 bytes.
// BFME address/transport layout and port retry path. The complete body,
// both returns and all call targets were independently audited.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

enum { LAN_BASE_PORT = 8086, LAN_LAST_PORT = 8094 };

extern "C" __declspec(dllimport) char *__cdecl getenv(const char *name);
extern "C" __declspec(dllimport) Int __cdecl atoi(const char *text);

struct TransportAddress
{
	UnsignedInt ip;
	UnsignedShort port;
	UnsignedShort pad;
};

class UDP
{
public:
	Int AllowBroadcasts(Bool value);
};

class Transport
{
public:
	void reset(void);
	Bool init(const TransportAddress *address);
	Bool allowBroadcasts(Bool value)
	{
		if (!m_udp)
			return false;
		return m_udp->AllowBroadcasts(value) ? true : false;
	}

private:
	unsigned char m_bfmeHead[0x40E04];
	UDP *m_udp;
};

#include "StringInline.h"

extern UnsignedInt ResolveIP(AsciiString host);

class LANAPI
{
public:
	virtual void _bfme_slot00(void) = 0;
	virtual void _bfme_slot01(void) = 0;
	virtual void _bfme_slot02(void) = 0;
	virtual void _bfme_slot03(void) = 0;
	virtual void _bfme_slot04(void) = 0;
	virtual void _bfme_slot05(void) = 0;
	virtual void _bfme_slot06(void) = 0;
	virtual void _bfme_slot07(void) = 0;
	virtual void _bfme_slot08(void) = 0;
	virtual void _bfme_slot09(void) = 0;
	virtual void _bfme_slot10(void) = 0;
	virtual void _bfme_slot11(void) = 0;
	virtual void _bfme_slot12(void) = 0;
	virtual void _bfme_slot13(void) = 0;
	virtual void _bfme_slot14(void) = 0;
	virtual void _bfme_slot15(void) = 0;
	virtual void _bfme_slot16(void) = 0;
	virtual void _bfme_slot17(void) = 0;
	virtual void _bfme_slot18(void) = 0;
	virtual void _bfme_slot19(void) = 0;
	virtual void _bfme_slot20(void) = 0;
	virtual void _bfme_slot21(void) = 0;
	virtual void _bfme_slot22(void) = 0;
	virtual void _bfme_slot23(void) = 0;
	virtual void _bfme_slot24(void) = 0;
	virtual void _bfme_slot25(void) = 0;
	virtual void _bfme_slot26(void) = 0;
	virtual void _bfme_slot27(void) = 0;
	virtual void _bfme_slot28(void) = 0;
	virtual void _bfme_slot29(void) = 0;
	virtual void _bfme_slot30(void) = 0;
	virtual void _bfme_slot31(void) = 0;
	virtual void _bfme_slot32(void) = 0;
	virtual void _bfme_slot33(void) = 0;
	virtual void _bfme_slot34(void) = 0;
	virtual void _bfme_slot35(void) = 0;
	virtual void _bfme_slot36(void) = 0;
	virtual void _bfme_slot37(void) = 0;
	virtual void _bfme_slot38(void) = 0;
	virtual void _bfme_slot39(void) = 0;
	virtual void _bfme_slot40(void) = 0;
	virtual void _bfme_slot41(void) = 0;
	virtual void _bfme_slot42(void) = 0;
	virtual void _bfme_slot43(void) = 0;
	virtual void _bfme_slot44(void) = 0;
	virtual Bool SetLocalIP(UnsignedInt localIP);

protected:
	unsigned char m_beforeLocalAddress[0x44 - 4];
	TransportAddress m_localAddress;
	Transport *m_transport;
	UnsignedInt m_broadcastAddr;
};

Bool LANAPI::SetLocalIP(UnsignedInt localIP)
{
	m_localAddress.ip = localIP;
	m_transport->reset();

	const char *headlessInstance = getenv("_EA_RTS_HEADLESS");
	Int port = LAN_BASE_PORT + atoi(headlessInstance ? headlessInstance : "0");
	while ((UnsignedShort)port < LAN_LAST_PORT)
	{
		m_localAddress.port = (UnsignedShort)port;
		if (m_transport->init(&m_localAddress))
			break;
		++port;
	}

	if (m_localAddress.ip == ResolveIP(AsciiString("127.0.0.1")))
	{
		m_transport->allowBroadcasts(false);
		m_broadcastAddr = m_localAddress.ip;
	}
	else
	{
		m_transport->allowBroadcasts(true);
		m_broadcastAddr = 0xffffffff;
	}

	return (UnsignedShort)port < LAN_LAST_PORT;
}
