// cl: /DNDEBUG /MD
//
// Retail 0x00809BF0: look the FESL message up in the LAN-game sink table; on a
// miss, emit an 'ECNL' transaction at depth 'magn'.  Either way stamp the
// message's status word and copy three dwords from the sink, then notify
// through the already-pinned triple at 0x007F93E0.

class Rva007E8810Message
{
public:
	int getInt( const char *key, int defaultValue );

	int m_gap00;
	int m_f04;
	int m_f08;
	int m_f0c;
	char m_gap10[ 0x10 ];
	int m_status;
};

struct Rva00809500Entry
{
	char m_body[ 4 ];
};

struct Rva00809500Sink
{
	int m_gap00;
	int m_f04;
	int m_f08;
	int m_f0c;
};

// 0x00809010 is a thiscall member of Rva00809010Finder (its matched body
// dereferences this+0x18), and the ledger's five callers prove that name.
// Retail calls it with ecx untouched, so `this` is already in place.
class Rva00809010Finder
{
public:
	Rva00809500Sink *find( Rva00809500Entry *entry );
};

class BfmeSinkSKA
{
public:
	void bfmeSendSKA( int category, int transactionId, int depth );
};

void *Rva007F93E0( void *a, void *b, void *c );

class Rva00809BF0Owner
{
public:
	void notify( Rva00809500Entry *entry );

	int m_gap00;
	BfmeSinkSKA *m_sink;
	char m_gap08[ 8 ];
	void *m_field10;
};

void Rva00809BF0Owner::notify( Rva00809500Entry *entry )
{
	Rva00809500Sink *sink;
	Rva007E8810Message *msg;

	msg = (Rva007E8810Message *)entry;
	sink = reinterpret_cast< Rva00809010Finder * >( this )->find( entry );
	if ( sink == 0 )
	{
		m_sink->bfmeSendSKA( 'ECNL', msg->getInt( "TID", 0 ), 'ngam' );
	}
	msg->m_status = (int)0xC0000000;
	msg->m_f04 = sink->m_f04;
	msg->m_f08 = sink->m_f08;
	msg->m_f0c = sink->m_f0c;
	Rva007F93E0( msg, "->L", m_field10 );
}
