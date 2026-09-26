// cl: /GX- /GS
// FESL browser entry-slot store at retail RVA 0x00802550 (227B).
//
// The matched caller at 0x008017E0 is BfmeE1173::bfmeHit1173.  It selects a
// 0x30-byte slot, passes its first opaque record argument through unchanged,
// and passes the context in its +0x04 field as the second argument.  The
// existing decorated store declaration therefore remains (void *,int) at
// the ABI boundary; the second value is immediately viewed as the proven
// host receiver below, rather than being treated as an arbitrary integer.
//
// The record is not Rva007FBEF0GameRecord.  The matched
// Rva007F5010Player constructor at 0x007F5010 is the independently measured
// data-bearing layout used by this body: message +8, player id +0x0c, name
// +0x10, and the eight-byte UID +0x90.  Those four offsets are exactly the
// target's stores and append argument.  The short 0x34-byte UGID record and
// the long 0x007FBC60 game record have incompatible fields here.
//
// The host vector has pointer/count fields at +0x2b8/+0x2bc. Retail callers
// explicitly pass this host in ECX to 0x007F76D0, whose body ignores ECX.
// This neutral receiver view preserves that observed call-site contract; it
// does not establish a public member identity or replace the existing bfmeAt
// row. Likewise, the Player accessor name below is a neutral receiver view
// of a message-field helper also used by the existing GameRecord view.

class Rva007FBC30GameKey
{
public:
	int m_lid;
	int m_gid;
};

class Rva007F5010Player : public Rva007FBC30GameKey
{
public:
	bool rva007FBFB0( const char *key, char *dest, unsigned int destSize );

	void *m_msg;
	int m_pid;
	char m_name[ 0x80 ];
	unsigned int m_uidLow;
	unsigned int m_uidHigh;
};

class BfmeSlotCZ
{
public:
	int *m_bfmePointer;
	int m_bfmeTag;
};

class BfmeVecCZ
{
public:
	BfmeSlotCZ *m_bfmeStart;
	int m_bfmeCount;
};

class Rva00802550Host
{
public:
	int *rva007F76D0( BfmeVecCZ *vector, int index );

	char m_opaquePrefix[ 0x2b8 ];
	BfmeVecCZ m_bfmeVector;
};

class Rva00800290Buffer
{
public:
	void addPadded( int size );
	void addString( const char *text );
	void allocate();

	char *m_ptr;
	int m_size;
};

class Rva00800460Arena
{
public:
	void *claim( int size, bool align );
	char *append( const char *text );

	char *m_base;
	unsigned m_cap;
	unsigned m_used;
};

class BfmeSlot1173
{
public:
	void measure( Rva007F5010Player *record );
	void bfmeStore1173( void *recordValue, int hostValue );

	char m_bfme00[ 4 ];
	Rva00802550Host *m_host;
	int m_playerId;
	int m_unobserved0c;
	unsigned int m_uidLow;
	unsigned int m_uidHigh;
	Rva00800460Arena m_arena;
	char *m_name;
	char **m_keys;
};

void BfmeSlot1173::measure( Rva007F5010Player *record )
{
	char buf[ 0x40 ];
	BfmeVecCZ *vector;
	int count;
	int i;
	int *slot;

	( (Rva00800290Buffer *)&m_arena )->addString( record->m_name );
	vector = &m_host->m_bfmeVector;
	count = vector->m_bfmeCount;
	( (Rva00800290Buffer *)&m_arena )->addPadded( count * 4 );
	for( i = 0; i < count; i++ )
	{
		slot = m_host->rva007F76D0( vector, i );
		buf[ 0 ] = 0;
		if( record->rva007FBFB0( (const char *)slot, buf, 0x40 ) )
			( (Rva00800290Buffer *)&m_arena )->addString( buf );
	}
}

void BfmeSlot1173::bfmeStore1173( void *recordValue, int hostValue )
{
	char buf[ 0x40 ];
	Rva007F5010Player *record = (Rva007F5010Player *)recordValue;
	BfmeVecCZ *vector;
	int count;
	int i;
	char *key;

	m_host = (Rva00802550Host *)(unsigned int)hostValue;
	m_playerId = record->m_pid;
	m_uidLow = record->m_uidLow;
	m_uidHigh = record->m_uidHigh;
	measure( record );
	( (Rva00800290Buffer *)&m_arena )->allocate();
	m_name = m_arena.append( record->m_name );
	vector = &m_host->m_bfmeVector;
	count = vector->m_bfmeCount;
	m_keys = (char **)m_arena.claim( count * 4, true );
	for( i = 0; i < count; i++ )
	{
		key = (char *)m_host->rva007F76D0( vector, i );
		buf[ 0 ] = 0;
		if( !record->rva007FBFB0( key, buf, 0x40 ) )
			m_keys[ i ] = 0;
		else
			m_keys[ i ] = m_arena.append( buf );
	}
}
