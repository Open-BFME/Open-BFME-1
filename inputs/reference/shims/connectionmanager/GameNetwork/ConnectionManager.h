#pragma once
// TU-scoped stand-in for the real GameNetwork/ConnectionManager.h (whose
// ZH-reference field layout does not match BFME's -- proven by three
// thunk-dump accessor bodies: retail getLocalPlayerID/isPacketRouter read
// this+0x12028/this+0x1202c for m_localSlot/m_packetRouterSlot, 0x12004
// bytes past the end of the this+4 m_connections pointer array the ZH
// header places right after the vptr. Whatever grew BFME's ConnectionManager
// between those two points is opaque padding here -- nothing in this TU
// touches it.
//
// Scoped to this TU via a private /Ireference/shims/connectionmanager
// include -- every other TU still resolves GameNetwork/ConnectionManager.h
// to the real header.

class NetProgressCommandMsg;

// Only the one dword retail's isPlayerConnected reads (this+0, compared to
// -1) is modeled; the rest of the real Connection object is irrelevant here.
class Connection
{
public:
	Int m_openSentinel;
};

class ConnectionManager
{
public:
	// The real class declares virtual init/reset/update/etc, giving it a
	// vptr at this+0; a dummy virtual here reproduces that so m_connections
	// lands at this+4 like retail.
	virtual ~ConnectionManager() {}

	Connection *m_connections[8];					// this+4 .. this+0x24
	char m_padBeforeLocalSlot[0x12028 - 0x24];		// unpinned; not touched by this TU
	UnsignedInt m_localSlot;						// this+0x12028
	UnsignedInt m_packetRouterSlot;				// this+0x1202c

	// The tail the frame scheduler works on. The constructor at 0x00669630 and
	// init at 0x00669050 write all of it; sendFrameInfo, the FRAMEINFO receiver
	// in the command dispatcher and the readiness gate read it back.
	UnsignedInt m_playerIds[8];					// this+0x12030, init to -1
	UnsignedInt m_pad12050;						// this+0x12050
	UnsignedShort m_pad12054;					// this+0x12054
	UnsignedShort m_pad12056;
	UnsignedInt m_pad12058;						// this+0x12058
	UnsignedInt m_frameCeiling;					// this+0x1205c -- the shared ceiling
	UnsignedInt m_playerLatestFrame[8];			// this+0x12060
	UnsignedInt m_playerState[8];					// this+0x12080, 0 empty / 1 in game / 2-3 leaving
	UnsignedInt m_playerFrameInfoAux[8];			// this+0x120a0, from FRAMEINFO +0x20
	UnsignedInt m_playerAux2[8];					// this+0x120c0
	UnsignedInt m_pad120e0;						// this+0x120e0
	void *m_frameData[8];						// this+0x120e4, FrameDataManager *

	void sendFrameDataToPlayer( UnsignedInt playerID, UnsignedInt startingFrame );
	UnsignedInt getLocalPlayerID();
	Bool isPacketRouter( void );
	Bool isPlayerConnected( Int playerID );

private:
	void processProgress( NetProgressCommandMsg *msg );
};
