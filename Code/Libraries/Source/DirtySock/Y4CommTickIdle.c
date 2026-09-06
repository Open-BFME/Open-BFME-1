// cl: /Od /GZ /GS /MD /DNDEBUG
/* EA DirtySock -- a second /Od /GZ comm transport, distinguished from the ring
 * one in Y4CommRingIdle.c by its LOCK OFFSET: +0x1E8 here against +0x1EC
 * there.  Four bytes is a whole field, so these are different objects and
 * therefore different transports, and that is the only reason the two files
 * are separate.  Placement of both bodies is by address neighbourhood; neither
 * reaches a string, so nothing names the module.
 */

int Rva007FEB00( void *lock );
void Rva007FECB0( void *lock );

/* The millisecond tick source. */
unsigned int Rva007FEA00( void );

struct Rva00814700Comm
{
	char m_head[ 0x48 ];
	void *m_socketAlias;             /* +0x48 */
	char m_gap4C[ 0x2C ];
	void *m_transport;               /* +0x78 */
	void *m_socket;                  /* +0x7C */
	unsigned char m_endpoint[ 0x08 ]; /* +0x80 */
	unsigned int m_handle;           /* +0x88 */
	char m_gap8C[ 0x04 ];
	int m_state;                     /* +0x90 */
	char m_gap94[ 0x04 ];
	int m_sequence;                  /* +0x98 */
	/* A SECOND RING, distinct from the one in Y4CommRingIdle.c: same shape --
	 * an offset advanced by a record size and reduced modulo a buffer size --
	 * but at +0x9C..+0xA8 rather than +0xB0..+0xBC.  Two rings in two
	 * transports, not one struct seen twice. */
	int m_recordSize;               /* +0x9C */
	int m_bufferSize;               /* +0xA0 */
	int m_readOffset;               /* +0xA4 */
	int m_writeOffset;              /* +0xA8 */
	void *m_allocA;                  /* +0xAC */
	char m_gapB0[ 0x04 ];
	int m_pending;                   /* +0xB4 */
	int m_countA;                   /* +0xB8 */
	int m_countB;                   /* +0xBC */
	int m_countC;                   /* +0xC0 */
	unsigned int m_lastTick;        /* +0xC4 */
	void *m_allocB;                  /* +0xC8 */
	char m_gapCC[ 0x04 ];
	unsigned int m_timeoutTick;     /* +0xD0 */
	char m_gapD4[ 0x04 ];
	int m_status;                   /* +0xD8 */
	char m_gapDC[ 0xBC ];
	unsigned int m_workerId;          /* +0x198 */
	char m_gap19C[ 0x4C ];
	char m_lock[ 4 ];               /* +0x1E8 */
	char m_gap1EC[ 0x24 ];
	int m_flags;                    /* +0x210 */
	void *m_value;                  /* +0x214 */
	void ( *m_callback )( struct Rva00814700Comm *, void * ); /* +0x218 */
};

void Rva008142B0( struct Rva00814700Comm *comm, void *socket )
{
	comm->m_socket = socket;
	comm->m_socketAlias = socket;
}

void Rva007FD3F0( void *socket );

int Rva00814400( struct Rva00814700Comm *comm )
{
	if ( comm->m_state == 3 )
		Rva008142B0( comm, 0 );

	if ( comm->m_socket != 0 )
	{
		Rva007FD3F0( comm->m_socket );
		Rva008142B0( comm, 0 );
	}

	comm->m_state = 1;
	return 0;
}

int Rva00814460( struct Rva00814700Comm *comm )
{
	if ( comm->m_state == 3 )
		Rva008142B0( comm, 0 );

	if ( comm->m_socket != 0 )
	{
		Rva007FD3F0( comm->m_socket );
		Rva008142B0( comm, 0 );
	}

	comm->m_state = 1;
	return 0;
}

int CommTCPUnlisten( struct Rva00814700Comm *comm );
void Rva007FEAA0( void *list );
void Rva007F0030( void *block );

void Rva008142D0( struct Rva00814700Comm *comm )
{
	if ( comm->m_state == 4 )
		CommTCPUnlisten( comm );

	if ( comm->m_socket != 0 )
	{
		Rva007FD3F0( comm->m_socket );
		Rva008142B0( comm, 0 );
	}

	Rva007FEAA0( comm->m_lock );
	Rva007F0030( comm->m_allocA );
	Rva007F0030( comm->m_allocB );
	Rva007F0030( comm );
}

void Rva008143A0( struct Rva00814700Comm *comm, void *value )
{
	comm->m_value = value;
	comm->m_flags |= 2;
}

__declspec(dllimport) void __stdcall Rva01358F30WorkerYield( int interval );
__declspec(dllimport) int __stdcall Rva01358EDC( void *handle, unsigned int mask );
__declspec(dllimport) int __stdcall Rva01358EB0( void *handle, unsigned int flags );
__declspec(dllimport) int __stdcall Rva01358CCC( void *handle );

