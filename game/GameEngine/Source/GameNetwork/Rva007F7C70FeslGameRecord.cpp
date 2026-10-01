// cl: /GS
// 0x007F7C70: FESL game-browser reply handler over a LID/GID record.
//
// The local record layout is fixed by its /GS frame: the established game-key
// base occupies the first eight bytes, followed by TYPE and a 0x100-byte
// REASON buffer.  The final call releases/reports the LID/GID pair through the
// existing 0x007F7C00 owner method.  The event and original method names are
// unavailable, so the handler name remains address-derived.

// Calls name each Rva007E8810Message helper by the ledger row at its pinned
// address (link_check.py near), the spelling the link resolves.
class BfmeThingRF
{
public:
	void *bfmeGoRF( void *one, void *two );                       // 0x007E8900
};

class BfmeThingUPB
{
public:
	char bfmeGoUPB( void *one, char *out, void *two );            // 0x007E8A80
};

class Rva007E8810Message
{
};

class Rva007FBC30GameKey
{
public:
	Rva007FBC30GameKey( Rva007E8810Message *msg );

	int m_lid;
	int m_gid;
};

class Rva007F7C70GameRecord : public Rva007FBC30GameKey
{
public:
	__forceinline Rva007F7C70GameRecord( Rva007E8810Message *msg )
		: Rva007FBC30GameKey( msg )
	{
		m_type = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"TYPE", (void *)0 );
		reinterpret_cast< BfmeThingUPB * >( msg )->bfmeGoUPB( (void *)"REASON", m_reason, (void *)(sizeof( m_reason )) );
	}

	int m_type;
	char m_reason[ 0x100 ];
};

class BfmeHostBT
{
public:
	void Rva007F7C70( Rva007E8810Message *msg );
	void bfmeReportBT( int first, int second );
};

void BfmeHostBT::Rva007F7C70( Rva007E8810Message *msg )
{
	Rva007F7C70GameRecord record( msg );
	bfmeReportBT( record.m_lid, record.m_gid );
}
