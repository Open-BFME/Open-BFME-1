// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/transport /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameNetwork/Transport.h"
#include "GameNetwork/NetworkInterface.h"

// Retail's packet check calls the WWLib CRC through the thunk at 0x0000A984.
extern unsigned long CRC_Memory( const unsigned char *data, unsigned long length, unsigned long crc );


/**
 * BFME does in the constructor what the reference does in init: clear both
 * message rings and every statistics counter. init is left with nothing to do
 * but bind.
 *
 * Two things about the clear loop are in the bytes and neither is free.
 *
 * The out buffer is cleared first. Retail strength-reduces the loop onto
 * &m_inBuffer[i].length -- the in buffer's last three stores get displacements
 * 0/+4/+8 and everything else is addressed backwards from there -- and which
 * of the ten addresses MSVC picks as the induction variable depends on the
 * order the two blocks are written in.
 *
 * The entries are reached through a local pointer each rather than subscripted
 * in place. Subscripting compiles to the same instructions and the same 182
 * bytes but anchors the loop on &m_outBuffer[i].length, one block earlier;
 * with the pointers the anchor lands where retail has it.
 */
Transport::Transport(void)
{
	m_winsockInit = false;
	m_udpsock = NULL;
	m_statisticsSlot = 0;
	m_lastSecond = 0;
	m_badPackets = 0;

	Int i;
	for (i=0; i<MAX_MESSAGES; ++i)
	{
		TransportMessage *out = &m_outBuffer[i];
		out->header.crc = 0;
		memset(out->data, 0, MAX_MESSAGE_LEN);
		out->length = 0;
		out->addr = 0;
		out->port = 0;

		TransportMessage *in = &m_inBuffer[i];
		in->header.crc = 0;
		memset(in->data, 0, MAX_MESSAGE_LEN);
		in->length = 0;
		in->addr = 0;
		in->port = 0;
	}

	for (i=0; i<MAX_TRANSPORT_STATISTICS_SECONDS; ++i)
	{
		m_incomingBytes[i] = 0;
		m_unknownBytes[i] = 0;
		m_outgoingBytes[i] = 0;
		m_incomingPackets[i] = 0;
		m_unknownPackets[i] = 0;
		m_outgoingPackets[i] = 0;
	}
}

void Transport::reset( void )
{
	if (m_udpsock)
	{
		delete m_udpsock;
		m_udpsock = NULL;
	}

	if (m_winsockInit)
	{
		WSACleanup();
		m_winsockInit = false;
	}
}

Bool Transport::update( void )
{
	Bool retval = TRUE;
	if (doRecv() == FALSE && m_udpsock && m_udpsock->GetStatus() == UDP::ADDRNOTAVAIL)
	{
		retval = FALSE;
	}
	if (doSend() == FALSE && m_udpsock && m_udpsock->GetStatus() == UDP::ADDRNOTAVAIL)
	{
		retval = FALSE;
	}
	return retval;
}

Bool Transport::doSend() {
	if (!m_udpsock)
	{
		return FALSE;
	}

	// Statistics gathering
	UnsignedInt now = timeGetTime();
	if (m_lastSecond + 1000 < now)
	{
		m_lastSecond = now;
		m_statisticsSlot = (m_statisticsSlot + 1) % MAX_TRANSPORT_STATISTICS_SECONDS;
		m_outgoingPackets[m_statisticsSlot] = 0;
		m_outgoingBytes[m_statisticsSlot] = 0;
		m_incomingPackets[m_statisticsSlot] = 0;
		m_incomingBytes[m_statisticsSlot] = 0;
		m_unknownPackets[m_statisticsSlot] = 0;
		m_unknownBytes[m_statisticsSlot] = 0;
	}

	Bool retval = TRUE;

	// Send all messages
	int i;
	for (i=0; i<MAX_MESSAGES; ++i)
	{
		if (m_outBuffer[i].length != 0)
		{
			int bytesSent = 0;
			// Send this message
			if ((bytesSent = m_udpsock->Write((unsigned char *)(&m_outBuffer[i]), m_outBuffer[i].length + sizeof(TransportMessageHeader), m_outBuffer[i].addr, m_outBuffer[i].port)) > 0)
			{
				m_outgoingPackets[m_statisticsSlot]++;
				m_outgoingBytes[m_statisticsSlot] += m_outBuffer[i].length + sizeof(TransportMessageHeader);
				m_outBuffer[i].length = 0;  // Remove from queue
			}
			else
			{
				retval = FALSE;
			}
		}
	} // for (i=0; i<MAX_MESSAGES; ++i)

	return retval;
}

// This assumes the buf is a multiple of 4 bytes.  Extra is not encrypted.
static inline void encryptBuf( unsigned char *buf, Int len )
{
	UnsignedInt mask = 0x38D9B7D4;

	UnsignedInt *uintPtr = (UnsignedInt *) (buf);

	for (int i=0 ; i<len/4 ; i++) {
		*uintPtr = (*uintPtr) ^ mask;
		*uintPtr = htonl(*uintPtr);
		uintPtr++;
		mask -= 0x7F39C50E;
	}
}