struct Rva0081B830Transport
{
	char m_head[ 0x7c ];
	void *m_handle;
	char m_gap80[ 0x4c ];
	int m_state;
};

int Rva0081B830( struct Rva0081B830Transport *comm )
{
	if ( comm->m_state == 1 )
		return 0;

	if ( comm->m_state == 4 )
	{
		comm->m_state = 6;
		while ( comm->m_state == 6 )
			Rva01358F30WorkerYield( 0 );
	}
	comm->m_state = 8;
	while ( comm->m_state != 1 )
		Rva01358F30WorkerYield( 0 );

	if ( comm->m_handle != (void *)-1 )
	{
		Rva01358EDC( comm->m_handle, 2 );
		Rva01358EB0( comm->m_handle, 0x0f );
		Rva01358CCC( comm->m_handle );
		comm->m_handle = (void *)-1;
	}

	return 0;
}

void Rva00813E30( struct Rva00814700Comm *comm )
{
	Rva0081B830( comm->m_transport );
}

int Rva0081BA60( void *transport, const void *payload, int length );

int Rva00814040( struct Rva00814700Comm *comm, const void *payload,
	int length )
{
	return Rva0081BA60( comm->m_transport, payload, length );
}

int Rva0081B9D0( void *transport );
void Rva0081B9B0( void *transport );
int __stdcall Rva0081BDAE( unsigned int handle );

int Rva00813F20( struct Rva00814700Comm *comm )
{
	if ( comm->m_state == 5 || comm->m_state == 8 )
		Rva0081B9B0( comm->m_transport );

	if ( comm->m_state == 3 || comm->m_state == 5 || comm->m_state == 8 )
		Rva0081BDAE( comm->m_handle );

	return 0;
}

int Rva00813F90( struct Rva00814700Comm *comm )
{
	if ( comm->m_state == 3 || comm->m_state == 4 )
		return 2;

	if ( comm->m_state == 2 || comm->m_state == 8 )
		return 1;

	if ( comm->m_state == 7 || comm->m_state == 6 )
		return 3;

	if ( comm->m_state == 5 )
		return Rva0081B9D0( comm->m_transport );

	return 4;
}

int Rva0081BC80( void *transport, void *buffer, int size,
	unsigned int *when );

int Rva00814070( struct Rva00814700Comm *comm, void *buffer, int size,
	unsigned int *when )
{
	return Rva0081BC80( comm->m_transport, buffer, size, when );
}

int Rva0081BD40( void *transport, void *buffer, int size,
	unsigned int *when );

int Rva008140A0( struct Rva00814700Comm *comm, void *buffer, int size,
	unsigned int *when )
{
	return Rva0081BD40( comm->m_transport, buffer, size, when );
}

int Rva008144C0( struct Rva00814700Comm *comm )
{
	if ( comm->m_state == 2 || comm->m_state == 3 )
		return 2;

	if ( comm->m_state == 1 || comm->m_state == 5 )
		return 1;

	if ( comm->m_state == 4 )
		return 3;

	return 4;
}

int Rva00815830( struct Rva00814700Comm *comm )
{
	if ( comm->m_state == 1 || comm->m_state == 2 )
		return 2;

	if ( comm->m_state == 0 || comm->m_state == 4 )
		return 1;

	if ( comm->m_state == 3 )
		return 3;

	return 4;
}

void Rva00816910( struct Rva00814700Comm *comm )
{
	comm->m_countA = 0;
	comm->m_countB = 0;
	comm->m_readOffset = 0;
	comm->m_writeOffset = 0;
	comm->m_lastTick = Rva007FEA00() - 5000;
	comm->m_status = -1;
}

void Rva00815170( struct Rva00814700Comm *comm )
{
	comm->m_countC = 0;
	comm->m_lastTick = 0;
	comm->m_pending = -1;
	comm->m_readOffset = 0;
	comm->m_writeOffset = 0;
	comm->m_sequence = 0;
	comm->m_timeoutTick = Rva007FEA00() - 5000;
}

void Rva008155F0( struct Rva00814700Comm *comm, int status );

void Rva00815C90( struct Rva00814700Comm *comm )
{
	if ( !( ( ( ( ( comm->m_endpoint[ 4 ] << 8 ) | comm->m_endpoint[ 5 ] )
		<< 8 | comm->m_endpoint[ 6 ] ) << 8 | comm->m_endpoint[ 7 ] ) )
		|| !( ( comm->m_endpoint[ 2 ] << 8 ) | comm->m_endpoint[ 3 ] ) )
		return;

	if ( Rva007FEA00() - comm->m_lastTick >= 1000 )
	{
		if ( comm->m_state == 1 )
			Rva008155F0( comm, 16 );
		else if ( comm->m_state == 2 )
			Rva008155F0( comm, 17 );
	}
}

