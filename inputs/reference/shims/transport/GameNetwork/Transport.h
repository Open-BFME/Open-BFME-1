#pragma once

#ifndef _TRANSPORT_H_
#define _TRANSPORT_H_

// TU-scoped stand-in for the real GameNetwork/Transport.h. BFME's Transport has
// the same members as the ZH reference's but not in the same order, and it drops
// three of them. Every offset below is pinned by a retail body in this TU:
//
//   0x00000  m_outBuffer[128]   stride 0x40E (queueSend: imul edi,edi,0x40e)
//   0x20700  m_inBuffer[128]    the constructor clears both arrays in one loop,
//                               the second at edx-0x404 == this+0x20700+i*0x40E
//   0x40E00  m_winsockInit      reset tests it as a byte and stores 0 back
//   0x40E04  m_udpsock          doSend's first load; reset deletes through it
//   0x40E08  m_statisticsSlot   idiv by 30 in doSend, then used as an index
//   0x40E0C  m_lastSecond       compared against timeGetTime()+1000
//   0x40E10  six UnsignedInt[30] statistics arrays
//   0x410E0  m_badPackets, a cumulative bad-packet count doRecv bumps
//
// The reference puts m_statisticsSlot and m_lastSecond *after* the statistics
// arrays and carries m_useLatency/m_usePacketLoss between m_udpsock and them;
// BFME has neither, and its two counters sit in front of the arrays instead.
// m_delayedInBuffer is absent as well, but that one is only #ifdef debug in the
// reference too, so its absence here is not evidence of a BFME change.
//
// The six arrays are named by doSend's clear order. It writes 0x41068, 0x40F00,
// 0x40F78, 0x40E10, 0x40FF0, 0x40E88, and the reference's doSend clears
// outgoingPackets, outgoingBytes, incomingPackets, incomingBytes,
// unknownPackets, unknownBytes in that order -- which sorts by offset back into
// exactly the reference's declaration order, so the names below are the
// reference's names in the reference's order.
//
// Scoped to this TU via a private /Ireference/shims/transport include -- every
// other TU still resolves GameNetwork/Transport.h to the real header.

#include "GameNetwork/udp.h"
#include "GameNetwork/NetworkDefs.h"

class Transport
{
public:

	Transport();
	~Transport();

	Bool init( AsciiString ip, UnsignedShort port );
	Bool init( const TransportAddress *addr );
	void reset( void );
	Bool update( void );

	Bool doRecv( void );
	Bool doSend( void );

	Bool queueSend( const TransportAddress *dest, const UnsignedByte *buf, UnsignedInt len );

	Real getIncomingBytesPerSecond( void );
	Real getIncomingPacketsPerSecond( void );
	Real getOutgoingBytesPerSecond( void );
	Real getOutgoingPacketsPerSecond( void );
	Real getUnknownBytesPerSecond( void );
	Real getUnknownPacketsPerSecond( void );

	TransportMessage m_outBuffer[MAX_MESSAGES];		// this+0x00000
	TransportMessage m_inBuffer[MAX_MESSAGES];		// this+0x20700

private:
	// The reference's m_port is absent: BFME's init never writes a port anywhere
	// on the object, and the three bytes of alignment before m_udpsock are all
	// that separate them.
	Bool m_winsockInit;								// this+0x40E00
	UDP *m_udpsock;									// this+0x40E04
	Int m_statisticsSlot;							// this+0x40E08
	UnsignedInt m_lastSecond;						// this+0x40E0C

	UnsignedInt m_incomingBytes[MAX_TRANSPORT_STATISTICS_SECONDS];		// 0x40E10
	UnsignedInt m_unknownBytes[MAX_TRANSPORT_STATISTICS_SECONDS];		// 0x40E88
	UnsignedInt m_outgoingBytes[MAX_TRANSPORT_STATISTICS_SECONDS];		// 0x40F00
	UnsignedInt m_incomingPackets[MAX_TRANSPORT_STATISTICS_SECONDS];	// 0x40F78
	UnsignedInt m_unknownPackets[MAX_TRANSPORT_STATISTICS_SECONDS];		// 0x40FF0
	UnsignedInt m_outgoingPackets[MAX_TRANSPORT_STATISTICS_SECONDS];	// 0x41068

	// A cumulative count of packets doRecv threw away, incremented next to the
	// per-second m_unknownPackets slot but never reset or read by anything in
	// this TU. The reference has no equivalent.
	UnsignedInt m_badPackets;						// this+0x410E0
};

#endif // _TRANSPORT_H_
