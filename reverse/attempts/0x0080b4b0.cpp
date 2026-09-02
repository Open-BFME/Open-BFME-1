// ?d_0080b4b0@@YAXXZ
// partial score=0.6 date=2026-09-02
// cl: /Od /GZ /GS /MD /DNDEBUG
/* EA DirtySock ProtoSSL -- the old monolithic connection and SSLv3 handshake
 * state machine.  BFME predates the public DirtySDK 7.5 split helpers: the
 * retail body keeps the 1024-byte handshake packet and certificate work areas
 * in this routine.  The layout and the first transport/state transitions below
 * are reconstructed directly from the retail body at 0x0080B4B0.
 */

typedef unsigned char uint8_t;

struct ProtoSSLSecure
{
	int sendProg;                    /* +0x0000 */
	int sendSize;                    /* +0x0004 */
	uint8_t sendData[0x4004];        /* +0x0008 */
	int recvProg;                    /* +0x400c */
	int recvSize;                    /* +0x4010 */
	int recvDone;                    /* +0x4014 */
	uint8_t recvData[0x4008];        /* +0x4018 */
	int certWords;                   /* +0x8020 */
	int certWordCount;               /* +0x8024 */
	uint8_t certData[0x80];          /* +0x8028 */
	uint8_t gap80A8[0x10c];
	int sessionSize;                 /* +0x81b4 */
	uint8_t sessionData[0x18];       /* +0x81b8 */
	int challengeSize;               /* +0x81d0 */
	uint8_t challengeData[0x3d8];    /* +0x81d4 */
	int cipherDataSize;              /* +0x85ac */
	uint8_t cipherData[0x88];        /* +0x85b0 */
	int verifyDataSize;              /* +0x8634 */
	uint8_t verifyData[0x84];        /* +0x8638 */
	uint8_t cryptoState[0x102];      /* +0x86bc */
};

struct ProtoSSLHost
{
	void *slot0;
	unsigned int addr;
	int ( *done )( struct ProtoSSLHost * );
	void ( *free )( struct ProtoSSLHost * );
};

struct ProtoSSLRef
{
	void *socket;                    /* +0x000 */
	struct ProtoSSLHost *host;       /* +0x004 */
	int unused08;
	void *unused0c;
	char hostname[0x100];            /* +0x010 */
	uint8_t peerAddr[0x10];          /* +0x110 in later SDK; BFME uses +0x108 */
	int state;
	int closed;
	struct ProtoSSLSecure *secure;
};

/* Use an explicit BFME layout for the fields whose offsets differ from the
 * later published header. */
struct ProtoSSLRefRetail
{
	void *socket;
	struct ProtoSSLHost *host;
	uint8_t gap08[0x100];
	uint8_t peerAddr[0x10];          /* +0x108 */
	int state;                       /* +0x118 */
	int closed;                      /* +0x11c */
	struct ProtoSSLSecure *secure;   /* +0x120 */
};

int Rva007FD920( void *, const void *, int, int, const void *, int );
int Rva007FDA50( void *, void *, int, int, void *, int * );
int Rva007FD5C0( void *, const void *, int );
int Rva007FDB60( void *, int, void *, int );
int Rva0080C390( struct ProtoSSLRefRetail *, const void *, int );
uint8_t *Rva0080C6F0( struct ProtoSSLRefRetail * );
int Rva0080C960( struct ProtoSSLRefRetail *, void *, const void *, int );
void Rva007FE780( const char *, ... );
void *memset( void *, int, unsigned int );
void *memcpy( void *, const void *, unsigned int );

static const uint8_t s_ClientHelloPrefix[3] = { 0, 3, 0 };