void Rva00815D40( struct Rva00814700Comm *comm )
{
	if ( comm->m_state == 3 && comm->m_countA == comm->m_countB
		&& Rva007FEA00() > comm->m_lastTick + 5000 )
	{
		Rva008155F0( comm, 19 );
	}
}

struct Rva00815DA0Comm;
void Rva00815DA0( struct Rva00815DA0Comm *comm );
void Rva00816490( struct Rva00814700Comm *comm );

void Rva00815BB0( struct Rva00814700Comm *comm )
{
	if ( comm->m_state == 1 || comm->m_state == 2 )
		Rva00815C90( comm );

	Rva00815DA0( (struct Rva00815DA0Comm *)comm );
	Rva00815D40( comm );
	Rva00816490( comm );

	if ( comm->m_flags == 0 && comm->m_value != 0 )
	{
		comm->m_flags++;
		if ( comm->m_callback != 0 )
			comm->m_callback( comm, comm->m_value );
		comm->m_flags--;
		comm->m_value = 0;
	}
}

struct Rva00815510Comm
{
	char m_head[ 0x7C ];
	void *m_socket;                  /* +0x7C */
	char m_gap80[ 0x10 ];
	int m_state;                     /* +0x90 */
	char m_gap94[ 0x18 ];
	void *m_allocA;                  /* +0xAC */
	char m_gapB0[ 0x10 ];
	void *m_allocB;                  /* +0xC0 */
	char m_gapC4[ 0x128 ];
	char m_lock[ 4 ];                /* +0x1EC */
};

int Rva008155A0( struct Rva00815510Comm *comm );
void Rva008154F0( struct Rva00815510Comm *comm, void *socket );

void Rva00815510( struct Rva00815510Comm *comm )
{
	if ( comm->m_state == 3 )
		Rva008155A0( comm );

	if ( comm->m_socket != 0 )
	{
		Rva007FD3F0( comm->m_socket );
		Rva008154F0( comm, 0 );
	}

	Rva007FEAA0( comm->m_lock );
	Rva007F0030( comm->m_allocA );
	Rva007F0030( comm->m_allocB );
	Rva007F0030( comm );
}

struct Rva00813E50Comm
{
	char m_head[ 0x7C ];
	int m_port;                      /* +0x7C */
	char m_gap80[ 0x10 ];
	int m_state;                     /* +0x90 */
	char m_gap94[ 0x04 ];
	char m_host[ 1 ];                /* +0x98 */
};

char *strchr( const char *text, int value );
char *strcpy( char *dest, const char *source );
void __stdcall Rva00813100( int port, int kind, struct Rva00813E50Comm *comm,
	int size, int a, int b );

int Rva00813E50( struct Rva00813E50Comm *comm, char *text )
{
	if ( comm->m_state != 2 )
		return -2;

	comm->m_port = 0;
	for ( ; *text >= '0' && *text <= '9'; text++ )
	{
		comm->m_port = comm->m_port * 10 + ( *text & 15 );
	}

	text = strchr( text, ':' );
	if ( text == 0 )
		return -3;

	strcpy( comm->m_host, text + 1 );
	comm->m_state = 3;
	Rva00813100( comm->m_port, 2, comm, 0x4000, 0, 0 );
	return 0;
}

void Rva00813A50( struct Rva00813E50Comm *comm, const char *text,
	char *output, int size, int flags );

int Rva00813D00( struct Rva00813E50Comm *comm, char *text )
{
	char address[ 64 ];

	if ( comm->m_state != 2 )
		return -2;

	if ( *text < '0' || *text > '9' )
	{
		Rva00813A50( comm, text, address, 64, 0 );
		text = address;
	}

	comm->m_port = 0;
	for ( ; *text >= '0' && *text <= '9'; text++ )
		comm->m_port = comm->m_port * 10 + ( *text & 15 );

	comm->m_host[ 0 ] = 0;
	comm->m_state = 4;
	Rva00813100( comm->m_port, 2, comm, 0x4000, 0, 0 );
	return 0;
}

struct Rva008151E0Address
{
	unsigned short m_family;
	unsigned short m_port;
	unsigned int m_address;
	unsigned int m_zeroA;
	unsigned int m_zeroB;
};

struct Rva008151E0Comm
{
	char m_head[ 0x48 ];
	void *m_socketAlias;             /* +0x48 */
	char m_gap4C[ 0x30 ];
	void *m_socket;                  /* +0x7C */
	struct Rva008151E0Address m_address; /* +0x80 */
	int m_state;                     /* +0x90 */
};

int Rva007FFCB0( struct Rva008151E0Address *address, const char *text );
void *Rva007FD2D0( int family, int type, int protocol );
int Rva007FD5C0( void *socket, struct Rva008151E0Address *address, int size );
int Rva007FDE80( void *socket, int flags, int interval, void *ref,
	int ( *callback )( unsigned int, int, struct Rva00814700Comm * ) );
