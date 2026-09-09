// _CommUdpProcess
// partial score=0.85 date=2026-09-09
// cl: /DNDEBUG /MD /GX /Od /GZ /GS

#define _DLL
#include <string.h>

struct CommUdpComm;

struct CommUdpMessage
{
	int m_length;
	unsigned int m_source;
	int m_code;
	int m_value;
	unsigned char m_body[ 0x218 ];
};

struct CommUdpComm
{
	char m_pad0[ 0x38 ];
	void ( __cdecl *m_sendProc )( CommUdpComm *, const void *, int, unsigned int );
	void ( __cdecl *m_receiveProc )( CommUdpComm *, const void *, int, unsigned int );
	char m_pad40[ 0x20 ];
	int m_bytesReceived;
	char m_pad64[ 0x04 ];
	int m_packetsReceived;
	char m_pad6c[ 0x0C ];
	CommUdpComm *m_next;
	void *m_socket;
	unsigned char m_peer[ 0x10 ];
	int m_state;
	int m_sessionHash;
	char m_pad98[ 0x14 ];
	int m_recvSequence;
	int m_reportedSequence;
	int m_recvCounter;
	char m_padB8[ 0x08 ];
	int m_sendWriteOffset;
	int m_sendReadOffset;
	int m_sendAckOffset;
	char m_padCC[ 0x0C ];
	unsigned int m_tickA;
	unsigned int m_tickB;
	unsigned int m_tickIdle;
	char m_padE4[ 0x134 ];
	int m_depth;
	int m_flags;
	void ( __cdecl *m_notify )( CommUdpComm *, int );
};

// EA's DirtySock CommUDP transport, which BFME uses for its GameSpy/online
// traffic. It has no counterpart in the vendored Zero Hour reference, and no
// __FILE__ string for it survives in the executable, so the directory name here
// is inferred from the module prefixes retail logs -- commudp, commtcp,
// protoadvt, NetGameUtil -- and from the sibling EA middleware that already
// lives under Code/Libraries/Source (Compression/EAC). Move it if better
// evidence turns up; only the `source` column of these rows has to follow.
//
// The surviving log strings establish the named entry points; the address-
// derived Rva helpers are retained by their retail RVAs and call graph. They
// are declared extern "C" because DirtySock is a C library.
//
// The lockstep path does not run through here -- that is SAGE's own udp.cpp.

extern "C" {
	int CommUDPWrite(void *ref, void *packet);
	int CommUDPConnect(void *ref, const char *addr, int bind, int peer);
	int CommUDPResolve(void *ref, const char *addr, char *buffer, int length, char divider);
	int Rva007FD920(void *socket, const void *data, int length, int flags, void *address, int addressLength);
	unsigned int Rva007FEA00();
	int Rva007FFDD0(unsigned int *address, int *port, int *extra, const char *text);
	void *Rva007FD2D0(int family, int type, int protocol);
	int Rva007FD510(void *socket, const void *address, int addressLength);
	void Rva007FD3F0(void *socket);
	void Rva00818FF0(void *ref, const char *text);
	int Rva00819590(void *ref, void *socket, const void *peerAddress);
	void Rva007FEBD0(void *lock);
	void Rva007FECB0(void *lock);
	void Rva00817640(void *ref);
	int Rva007FDA50(void *socket, char *buffer, int length, int flags,
		char *address, int *addressLength);
	int Rva007FF720(const void *a, const void *b);
	int Rva00818620(void *ref);
	void Rva008186C0(void *ref, void *message);
	int Rva008187E0(void *ref, void *message);
	int Rva00816F60(void *ref);
	void Rva00818AD0(void *ref);
	int Rva00817B30(unsigned int tick);
}

extern char g_Rva0130AF38Lock[4];
extern int g_Rva0130AD08Count;
extern CommUdpComm *g_Rva0130B188List;
extern CommUdpMessage g_Rva0130AD10;
extern CommUdpMessage g_Rva0130AF60;

int Rva007FE780Printf(const char *format, ...);

extern "C" { int CommUdpProcess(unsigned int tick); void CommUdpSetup(void *, void *, void *); int CommUdpPoke(void *); }