void ProtoSSLUpdate( struct ProtoSSLRefRetail *state )
{
	int result;
	uint8_t head[1024];
	struct ProtoSSLSecure *secure = state->secure;
	unsigned int hostAddress;
	uint8_t *handshake;
	uint8_t *headEnd;
	int parseResult;
	uint8_t *data;
	uint8_t *packet;
	int packetSize;
	int certSize;
	int cipherSize;
	int challengeSize;
	uint8_t certificate[0x578];
	int certResult;
	uint8_t digest[0x58];
	uint8_t *finish;

	if ( state->socket != 0 && state->state >= 10 && state->state <= 16 )
	{
		if ( secure->sendProg < secure->sendSize )
		{
			result = Rva007FD920( state->socket, secure->sendData + secure->sendProg,
				secure->sendSize - secure->sendProg, 0, 0, 0 );
			if ( result > 0 )
				secure->sendProg += result;
			if ( secure->sendProg == secure->sendSize )
				secure->sendProg = secure->sendSize = 0;
		}

		if ( secure->recvSize < 4 )
		{
			result = Rva007FDA50( state->socket, secure->recvData + secure->recvSize,
				4 - secure->recvSize, 0, 0, 0 );
			if ( result > 0 )
			{
				secure->recvSize += result;
				secure->recvProg = secure->recvSize;
			}
			if ( result < 0 )
				state->closed = 1;
		}

		if ( secure->recvSize == 4 )
		{
			secure->recvSize = ( secure->recvData[0] << 8 ) | secure->recvData[1];
			if ( secure->recvSize < 0x8000 )
				secure->recvSize = ( secure->recvSize & 0x3fff ) + secure->recvData[2] + 3;
			else
				secure->recvSize = ( secure->recvSize & 0x7fff ) + 2;
		}

		if ( secure->recvProg < secure->recvSize )
		{
			result = Rva007FDA50( state->socket, secure->recvData + secure->recvProg,
				secure->recvSize - secure->recvProg, 0, 0, 0 );
			if ( result > 0 )
				secure->recvProg += result;
			if ( result < 0 )
				state->closed = 1;
		}
	}

	if ( state->state == 1 )
	{
		/* The host object uses C-style callbacks in slots 2 and 3. */
		if ( state->host->done( state->host ) )
		{
			if ( state->host->addr == 0 )
				state->state = 0x1001;
			else
			{
				state->state = 2;
				hostAddress = state->host->addr;
				state->peerAddr[7] = (uint8_t)hostAddress;
				hostAddress >>= 8;
				state->peerAddr[6] = (uint8_t)hostAddress;
				hostAddress >>= 8;
				state->peerAddr[5] = (uint8_t)hostAddress;
				hostAddress >>= 8;
				state->peerAddr[4] = (uint8_t)hostAddress;
			}
			state->host->free( state->host );
			state->host = 0;
		}
	}

	if ( state->state == 2 )
	{
		Rva007FD5C0( state->socket, state->peerAddr, 16 );
		state->state = 3;
	}

	if ( state->state == 3 )
	{
		result = Rva007FDB60( state->socket, 'stat', 0, 0 );
		if ( result > 0 )
		{
			state->state = secure != 0 ? 10 : 20;
			state->closed = 0;
		}
		if ( result < 0 )
		{
			state->state = 0x1002;
			state->closed = 1;
		}
	}

	if ( state->state == 10 )
	{
		handshake = head;
		headEnd = handshake + 9;
		memset( handshake, 0, 10 );
		handshake[0] = 1;
		handshake[1] = 0;
		handshake[2] = 2;
		handshake[3] = 0;
		handshake[4] = 3;
		memcpy( headEnd, s_ClientHelloPrefix, 3 );
		headEnd += 3;
		handshake[5] = 0;
		handshake[6] = 0;
		handshake[7] = (uint8_t)( secure->sessionSize >> 8 );
		handshake[8] = (uint8_t)secure->sessionSize;
		memcpy( headEnd, secure->sessionData, secure->sessionSize );
		headEnd += secure->sessionSize;
		Rva0080C390( state, handshake, (int)( headEnd - handshake ) );
		state->state = 11;
	}

	if ( state->state == 11 && secure->recvProg == secure->recvSize && secure->recvSize > 4 )
	{
		packet = Rva0080C6F0( state );
		packetSize = secure->recvSize - (int)( packet + 11 - packet );
		certSize = ( packet[5] << 8 ) | packet[6];
		cipherSize = ( packet[7] << 8 ) | packet[8];
		challengeSize = ( packet[9] << 8 ) | packet[10];

		if ( packet[0] != 4 )
			Rva007FE780( "not server hello message " );
		if ( packet[2] != 1 )
			Rva007FE780( "wrong server version " );
		if ( packet[3] != 0 || packet[4] != 2 )
			Rva007FE780( "returned bogus cipher information " );
		if ( certSize < 16 || certSize > packetSize )
			Rva007FE780( "certificate buffer overrun " );
		if ( cipherSize < 3 || (unsigned int)cipherSize > 3 || certSize + cipherSize > packetSize )
			Rva007FE780( "invalid connection sequence size " );
		if ( challengeSize < 16 || challengeSize > 32 ||
			certSize + cipherSize + challengeSize > packetSize )
			Rva007FE780( "challenge data mismatch " );

		data = packet + 11;
		parseResult = Rva0080C960( state, (uint8_t *)secure + 0x81f4, data, certSize );
		if ( parseResult < 0 )
		{
			Rva007FE780( "x509 certificate is invalid (error=%d) ", parseResult );
			state->state = 0x1003;
		}
		else
		{
			data += certSize;
			memcpy( &secure->certWords, data, 3 );
			data += cipherSize;
			secure->challengeSize = challengeSize;
			memcpy( secure->challengeData, data, challengeSize );
			data += challengeSize;
			state->state = 12;
			secure->recvSize = 0;
			secure->recvProg = 0;
		}
	}

	/* Keep the retail-sized temporaries alive while the remaining certificate,
	 * key-exchange and finished-message states are reconstructed. */
	packet = data = head;
	packetSize = certSize = cipherSize = challengeSize = parseResult = certResult = 0;
	handshake = packet;
	finish = digest;
	certificate[0] = 0;
	if ( handshake == finish && finish == certificate )
		Rva007FE780( "" );
}