int Rva00814700( unsigned int socket, int flags,
	struct Rva00814700Comm *ref );

int Rva008151E0( struct Rva008151E0Comm *comm, const char *text )
{
	void *socket;

	if ( comm->m_state != 1 || comm->m_socket != 0 )
		return -2;

	comm->m_address.m_family = 2;
	comm->m_address.m_port = 0;
	comm->m_address.m_address = 0;
	comm->m_address.m_zeroA = 0;
	comm->m_address.m_zeroB = 0;
	if ( Rva007FFCB0( &comm->m_address, text ) != 3 )
		return -3;

	Rva00815170( (struct Rva00814700Comm *)comm );
	socket = Rva007FD2D0( 2, 1, 0 );
	Rva008142B0( (struct Rva00814700Comm *)comm, socket );
	if ( comm->m_socket == 0 )
		return -4;

	Rva007FD5C0( comm->m_socket, &comm->m_address, 16 );
	Rva007FDE80( comm->m_socket, 2, 100, comm, Rva00814700 );
	comm->m_state = 2;
	return 0;
}

int Rva007FD510( void *socket, struct Rva008151E0Address *address,
	int size );
int Rva007FD7A0( void *socket, int backlog );

int Rva00814FE0( struct Rva008151E0Comm *comm, const char *text )
{
	int result;
	unsigned char address[ 16 ];
	void *socket;

	if ( comm->m_state != 1 || comm->m_socket != 0 )
		return -2;

	*(unsigned short *)&address[ 0 ] = 2;
	*(unsigned short *)&address[ 2 ] = 0;
	*(unsigned int *)&address[ 4 ] = 0;
	*(unsigned int *)&address[ 8 ] = 0;
	*(unsigned int *)&address[ 12 ] = 0;
	if ( ( Rva007FFCB0( (struct Rva008151E0Address *)address, text ) & 2 ) == 0 )
		return -3;

	Rva00815170( (struct Rva00814700Comm *)comm );
	socket = Rva007FD2D0( 2, 1, 0 );
	Rva008142B0( (struct Rva00814700Comm *)comm, socket );
	if ( comm->m_socket == 0 )
		return -4;

	result = Rva007FD510( comm->m_socket,
		(struct Rva008151E0Address *)address, 16 );
	if ( result < 0 )
	{
		Rva007FD3F0( comm->m_socket );
		Rva008142B0( (struct Rva00814700Comm *)comm, 0 );
		return -5;
	}

	Rva007FD7A0( comm->m_socket, 5 );
	Rva007FDE80( comm->m_socket, 2, 100, comm, Rva00814700 );
	comm->m_state = 3;
	return 0;
}

struct Rva00814D60Comm
{
	char m_head[ 0x6C ];
	unsigned int m_bindAddress;      /* +0x6C */
	unsigned int m_peerAddress;      /* +0x70 */
	unsigned short m_portA;          /* +0x74 */
	unsigned short m_portB;          /* +0x76 */
	char m_gap78[ 0x04 ];
	void *m_socket;                  /* +0x7C */
};

void Rva007FDB60( void *socket, int selector, void *address, int size );
int Rva007FE780( const char *format, ... );
extern char Rva012C4A80[];

void Rva00814D60( struct Rva00814D60Comm *comm )
{
	unsigned char address[ 16 ];

	Rva007FDB60( comm->m_socket, 0x70656572, address, 16 );
	comm->m_peerAddress = ( ( ( ( address[ 4 ] << 8 ) | address[ 5 ] )
		<< 8 | address[ 6 ] ) << 8 ) | address[ 7 ];
	comm->m_portA = ( address[ 2 ] << 8 ) | address[ 3 ];

	Rva007FDB60( comm->m_socket, 0x62696E64, address, 16 );
	comm->m_bindAddress = ( ( ( ( address[ 4 ] << 8 ) | address[ 5 ] )
		<< 8 | address[ 6 ] ) << 8 ) | address[ 7 ];
	comm->m_portA = ( address[ 2 ] << 8 ) | address[ 3 ];

	Rva007FE780( Rva012C4A80, comm->m_peerAddress, comm->m_portB,
		comm->m_bindAddress, comm->m_portA );
}

struct Rva00814540Record
{
	unsigned int m_tick;
	short m_length;
	char m_data[ 1 ];
};

struct Rva00814540Comm
{
	char m_head[ 0x7C ];
	void *m_socket;                  /* +0x7C */
	char m_gap80[ 0x10 ];
	int m_state;                     /* +0x90 */
	char m_gap94[ 0x24 ];
	int m_recordSize;                /* +0xB8 */
	int m_bufferSize;                /* +0xBC */
	int m_writeOffset;               /* +0xC0 */
	int m_readOffset;                /* +0xC4 */
	void *m_buffer;                  /* +0xC8 */
};