// This assumes the buf is a multiple of 4 bytes.  Extra is not encrypted.
static inline void decryptBuf( unsigned char *buf, Int len )
{
	UnsignedInt mask = 0x38D9B7D4;

	UnsignedInt *uintPtr = (UnsignedInt *) (buf);

	for (int i=0 ; i<len/4 ; i++) {
		*uintPtr = htonl(*uintPtr);
		*uintPtr = (*uintPtr) ^ mask;
		uintPtr++;
		mask -= 0x7F39C50E;
	}
}

Bool Transport::doRecv()
{
	if (!m_udpsock)
	{
		return FALSE;
	}

	// The reference starts this TRUE and only clears it on a socket error, so it
	// answers "did the socket behave". BFME starts it FALSE and sets it only
	// when a packet actually lands in m_inBuffer, so it answers "did anything
	// arrive" -- and a read error is no longer distinguishable from a quiet
	// socket.
	Bool retval = FALSE;

	sockaddr_in from;
	TransportMessage incomingMessage;

	Int len;
	while ( (len=m_udpsock->Read((unsigned char *)&incomingMessage, sizeof(TransportMessage), &from)) > 0 )
	{
		decryptBuf((unsigned char *)&incomingMessage, len);

		// The reference fills these in on the m_inBuffer slot it picks. BFME
		// fills in the local and copies the whole struct into the slot, which is
		// why the slot store below is an assignment rather than a memcpy.
		incomingMessage.addr = ntohl(from.sin_addr.S_un.S_addr);
		incomingMessage.port = ntohs(from.sin_port);

		UnsignedInt msgLen = len - sizeof(TransportMessageHeader);
		incomingMessage.length = msgLen;

		// Where the reference checks a magic number through isGeneralsPacket,
		// BFME recomputes the CRC over the payload and compares it against the
		// header. That check is the reason BFME's header has no magic field left
		// to check, and it is the only validation an incoming packet gets.
		if (msgLen <= 0 || msgLen > MAX_MESSAGE_LEN ||
				incomingMessage.header.crc != CRC_Memory(incomingMessage.data, msgLen, 0))
		{
			++m_badPackets;
			m_unknownPackets[m_statisticsSlot]++;
			m_unknownBytes[m_statisticsSlot] += len;
			continue;
		}

		m_incomingPackets[m_statisticsSlot]++;
		m_incomingBytes[m_statisticsSlot] += len;

		for (int i=0; i<MAX_MESSAGES; ++i)
		{
			if (m_inBuffer[i].length == 0)
			{
				// Empty slot; use it
				m_inBuffer[i] = incomingMessage;
				retval = TRUE;
				break;
			}
		}
	}

	return retval;
}

// The six bandwidth metrics are the reference's, unchanged, and retail lays
// them out in this order -- each one identified by the statistics array its
// unrolled loop indexes.

Real Transport::getIncomingBytesPerSecond( void )
{
	Real totalIncomingBytes = 0.0;
	for (int sampleIndex=0; sampleIndex<MAX_TRANSPORT_STATISTICS_SECONDS; ++sampleIndex)
	{
		if (sampleIndex != m_statisticsSlot)
			totalIncomingBytes += m_incomingBytes[sampleIndex];
	}
	return totalIncomingBytes / (MAX_TRANSPORT_STATISTICS_SECONDS-1);
}

Real Transport::getIncomingPacketsPerSecond( void )
{
	Real totalIncomingPackets = 0.0;
	for (int sampleIndex=0; sampleIndex<MAX_TRANSPORT_STATISTICS_SECONDS; ++sampleIndex)
	{
		if (sampleIndex != m_statisticsSlot)
			totalIncomingPackets += m_incomingPackets[sampleIndex];
	}
	return totalIncomingPackets / (MAX_TRANSPORT_STATISTICS_SECONDS-1);
}

Real Transport::getOutgoingBytesPerSecond( void )
{
	Real totalOutgoingBytes = 0.0;
	for (int sampleIndex=0; sampleIndex<MAX_TRANSPORT_STATISTICS_SECONDS; ++sampleIndex)
	{
		if (sampleIndex != m_statisticsSlot)
			totalOutgoingBytes += m_outgoingBytes[sampleIndex];
	}
	return totalOutgoingBytes / (MAX_TRANSPORT_STATISTICS_SECONDS-1);
}

Real Transport::getOutgoingPacketsPerSecond( void )
{
	Real totalOutgoingPackets = 0.0;
	for (int sampleIndex=0; sampleIndex<MAX_TRANSPORT_STATISTICS_SECONDS; ++sampleIndex)
	{
		if (sampleIndex != m_statisticsSlot)
			totalOutgoingPackets += m_outgoingPackets[sampleIndex];
	}
	return totalOutgoingPackets / (MAX_TRANSPORT_STATISTICS_SECONDS-1);
}

