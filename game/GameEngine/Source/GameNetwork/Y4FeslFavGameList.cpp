// cl: /O2 /GS
// Retail 0x00809520: count recent FESL game records, send the GLST summary,
// then send one TADG message for each recent record.

class BfmeC994
{
public:
	BfmeC994( char *buffer, int capacity );

	char m_pad00[ 0x1c ];
	int m_category;
	char m_pad20[ 0x0c ];
	int m_pad2c;
	char m_pad30;
};

class BfmeThingCIB
{
public:
	void bfmeGoCIB( void *one, void *two );
};

class BfmeMsgVJH
{
public:
	virtual void handle();
	BfmeMsgVJH();

	char m_pad04[ 0x0c ];
	int m_value10;
	int m_value14;
	int m_value18;
	int m_category;
	char m_pad20[ 0x0c ];
	int m_pad2c;
	char m_pad30;
};

class BfmeThingVJH
{
public:
	void bfmeSendVJH( BfmeMsgVJH *message );
};

class Gen_007e86c0
{
public:
	void m();
};

extern int g_bfmeKeyVHE;
extern char g_bfmeLidKey[];
extern char g_bfmeNumGamesKey[];

struct Rva00809520Entry
{
	char m_pad00[ 0x14 ];
	int m_gameId;
	int m_lobbyId;
	unsigned int m_time;
};

class Gen0080AB50
{
public:
	void process( unsigned int timestamp );

	char m_pad00[ 0x04 ];
	BfmeThingVJH *m_sender;
	char m_pad08[ 0x10 ];
	Rva00809520Entry *m_entries[ 16 ];
	int m_pad58;
	int m_deadline;
	int m_pad60;
	int m_tid;
	char m_pad68[ 0x100 ];
	char m_status;
};

void Gen0080AB50::process( unsigned int timestamp )
{
	int recentCount = 0;
	Rva00809520Entry **entry = &m_entries[ 1 ];
	int groups = 4;

	do
	{
		Rva00809520Entry *item = entry[ -1 ];
		if ( item != 0 && timestamp - item->m_time < 3000 )
			++recentCount;
		item = entry[ 0 ];
		if ( item != 0 && timestamp - item->m_time < 3000 )
			++recentCount;
		item = entry[ 1 ];
		if ( item != 0 && timestamp - item->m_time < 3000 )
			++recentCount;
		item = entry[ 2 ];
		if ( item != 0 && timestamp - item->m_time < 3000 )
			++recentCount;
		entry += 4;
	}
	while ( --groups != 0 );

	char buffer[ 0x40 ];
	BfmeC994 summary( buffer, sizeof( buffer ) );
	BfmeThingCIB *summaryCIB = reinterpret_cast< BfmeThingCIB * >( &summary );
	summary.m_category = 'GLST';
	summaryCIB->bfmeGoCIB( &g_bfmeKeyVHE, (void *)m_tid );
	summaryCIB->bfmeGoCIB( g_bfmeLidKey, (void *)-2 );
	summaryCIB->bfmeGoCIB( g_bfmeNumGamesKey, (void *)recentCount );
	m_sender->bfmeSendVJH( reinterpret_cast< BfmeMsgVJH * >( &summary ) );

	BfmeMsgVJH message;
	message.m_category = 0x47444154;
	entry = m_entries;
	int remaining = 16;
	do
	{
		Rva00809520Entry *item = *entry;
		if ( item != 0 && timestamp - item->m_time < 3000 )
		{
			message.m_value10 = item->m_gameId;
			message.m_value14 = item->m_lobbyId;
			m_sender->bfmeSendVJH( &message );
		}
		++entry;
	}
	while ( --remaining != 0 );

	m_deadline = 0;
	m_tid = 0;
	m_status = 0;
	reinterpret_cast< Gen_007e86c0 * >( &message )->m();
	reinterpret_cast< Gen_007e86c0 * >( &summary )->m();
}