extern char Rva012C4AF0[];
extern char Rva012C4B0C[];
void *memcpy( void *dest, const void *source, unsigned int size );

int Rva00814540( struct Rva00814540Comm *comm, const void *payload,
	int length )
{
	int count;
	struct Rva00814540Record *record;

	if ( comm->m_state != 4 )
		return -2;

	if ( ( comm->m_writeOffset + comm->m_recordSize )
		% comm->m_bufferSize == comm->m_readOffset )
	{
		Rva007FE780( Rva012C4AF0 );
		return 0;
	}

	if ( length > comm->m_recordSize - 8 )
	{
		Rva007FE780( Rva012C4B0C, length );
		return -6;
	}

	if ( length == 0 )
	{
		count = ( ( comm->m_writeOffset + comm->m_bufferSize
			- comm->m_readOffset ) % comm->m_bufferSize )
			/ comm->m_recordSize;
		return count + 1;
	}

	record = (struct Rva00814540Record *)( (char *)comm->m_buffer
		+ comm->m_writeOffset );
	record->m_length = (short)length;
	memcpy( record->m_data, payload, length );
	record->m_tick = Rva007FEA00();
	comm->m_writeOffset = ( comm->m_writeOffset + comm->m_recordSize )
		% comm->m_bufferSize;
	Rva00814700( (unsigned int)comm->m_socket, 0,
		(struct Rva00814700Comm *)comm );
	count = ( ( comm->m_writeOffset + comm->m_bufferSize
		- comm->m_readOffset ) % comm->m_bufferSize )
		/ comm->m_recordSize;
	return count > 0 ? count : 1;
}

struct Rva00815DA0Record
{
	unsigned int m_address;
	int m_length;
	unsigned char m_type;
};

struct Rva00815DA0Comm
{
	char m_head[ 0x3C ];
	void ( *m_receiveCallback )( struct Rva00815DA0Comm *, void *, int, int );
	char m_gap40[ 0x3C ];
	void *m_socket;                  /* +0x7C */
	char m_gap80[ 0x10 ];
	int m_state;                     /* +0x90 */
	char m_gap94[ 0x04 ];
	int m_receiveSize;               /* +0x98 */
	int m_receiveThreshold;          /* +0x9C */
	int m_bufferSize;                /* +0xA0 */
	int m_readOffset;                /* +0xA4 */
	int m_writeOffset;               /* +0xA8 */
	void *m_buffer;                  /* +0xAC */
	char m_gapB0[ 0x20 ];
	int m_typeOffset;                /* +0xD0 */
	char m_gapD4[ 0x04 ];
	unsigned int m_status;           /* +0xD8 */
	char m_gapDC[ 0x134 ];
	int m_callbackDepth;             /* +0x210 */
	int m_flags;                     /* +0x214 */
};

int Rva007FDA50( void *socket, char *buffer, int length, int flags,
	char *from, int *fromLength );
void Rva00816020( struct Rva00815DA0Comm *comm,
	struct Rva00815DA0Record *record, const void *from );
void Rva00815FA0( struct Rva00815DA0Comm *comm,
	struct Rva00815DA0Record *record );
int Rva00816280( struct Rva00815DA0Comm *comm,
	struct Rva00815DA0Record *record );
extern char Rva012C4C24[];

void Rva00815DA0( struct Rva00815DA0Comm *comm )
{
	int result;
	int addressLength;
	int status;
	char *payload;
	unsigned char address[ 16 ];
	struct Rva00815DA0Record *record;

	status = 0;
	while ( comm->m_state >= 1 && comm->m_state <= 3 && status >= 0 )
	{
		record = (struct Rva00815DA0Record *)( (char *)comm->m_buffer
			+ comm->m_readOffset );
		payload = (char *)record + 8;
		addressLength = 16;
		result = Rva007FDA50( comm->m_socket, payload,
			comm->m_receiveSize, 0, (char *)address, &addressLength );
		if ( result > 0 )
		{
			record->m_length = result;
			record->m_address = ( ( ( ( address[ 8 ] << 8 ) | address[ 9 ] )
				<< 8 | address[ 10 ] ) << 8 ) | address[ 11 ];
			if ( record->m_type >= 0x10 && record->m_type <= 0x3F )
				Rva00816020( comm, record, address );
			else if ( record->m_type >= 0xC0 )
				Rva00815FA0( comm, record );
			else
			{
				status = Rva00816280( comm, record );
				if ( status == 1 && record->m_type >= 0x80
					&& record->m_type < 0xC0 )
				{
					Rva008155F0( (struct Rva00814700Comm *)comm,
						record->m_type + 0x40 );
				}
			}
		}
		else
		{
			if ( result < 0 )
			{
				Rva007FE780( Rva012C4C24, result );
				comm->m_state = 4;
				break;
			}
			break;
		}
	}
}

extern char Rva012C4BD8[];

