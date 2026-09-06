// ?d_007f49e0@@YAXXZ
// partial score=0.9 date=2026-09-05
// cl: /GS
// EA FESL Aries UDP sender from ariesudp.cpp, retail 0x007F49E0.

#include <string.h>

class Rva007EB810Diag
{
public:
	virtual void v0();
	virtual void report(const char *message);
	virtual void v2();
	virtual void fail(const char *expression, const char *file, int line);
};

Rva007EB810Diag *Rva007EB810Get();

class Rva007F49E0LocalSocket
{
public:
	virtual void v0();
	virtual void v1();
	virtual void send(const void *address, const void *data, int length);
};

class Rva007F49E0SharedSocket
{
public:
	virtual void v0();
	virtual void v1();
	virtual void send(const void *address, const void *data, int length, bool reliable);
};

struct Rva007F49E0Fap
{
	unsigned int m_sequence;
	unsigned int m_type;
	const unsigned char *m_data;
	unsigned int m_size;
	bool m_reliable;
	char m_pad11[ 3 ];
	char m_address[ 8 ];
	unsigned int m_mode;
};

class Rva007F49E0AriesUdp
{
public:
	int send( Rva007F49E0Fap *fap );

private:
	char m_pad00[ 4 ];
	Rva007F49E0LocalSocket m_socket;
	char m_pad08[ 8 ];
	Rva007F49E0SharedSocket *m_sharedSocket;
	unsigned int m_sequence;
};

int Rva007F49E0AriesUdp::send( Rva007F49E0Fap *fap )
{
	unsigned char packet[ 0x200 ];
	unsigned int pos = fap->m_size + 12;
	int result = 0;

	if( pos >= 0x200 )
	{
		result = -1;
		goto done;
	}

	packet[ 0 ] = (unsigned char)( fap->m_sequence >> 24 );
	packet[ 1 ] = (unsigned char)( fap->m_sequence >> 16 );
	packet[ 2 ] = (unsigned char)( fap->m_sequence >> 8 );
	packet[ 3 ] = (unsigned char)fap->m_sequence;
	packet[ 4 ] = (unsigned char)( fap->m_type >> 24 );
	packet[ 5 ] = (unsigned char)( fap->m_type >> 16 );
	packet[ 6 ] = (unsigned char)( fap->m_type >> 8 );
	packet[ 7 ] = (unsigned char)fap->m_type;
	packet[ 8 ] = (unsigned char)( pos >> 24 );
	packet[ 9 ] = (unsigned char)( pos >> 16 );
	packet[ 10 ] = (unsigned char)( pos >> 8 );
	packet[ 11 ] = (unsigned char)pos;
	memcpy( packet + 12, fap->m_data, fap->m_size );
	if( pos >= 0x200 )
		Rva007EB810Get()->fail(
			"pos < MAX_UDP_PACKET_LEN",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\ariesudp.cpp",
			121 );

	if( fap->m_mode == 0 )
	{
		m_socket.send( fap->m_address, packet, pos );
		goto done;
	}

	Rva007F49E0SharedSocket *socket = m_sharedSocket;
	if( socket == 0 )
	{
		Rva007EB810Get()->report( "Error: no shared socket registered." );
		result = -1;
		goto done;
	}

	if( fap->m_reliable )
		m_sequence = fap->m_mode;
	socket->send( fap->m_address, packet, pos, fap->m_reliable );

done:
	return result;
}
