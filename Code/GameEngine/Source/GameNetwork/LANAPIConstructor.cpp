// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline
// BFME LANAPI constructor at 006854F0; caller ILT 0003ECC5 and vtable 0111AF50.
// Compiler-only barriers preserve the two retail store scheduling windows.
#include <stdlib.h>
#include "StringInline.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef int Int;
typedef bool Bool;

class SubsystemInterface
{
public:
	SubsystemInterface(void);
	virtual ~SubsystemInterface(void);
};

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

class Transport
{
public:
	Transport(void);
private:
	// Only the retail allocation size is needed here; Transport owns the layout.
	UnsignedByte m_unmodelled000[0x410e4];
};

class LANAPI : public SubsystemInterface
{
public:
	virtual ~LANAPI(void);
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual void slot27(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot29(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot31(void) = 0;
	virtual void slot32(void) = 0;
	virtual void slot33(void) = 0;
	virtual void slot34(void) = 0;
	virtual void slot35(void) = 0;
	virtual void slot36(void) = 0;
	virtual void slot37(void) = 0;
	virtual void slot38(void) = 0;
	virtual void slot39(void) = 0;
	virtual void slot40(void) = 0;
	virtual void slot41(void) = 0;
	virtual void slot42(void) = 0;
	virtual void slot43(void) = 0;
	virtual void slot44(void) = 0;
	virtual void slot45(void) = 0;
	virtual void slot46(void) = 0;
	virtual void slot47(void) = 0;
	virtual void slot48(void) = 0;
	virtual void slot49(void) = 0;
	virtual void slot50(void) = 0;
	virtual void slot51(void) = 0;
	virtual void slot52(void) = 0;
	virtual void slot53(void) = 0;
	virtual void slot54(void) = 0;
	virtual void slot55(void) = 0;

	LANAPI(void);

protected:
	UnsignedByte m_bfme_0x04[4];
	void *m_lobbyPlayers;
	void *m_games;
	UnicodeString m_name;
	AsciiString m_userName;
	AsciiString m_hostName;
	UnsignedInt m_gameStartTime;
	Int m_gameStartSeconds;
	Int m_pendingAction;
	UnsignedInt m_expiration;
	UnsignedInt m_actionTimeout;
	UnsignedInt m_directConnectRemoteIP;
	UnsignedShort m_bfme_0x34;
	UnsignedInt m_lastResendTime;
	Bool m_isInLANMenu;
	Bool m_inLobby;
	UnsignedByte m_bfme_0x3e[2];
	void *m_currentGame;
	UnsignedInt m_localIP;
	UnsignedShort m_localPort;
	UnsignedShort m_bfme_0x4a;
	Transport *m_transport;
	UnsignedInt m_broadcastAddr;
	UnsignedInt m_lastUpdate;
	Bool m_isActive;
	Bool m_bfme_0x59;
	UnsignedShort m_bfme_0x5a;
	UnsignedInt m_bfme_0x5c;
	UnsignedInt m_bfme_0x60;
	UnsignedInt m_bfme_0x64;
};

LANAPI::LANAPI(void)
	: m_lobbyPlayers(0), m_games(0)
{
	m_gameStartTime = 0;
	m_gameStartSeconds = 0;
	m_pendingAction = 0;
	m_expiration = 0;
	m_actionTimeout = getenv("_EA_RTS_HEADLESS") ? 50000 : 5000;
	m_directConnectRemoteIP = 0;
	m_bfme_0x34 = 0;
	_ReadWriteBarrier();
	m_lastResendTime = 0;
	m_isInLANMenu = true;
	m_inLobby = true;
	m_currentGame = 0;
	m_localIP = 0;
	m_localPort = 0;
	_ReadWriteBarrier();
	m_transport = 0;
	m_broadcastAddr = 0xffffffff;
	m_lastUpdate = 0;
	m_isActive = true;
	m_bfme_0x59 = false;
	m_bfme_0x5c = 0;
	m_bfme_0x60 = 0;
	m_bfme_0x64 = 0;
	m_transport = new Transport;
}