int Rva00816280( struct Rva00815DA0Comm *comm,
	struct Rva00815DA0Record *record )
{
	unsigned char *destination;
	int offset;
	int count;
	int typeOffset;

	if ( record->m_type >= 0x40 && record->m_type < 0x80 )
	{
		offset = ( comm->m_readOffset + comm->m_bufferSize
			- comm->m_writeOffset ) % comm->m_bufferSize;
		count = ( comm->m_bufferSize - offset ) / comm->m_receiveSize;
		if ( count <= comm->m_receiveThreshold )
			return -1;
		comm->m_typeOffset = record->m_type - 0x40;
	}
	else
	{
		if ( ( comm->m_readOffset + comm->m_receiveSize )
			% comm->m_bufferSize == comm->m_writeOffset )
		{
			Rva007FE780( Rva012C4BD8 );
			return -1;
		}

		typeOffset = record->m_type - 0x80;
		if ( typeOffset == ( comm->m_status + 1 ) % 64 )
			comm->m_status = typeOffset;
		else if ( typeOffset == comm->m_status )
			return 1;
		else
			return 0;
	}

	destination = (unsigned char *)comm->m_buffer + comm->m_readOffset;
	memcpy( destination, record, comm->m_receiveSize );
	comm->m_callbackDepth++;
	comm->m_readOffset = ( comm->m_readOffset + comm->m_receiveSize )
		% comm->m_bufferSize;
	comm->m_flags |= 1;
	if ( comm->m_receiveCallback != 0 )
	{
		comm->m_receiveCallback( comm, destination + 9,
			*(int *)( destination + 4 ), *(int *)destination );
	}
	comm->m_callbackDepth--;
	return 1;
}

struct Rva008140D0Comm
{
	void *m_ops[ 14 ];               /* +0x00 */
	char m_gap38[ 0x14 ];
	char m_name[ 0x44 ];             /* +0x4C */
	int m_state;                     /* +0x90 */
	int m_field94;                   /* +0x94 */
	char m_gap98[ 0x04 ];
	int m_recordSizeA;               /* +0x9C */
	int m_bufferSizeA;               /* +0xA0 */
	char m_gapA4[ 0x08 ];
	void *m_bufferA;                 /* +0xAC */
	char m_gapB0[ 0x08 ];
	int m_recordSizeB;               /* +0xB8 */
	int m_bufferSizeB;               /* +0xBC */
	char m_gapC0[ 0x08 ];
	void *m_bufferB;                 /* +0xC8 */
	char m_gapCC[ 0x11C ];
	char m_lock[ 4 ];                /* +0x1E8 */
	char m_gap1EC[ 0x2C ];
};

void *Rva007F0000( int size );
void Rva007FEA20( void *lock );
void CommTCPResolve( void );
void Rva008143F0( void );
void Rva00814520( void );
extern char Rva012C4AAC[];
void *memset( void *dest, int value, unsigned int size );
int Rva00814EA0( struct Rva00814700Comm *comm, void *buffer, int size,
	unsigned int *when );
int Rva00814F70( struct Rva00814700Comm *comm, void *buffer, int size,
	unsigned int *when );

struct Rva008140D0Comm *Rva008140D0( int payloadSize, int countA,
	int countB )
{
	struct Rva008140D0Comm *comm;

	comm = (struct Rva008140D0Comm *)Rva007F0000( 0x218 );
	if ( comm == 0 )
		return 0;

	memset( comm, 0, 0x218 );
	comm->m_ops[ 0 ] = (void *)Rva008140D0;
	comm->m_ops[ 1 ] = (void *)Rva008142D0;
	comm->m_ops[ 2 ] = (void *)CommTCPResolve;
	comm->m_ops[ 3 ] = (void *)Rva008143F0;
	comm->m_ops[ 4 ] = (void *)Rva00814FE0;
	comm->m_ops[ 5 ] = (void *)Rva00814400;
	comm->m_ops[ 6 ] = (void *)Rva008151E0;
	comm->m_ops[ 7 ] = (void *)Rva00814460;
	comm->m_ops[ 8 ] = (void *)Rva008143A0;
	comm->m_ops[ 9 ] = (void *)Rva008144C0;
	comm->m_ops[ 10 ] = (void *)Rva00814520;
	comm->m_ops[ 11 ] = (void *)Rva00814540;
	comm->m_ops[ 12 ] = (void *)Rva00814EA0;
	comm->m_ops[ 13 ] = (void *)Rva00814F70;
	strcpy( comm->m_name, Rva012C4AAC );
	Rva007FEA20( comm->m_lock );

	comm->m_recordSizeA = payloadSize + 8;
	comm->m_recordSizeA = ( comm->m_recordSizeA + 3 ) & 0x7FFC;
	comm->m_bufferSizeA = comm->m_recordSizeA * countA;
	comm->m_bufferA = Rva007F0000( comm->m_bufferSizeA );
	comm->m_recordSizeB = payloadSize + 8;
	comm->m_recordSizeB = ( comm->m_recordSizeB + 3 ) & 0x7FFC;
	comm->m_bufferSizeB = comm->m_recordSizeB * countB;
	comm->m_bufferB = Rva007F0000( comm->m_bufferSizeB );
	Rva008142B0( (struct Rva00814700Comm *)comm, 0 );
	comm->m_state = 1;
	comm->m_field94 = 0;
	return comm;
}