int CommUdpProcess(unsigned int tick)
{
	int addressLength;
	int iResult;
	CommUdpComm *comm;
	CommUdpComm *selected;
	unsigned char address[ 0x10 ];
	void *socket;
	int savedSequence;
	int packetCount;
	unsigned int elapsed;

	iResult = 0;
	selected = 0;
	memset( address, 0, 0x10 );
	g_Rva0130AD10.m_length = -1;
	socket = 0;
	comm = g_Rva0130B188List;
	goto first_check;
first_next:
	comm = comm->m_next;
first_check:
	if ( comm != 0 )
	{
		if ( comm->m_socket != 0 && comm->m_socket != socket )
		{
			socket = comm->m_socket;
			addressLength = 0x10;
			addressLength = Rva007FDA50( socket,
				(char *)&g_Rva0130AD10.m_code, 0x220, 0,
				(char *)address, &addressLength );
			if ( addressLength > 0 )
			{
				g_Rva0130AD10.m_length = addressLength - 8;
				g_Rva0130AD10.m_source =
					( ( ( ( (unsigned int)address[ 8 ] << 8 )
						| address[ 9 ] ) << 8 | address[ 10 ] ) << 8
						| address[ 11 ] );
				if ( g_Rva0130AD10.m_code == 1 )
					Rva007FE780Printf(
						"CommUdpProcess: got RAW_PACKET_INIT\n" );
				if ( g_Rva0130AD10.m_code == 2 )
					Rva007FE780Printf(
						"CommUdpProcess: got RAW_PACKET_CONN\n" );
				++iResult;
				goto first_done;
			}
		}
		goto first_next;
	}
first_done:

	comm = g_Rva0130B188List;
	goto second_check;
second_next:
	comm = comm->m_next;
second_check:
	if ( comm != 0 )
	{
		tick = Rva007FEA00();
		if ( selected == 0
			&& socket == comm->m_socket
			&& comm->m_state == 3
			&& g_Rva0130AD10.m_length == 0
			&& g_Rva0130AD10.m_code == 1
			&& comm->m_sessionHash == g_Rva0130AD10.m_value )
		{
			selected = comm;
		}

		if ( g_Rva0130AD10.m_length >= 0
			&& comm->m_state != 3
			&& comm->m_state != 5
			&& socket == comm->m_socket
			&& Rva007FF720( comm->m_peer, address ) == 0 )
		{
			comm->m_bytesReceived += g_Rva0130AD10.m_length;
			comm->m_packetsReceived++;
			if ( g_Rva0130AD10.m_code == 1
				|| g_Rva0130AD10.m_code == 2
				|| g_Rva0130AD10.m_code == 3 )
			{
				CommUdpSetup( comm, &g_Rva0130AD10, address );
				goto packet_done;
			}
			if ( comm->m_state != 4 )
				goto packet_done;
			if ( g_Rva0130AD10.m_code == 4 )
			{
				comm->m_tickB = g_Rva0130AD10.m_source;
				Rva008186C0( comm, &g_Rva0130AD10 );
				goto packet_done;
			}
			if ( (unsigned int)g_Rva0130AD10.m_code > 0x10000000 )
			{
				savedSequence = comm->m_recvSequence;
				packetCount = (unsigned int)g_Rva0130AD10.m_code >> 28;
				g_Rva0130AF60.m_source = g_Rva0130AD10.m_source;
				g_Rva0130AF60.m_code =
					(g_Rva0130AD10.m_code & 0x0FFFFFFF) - packetCount;
				g_Rva0130AF60.m_value = g_Rva0130AD10.m_value;
				comm->m_tickB = g_Rva0130AD10.m_source;

				for ( ; packetCount >= 0; --packetCount )
				{
					if ( packetCount > 0 )
					{
						--g_Rva0130AD10.m_length;
						g_Rva0130AF60.m_length =
							g_Rva0130AD10.m_body[ g_Rva0130AD10.m_length ];
					}
					else
					{
						g_Rva0130AF60.m_length =
							g_Rva0130AD10.m_length;
					}
					g_Rva0130AD10.m_length -= g_Rva0130AF60.m_length;
					memcpy( g_Rva0130AF60.m_body,
						g_Rva0130AD10.m_body + g_Rva0130AD10.m_length,
						g_Rva0130AF60.m_length );
					Rva008186C0( comm, &g_Rva0130AF60 );
					if ( Rva008187E0( comm, &g_Rva0130AF60 ) < 0 )
						packetCount = 0;
					if ( packetCount > 0
						&& savedSequence != comm->m_recvSequence )
						savedSequence = comm->m_recvSequence;
					++g_Rva0130AF60.m_code;
				}
				goto packet_done;
			}
			comm->m_tickB = g_Rva0130AD10.m_source;
			Rva008186C0( comm, &g_Rva0130AD10 );
			Rva008187E0( comm, &g_Rva0130AD10 );
packet_done:
			g_Rva0130AD10.m_length = -1;
		}

		if ( comm->m_state == 2
			&& tick - comm->m_tickA > 1000 )
			Rva00818620( comm );
		if ( comm->m_state == 4
			&& comm->m_sendAckOffset != comm->m_sendWriteOffset )
			Rva00817640( comm );
		if ( comm->m_state == 4
			&& tick - comm->m_tickB > 120000
			&& tick - comm->m_tickA < 2000 )
		{
			Rva007FE780Printf(
				"CommUDP: closing connection due to timeout\n" );
			Rva007FE780Printf(
				"CommUDP: tick=%d, rtick=%d, stick=%d\n",
				tick, comm->m_tickB, comm->m_tickA );
			Rva00816F60( comm );
		}
		if ( comm->m_state == 3
			&& *(unsigned short *)comm->m_peer == 2
			&& tick > comm->m_tickA + 1000 )
			CommUdpPoke( comm );
		if ( comm->m_flags == 0
			&& tick > comm->m_tickIdle + 250 )
		{
			comm->m_tickIdle = tick;
			comm->m_flags |= 4;
		}
		if ( comm->m_depth == 0 && comm->m_flags != 0 )
		{
			++comm->m_depth;
			if ( comm->m_notify != 0 )
				comm->m_notify( comm, comm->m_flags );
			comm->m_depth = comm->m_depth - 1;
			comm->m_flags = 0;
			tick = Rva007FEA00();
		}
		if ( comm->m_state == 4
			&& comm->m_sendAckOffset == comm->m_sendWriteOffset )
		{
			elapsed = tick - comm->m_tickA;
			if ( ( elapsed > 100
				&& comm->m_reportedSequence != comm->m_recvSequence )
				|| ( elapsed > 100
					&& comm->m_sendWriteOffset != comm->m_sendReadOffset )
				|| elapsed > 2500
				|| comm->m_recvCounter >= 0x800 )
			{
				comm->m_recvCounter = 0;
				Rva00818AD0( comm );
			}
		}
		goto second_next;
	}

	if ( g_Rva0130AD10.m_length >= 0
		&& g_Rva0130AD10.m_code == 5
		&& *(unsigned short *)address == 2 )
	{
		Rva007FE780Printf(
			"CommUDP: received poke packet (from=%08x)\n",
			( ( ( ( (unsigned int)address[ 4 ] << 8 )
				| address[ 5 ] ) << 8 | address[ 6 ] ) << 8 | address[ 7 ] ) );
		comm = g_Rva0130B188List;
		goto poke_check;
	poke_next:
		comm = comm->m_next;
	poke_check:
		if ( comm != 0 )
		{
			if ( comm->m_state == 2
				&& *(unsigned short *)comm->m_peer == 2
				&& comm->m_sessionHash == g_Rva0130AD10.m_value )
			{
				Rva007FE780Printf(
					"CommUdp: poke source = %08x -- forcing match\n",
					( ( ( ( (unsigned int)comm->m_peer[ 4 ] << 8 )
						| comm->m_peer[ 5 ] ) << 8 | comm->m_peer[ 6 ] ) << 8
						| comm->m_peer[ 7 ] ) );
				if ( socket == comm->m_socket )
				{
					Rva007FE780Printf(
						"CommUDP: changing peer to %08x:%d due to poke "
						"(was expecting %08x:%d)\n",
						( ( ( ( (unsigned int)address[ 4 ] << 8 )
							| address[ 5 ] ) << 8 | address[ 6 ] ) << 8
							| address[ 7 ] ),
						( (unsigned int)address[ 2 ] << 8 ) | address[ 3 ],
						( ( ( ( (unsigned int)comm->m_peer[ 4 ] << 8 )
							| comm->m_peer[ 5 ] ) << 8 | comm->m_peer[ 6 ] ) << 8
							| comm->m_peer[ 7 ] ),
						( (unsigned int)comm->m_peer[ 2 ] << 8 )
						| comm->m_peer[ 3 ] );
					memcpy( comm->m_peer, address, 0x10 );
					goto tail_done;
				}
			}
			goto poke_next;
		}
	}
tail_done:
	if ( selected != 0 && g_Rva0130AD10.m_length == 0 )
	{
		comm = selected;
		if ( comm->m_sessionHash == g_Rva0130AD10.m_value )
		{
			memcpy( comm->m_peer, address, 0x10 );
			comm->m_state = 4;
			CommUdpSetup( comm, &g_Rva0130AD10, address );
		}
	}
	return iResult;
}