Real Transport::getUnknownBytesPerSecond( void )
{
	Real totalUnknownBytes = 0.0;
	for (int sampleIndex=0; sampleIndex<MAX_TRANSPORT_STATISTICS_SECONDS; ++sampleIndex)
	{
		if (sampleIndex != m_statisticsSlot)
			totalUnknownBytes += m_unknownBytes[sampleIndex];
	}
	return totalUnknownBytes / (MAX_TRANSPORT_STATISTICS_SECONDS-1);
}

Real Transport::getUnknownPacketsPerSecond( void )
{
	Real totalUnknownPackets = 0.0;
	for (int sampleIndex=0; sampleIndex<MAX_TRANSPORT_STATISTICS_SECONDS; ++sampleIndex)
	{
		if (sampleIndex != m_statisticsSlot)
			totalUnknownPackets += m_unknownPackets[sampleIndex];
	}
	return totalUnknownPackets / (MAX_TRANSPORT_STATISTICS_SECONDS-1);
}

/**
 * The reference takes (UnsignedInt ip, UnsignedShort port); BFME takes one
 * TransportAddress pointer, which is why this ends in `ret 4`. Everything the
 * reference's init does after the bind is still here even though the
 * constructor now does it too -- BFME clears the two length fields and the six
 * statistics arrays a second time.
 */
Bool Transport::init( const TransportAddress *addr )
{
	// ----- Initialize Winsock -----
	if (!m_winsockInit)
	{
		WORD verReq = MAKEWORD(2, 2);
		WSADATA wsadata;

		int err = WSAStartup(verReq, &wsadata);
		if (err != 0) {
			return false;
		}

		if ((LOBYTE(wsadata.wVersion) != 2) || (HIBYTE(wsadata.wVersion) !=2)) {
			WSACleanup();
			return false;
		}
		m_winsockInit = true;
	}

	// ------- Bind our port --------
	if (m_udpsock)
		delete m_udpsock;
	m_udpsock = new UDP();

	if (!m_udpsock)
		return false;

	int retval = -1;
	UnsignedInt now = timeGetTime();
	while ((retval != 0) && ((timeGetTime() - now) < 1000)) {
		retval = m_udpsock->Bind(addr->ip, addr->port);
	}

	if (retval != 0) {
		delete m_udpsock;
		m_udpsock = NULL;
		return false;
	}

	// ------- Clear buffers --------
	int i;
	for (i=0; i<MAX_MESSAGES; ++i)
	{
		m_outBuffer[i].length = 0;
		m_inBuffer[i].length = 0;
	}
	for (i=0; i<MAX_TRANSPORT_STATISTICS_SECONDS; ++i)
	{
		m_incomingBytes[i] = 0;
		m_outgoingBytes[i] = 0;
		m_unknownBytes[i] = 0;
		m_incomingPackets[i] = 0;
		m_outgoingPackets[i] = 0;
		m_unknownPackets[i] = 0;
		// Retail really does clear this inside the loop, thirty times over.
		m_badPackets = 0;
	}
	m_statisticsSlot = 0;
	m_lastSecond = timeGetTime();

	return true;
}

// Transport::init(AsciiString, UnsignedShort) is matched from
// Transport_init_AsciiString.cpp, not from here. It needs an AsciiString whose
// copy constructor is declared and not defined so that ResolveIP's by-value
// argument is built by an out-of-line call, and the header set this file
// compiles against defines that constructor inline.

/**
 * Two departures from the reference: the guard rejects a NULL buffer rather
 * than a zero length, and the packet is stamped with a CRC over the caller's
 * buffer instead of a magic number. doRecv is the other half of that -- it
 * recomputes the same CRC and drops anything that disagrees.
 */
// ?queueSend@Transport@@QAE_NPBUTransportAddress@@PBEI@Z present-unmatched
// (and the name is inferred -- see the TransportAddress note in the shim).
// Compiles to retail's length and instructions; retail commits to a three
// register prologue and holds this in ebp, buf in esi and len in ebx, while
// this source leaves this in ecx. Same allocator tie-break as the constructor.
Bool Transport::queueSend(const TransportAddress *dest, const UnsignedByte *buf, UnsignedInt len)
{
	int i;

	if (buf == NULL || len > MAX_PACKET_SIZE)
	{
		return false;
	}

	for (i=0; i<MAX_MESSAGES; ++i)
	{
		if (m_outBuffer[i].length == 0)
		{
			// Insert data here
			m_outBuffer[i].addr = dest->ip;
			m_outBuffer[i].port = dest->port;
			m_outBuffer[i].length = len;
			memcpy(m_outBuffer[i].data, buf, len);
			m_outBuffer[i].header.crc = CRC_Memory(buf, len, 0);

			// Encrypt packet
			encryptBuf((unsigned char *)&m_outBuffer[i], len + sizeof(TransportMessageHeader));

			return true;
		}
	}
	return false;
}