void Rva00814770( struct Rva00814700Comm *comm, unsigned int tick );

/* The socket callback.  Same shape as the ring transport's -- handle and event
 * flags ignored, only the ref used, lock TRIED rather than taken -- with one
 * addition: it READS THE CLOCK ITSELF and hands the tick to the pump, rather
 * than letting the pump read it.  So every record the pump processes in one
 * call is stamped with a single consistent time, which it could not be if the
 * pump sampled per record.
 */
int Rva00814700( unsigned int socket, int flags, struct Rva00814700Comm *ref )
{
	struct Rva00814700Comm *comm;
	unsigned int uTick;

	comm = ref;

	if ( Rva007FEB00( comm->m_lock ) != 0 )
	{
		uTick = Rva007FEA00();
		Rva00814770( comm, uTick );
		Rva007FECB0( comm->m_lock );
	}

	return 0;
}

/* 0x00813780 guards a one-argument import behind an INVALID-HANDLE CHECK,
 * returning 0x8000002B instead of calling when the handle is -1.  The high bit
 * makes that a negative value, so callers testing for failure see it without
 * knowing the code.
 *
 * The import is not named: its thunk lands in an IAT slot the ledger has no
 * name for, so the declaration below is address-derived and asserts nothing
 * about which API it is.  What the bytes do fix is the shape -- one argument,
 * nothing cleaned at the call site, so __stdcall -- and that its result is
 * returned unchanged.
 */
int Rva00813780( unsigned int handle )
{
	int iResult;

	if ( handle != 0xFFFFFFFF )
		iResult = Rva0081BDAE( handle );
	else
		iResult = 0x8000002B;

	return iResult;
}

/* 0x00814F70 forwards four arguments unchanged and then ADVANCES THE RING ONLY
 * ON SUCCESS -- the cursor moves when the inner call returns a non-negative
 * result and stays put otherwise.  So a failed operation leaves the slot
 * available to be retried rather than consuming it, which is the whole reason
 * this wrapper exists separately from the body it calls.
 *
 * The test is `jl`, i.e. SIGNED: the inner call's negative returns are error
 * codes and its non-negative ones are counts.
 *
 * The four forwarded arguments are all 4-byte pushes and this body does not
 * look inside any of them, so their types are not recoverable here; they are
 * declared as plain words rather than guessed at.
 */
struct Rva00814EA0Record
{
	unsigned int m_tick;
	short m_length;
	char m_data[ 1 ];
};

int Rva00814EA0( struct Rva00814700Comm *comm, void *buffer, int size,
	unsigned int *when )
{
	struct Rva00814EA0Record *record;
	int copyLength;

	if ( comm->m_writeOffset == comm->m_readOffset )
		Rva00814700( 0, 0, comm );

	if ( comm->m_writeOffset == comm->m_readOffset )
		return -7;

	record = (struct Rva00814EA0Record *)( (char *)comm->m_allocA
		+ comm->m_writeOffset );
	if ( record->m_length < size )
		copyLength = record->m_length;
	else
		copyLength = size;
	memcpy( buffer, record->m_data, copyLength );
	if ( when != 0 )
		*when = record->m_tick;

	return record->m_length;
}

int Rva00814F70( struct Rva00814700Comm *comm, void *buffer, int size,
	unsigned int *when )
{
	int iResult;

	iResult = Rva00814EA0( comm, buffer, size, when );

	if ( iResult >= 0 )
	{
		comm->m_writeOffset = ( comm->m_writeOffset + comm->m_recordSize )
			% comm->m_bufferSize;
	}

	return iResult;
}

unsigned int strlen( const char *text );
int __stdcall Rva0081BDC6( int line, int address, char *destination,
	int countryCode, void *callParameters );

int Rva00813890( int line, int address, const char *destination,
	int countryCode )
{
	unsigned char callParameters[ 0x470 ];

	memset( callParameters, 0, sizeof( callParameters ) );
	*(int *)( callParameters + 0x00 ) = sizeof( callParameters );
	*(int *)( callParameters + 0x04 ) = 1;
	*(int *)( callParameters + 0x10 ) = 0x10;
	*(int *)( callParameters + 0x14 ) = 2;
	*(int *)( callParameters + 0x18 ) = 1;
	*(int *)( callParameters + 0x1C ) = 0;
	*(int *)( callParameters + 0x3C ) = 0x70;
	strcpy( (char *)callParameters + 0x70, destination );
	*(int *)( callParameters + 0x38 ) = strlen( (char *)callParameters + 0x70 );

	return Rva0081BDC6( line, address, (char *)callParameters + 0x70,
		countryCode, callParameters );
}

