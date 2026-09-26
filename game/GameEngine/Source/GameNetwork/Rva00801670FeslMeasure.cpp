// cl: /GX- /GS
// FESL game-browser record measurement at retail 0x00801670.
//
// The enclosing object is the BfmeThingVHW family: the matched
// BfmeThingVHW::bfmeClearVHW body finishes by writing the 0x0112C358 vtable
// at +0. The independently decoded 0x00801CB0/523 generated caller writes
// the host pointer at +0x04 before calling this body at its +0x2B. That caller
// also reads the same long record's N/HN/V and join fields. It is boundary
// evidence, not a recovered public caller name. The method name remains
// address-derived because no public
// source name for this slot was recovered.
//
// The helper at 0x007F76D0 is already matched as the bfmeAt body.  Its body
// reads the vector and index from [esp+4]/[esp+8] and returns with ret 8, but
// every named demangler-family caller loads the host into ECX before those
// pushes.  This neutral receiver view preserves that proven source ABI while
// making no claim about an unrecovered public helper class name.

class Rva00800290Buffer
{
public:
	void addPadded( int size );
	void addString( const char *text );

	char *m_ptr;
	int m_size;
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

class Rva00801670Host
{
public:
	int *rva007F76D0( BfmeVecCZ *vector, int index );

	unsigned char m_unreconstructed00[0x2A8];
	BfmeVecCZ m_gameKeys;
};

typedef __int64 FeslInt64;

// This is the data-bearing record from the matched Rva007FBC60Game
// constructor.  Its message is at +8, N/HN/V are at +26/+A6/+130, and the
// platform buffer used by the matched +0x7FBE70 accessor is at +190.  The
// short Rva007FBEF0GameRecord is a different 0x34-byte UGID record and is not
// used as this body's argument view.
class Rva007FBC60Game
{
public:
	char *rva007FBE70();
	bool rva007FBE80( const char *key, char *dest, unsigned destSize );

	int m_lid;
	int m_gid;
	void *m_msg;
	int m_ap;
	int m_jp;
	int m_qp;
	int m_mp;
	int m_p;
	int m_nf;
	bool m_f;
	bool m_pw;
	char m_n[ 0x80 ];
	char m_hn[ 0x80 ];
	FeslInt64 m_hu;
	char m_v[ 0x40 ];
	char m_i[ 0x20 ];
	char m_platform[ 0x20 ];
	int m_join;
};

class BfmeThingVHW
{
public:
	void rva00801670( Rva007FBC60Game *rec );

	void *m_bfmeVfptr;
	Rva00801670Host *m_bfme04;
	char m_bfmePad08[8];
	Rva00800290Buffer m_bfme10;
};

void BfmeThingVHW::rva00801670( Rva007FBC60Game *rec )
{
	char slot[0x40];
	int count;
	int i;
	BfmeVecCZ *vector;
	char *key;

	m_bfme10.addString( rec->m_n );
	m_bfme10.addString( rec->m_hn );
	m_bfme10.addString( rec->m_v );
	if( rec->rva007FBE70() )
		m_bfme10.addPadded( 0x28 );
	else
		m_bfme10.addPadded( 0x10 );

	vector = &m_bfme04->m_gameKeys;
	count = vector->m_bfmeCount;
	m_bfme10.addPadded( count * 4 );
	for( i = 0; i < count; i++ )
	{
		key = (char *)m_bfme04->rva007F76D0( vector, i );
		slot[0] = 0;
		if( rec->rva007FBE80( key, slot, 0x40 ) )
			m_bfme10.addString( slot );
	}
}
