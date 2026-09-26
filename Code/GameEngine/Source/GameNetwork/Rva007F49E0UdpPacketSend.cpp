// cl: /O2 /GS
// 0x007F49E0 (372 bytes): slot 3 of vtable 0x0112B3FC, an EA FESL ariesudp.cpp
// UDP send. It writes a 12-byte big-endian header (two record words and the
// total length) and the payload into a 0x200-byte packet, asserts
// "pos < MAX_UDP_PACKET_LEN" (ariesudp.cpp line 121), then hands the packet to
// the object at +4 when record+0x1c is zero, otherwise to the shared socket at
// +0x10 ("Error: no shared socket registered." when that is null).
// The owner class is not proven beyond the vtable slot; names stay address-derived.
#include <string.h>

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void report(const char *message);
	virtual void v2();
	virtual void fail(const char *expression, const char *file, int line);
};

Rva007EB810Diag *Rva007EB810Get();

class Rva007F49E0Member4
{
public:
	virtual void v0();
	virtual void v1();
	virtual void slot2(const void *address, const void *data, int length);
};

class Rva007F49E0SharedSocket
{
public:
	virtual void v0();
	virtual void v1();
	virtual void slot2(const void *address, const void *data, int length, bool flag);
};

struct Rva007F49E0Packet
{
	int dword_0;
	int dword_4;
	const unsigned char *m_data;
	unsigned int m_size;
	bool byte_10;
	char pad_11[ 3 ];
	char bytes_14[ 8 ];
	unsigned int dword_1c;
};

class Rva007F49E0VtableSlot3
{
public:
	virtual int send( Rva007F49E0Packet *record );

private:
	Rva007F49E0Member4 m_object4;
	char pad_08[ 8 ];
	Rva007F49E0SharedSocket *m_sharedSocket;
	unsigned int dword_14;
};

int Rva007F49E0VtableSlot3::send( Rva007F49E0Packet *record )
{
	unsigned char packet[ 0x200 ];
	unsigned int len = record->m_size + 12;

	if( len >= 0x200 )
		return -1;

	// The header is written through a running index and the index is
	// asserted after the payload copy; testing len twice lets VC7.1 fold the
	// assert away (retail keeps it, with pos spilled across the fail call).
	unsigned int pos = 0;
	packet[ pos++ ] = (unsigned char)( record->dword_0 >> 24 );
	packet[ pos++ ] = (unsigned char)( record->dword_0 >> 16 );
	packet[ pos++ ] = (unsigned char)( record->dword_0 >> 8 );
	packet[ pos++ ] = (unsigned char)record->dword_0;
	packet[ pos++ ] = (unsigned char)( record->dword_4 >> 24 );
	packet[ pos++ ] = (unsigned char)( record->dword_4 >> 16 );
	packet[ pos++ ] = (unsigned char)( record->dword_4 >> 8 );
	packet[ pos++ ] = (unsigned char)record->dword_4;
	packet[ pos++ ] = (unsigned char)( len >> 24 );
	packet[ pos++ ] = (unsigned char)( len >> 16 );
	packet[ pos++ ] = (unsigned char)( len >> 8 );
	packet[ pos++ ] = (unsigned char)len;
	memcpy( packet + pos, record->m_data, record->m_size );
	pos += record->m_size;
	if( !( pos < 0x200 ) )
		Rva007EB810Get()->fail(
			"pos < MAX_UDP_PACKET_LEN",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\ariesudp.cpp",
			121 );

	if( record->dword_1c == 0 )
	{
		m_object4.slot2( record->bytes_14, packet, pos );
		return 0;
	}

	Rva007F49E0SharedSocket *socket = m_sharedSocket;
	if( socket == 0 )
	{
		Rva007EB810Get()->report( "Error: no shared socket registered." );
		return -1;
	}

	if( record->byte_10 )
		dword_14 = record->dword_1c;
	socket->slot2( record->bytes_14, packet, pos, record->byte_10 );
	return 0;
}