extern char Rva012C4A40[];
int __stdcall Rva0081BDC0( int line, int requestMode, int extension,
	int versionCount, void *capabilities, void *apiVersion );

int Rva008137C0( int line )
{
	int iResult;
	unsigned char capabilities[ 0x11C ];
	int iReturn;

	memset( capabilities, 0, sizeof( capabilities ) );
	*(int *)capabilities = sizeof( capabilities );
	iResult = Rva0081BDC0( line, 0, 0, 1, capabilities, Rva012C4A40 );

	if ( iResult != 0 )
		iReturn = -1;
	else
		iReturn = *(int *)( capabilities + 0x18 );

	return iReturn;
}

struct Rva008136C0ExtensionId
{
	int m_words[ 4 ];
};

int __stdcall Rva0081BDBA( int lineApplication, int deviceId,
	int apiLowVersion, int apiHighVersion, int *apiVersion,
	struct Rva008136C0ExtensionId *extensionId );
int __stdcall Rva0081BDB4( int lineApplication, int deviceId, void *line,
	int apiVersion, int extensionVersion, int callbackInstance,
	int privileges, int mediaModes, void *callParameters );

int Rva008136C0( int lineApplication, int deviceId, void *line,
	int callbackInstance, int privileges, int mediaModes )
{
	int iResult;
	int apiVersion;
	struct Rva008136C0ExtensionId extensionId;

	apiVersion = 0;
	iResult = Rva0081BDBA( lineApplication, deviceId, 0x10004, 0x20002,
		&apiVersion, &extensionId );
	if ( iResult != 0 )
		return iResult;

	return Rva0081BDB4( lineApplication, deviceId, line, apiVersion, 0,
		callbackInstance, privileges, mediaModes, 0 );
}

void Rva0081ACD0( void *transport );
void __stdcall Rva0081BDCC( int lineApplication );
__declspec(dllimport) int __stdcall Rva0135904CPostWorkerMessage(
	unsigned int workerId, unsigned int message, int first, int second );
__declspec(dllimport) void __stdcall Rva01358F30WorkerYield( int interval );
typedef void *( __stdcall *Rva008139A0WorkerHandleProc )( void );
typedef int ( __stdcall *Rva008139A0ReleaseHandleProc )( void *handle,
	int value, struct Rva00814700Comm *comm );

void Rva008139A0( struct Rva00814700Comm *comm )
{
	Rva0081ACD0( comm->m_transport );
	Rva0081BDCC( *(int *)( comm->m_endpoint + 4 ) );
	comm->m_state = 9;
	Rva0135904CPostWorkerMessage( comm->m_workerId, 0x12, 0, 0 );

	while ( comm->m_state == 9 )
		Rva01358F30WorkerYield( 0 );

	( *(Rva008139A0ReleaseHandleProc *)0x01358E44 )(
		( *(Rva008139A0WorkerHandleProc *)0x01358DDC )(), 0, comm );
}

struct Rva00812FD0Message
{
	int m_words[ 7 ];
};

__declspec(dllimport) int __stdcall Rva01359044DiscardMessage(
	struct Rva00812FD0Message *message, int window, int first, int last,
	int flags );
__declspec(dllimport) void *__stdcall Rva01358DC8ModuleHandle( int module );
__declspec(dllimport) int __stdcall Rva0135900CReadMessage(
	struct Rva00812FD0Message *message, int window, int first, int last );
__declspec(dllimport) int __stdcall Rva01359098TranslateMessage(
	struct Rva00812FD0Message *message );
__declspec(dllimport) int __stdcall Rva01358FC8DispatchMessage(
	struct Rva00812FD0Message *message );
int __stdcall Rva0081BDA2( void *lineApplication, void *module,
	void *callback, int name, void *deviceCount );

int Rva00812FD0( struct Rva00814700Comm *argument )
{
	struct Rva00812FD0Message message;
	int iResult;
	struct Rva00814700Comm *comm;

	comm = argument;
	Rva01359044DiscardMessage( &message, 0, 0, 0, 0 );
	iResult = Rva0081BDA2( comm->m_endpoint + 4,
		Rva01358DC8ModuleHandle( 0 ), (void *)0x00C13100, 0,
		comm->m_endpoint );

	if ( *(int *)comm->m_endpoint == 0 )
	{
		comm->m_state = 1;
		return 0;
	}

	comm->m_state = 2;
	while ( Rva0135900CReadMessage( &message, 0, 0, 0 ) != 0 )
	{
		Rva01359098TranslateMessage( &message );
		Rva01358FC8DispatchMessage( &message );
	}

	comm->m_state = 1;
	return 0;
}
