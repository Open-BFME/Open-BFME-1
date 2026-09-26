// cl: /GX- /GS
// partial score=0.65 date=2026-09-09
// ?notify@Rva00802A90Elem@@QAEXPAURva00802A90Query@@PAXHH@Z
// FESL game-browser record notification body, retail RVA 0x00801CB0.
// The owner and record identities are established by the adjoining
// Rva00802A90FeslBrowserQuery and Rva00801670FeslMeasure TUs.

struct Rva00802A90Query
{
	int m_lid;
	int m_gid;
	char m_pad08[0x10];
	int m_p;
	int m_mp;
	char m_pad20[4];
	char m_flag24;
	char m_flag25;
	char m_name[0x80];
	char m_hostName[0x80];
	__int64 m_host;
	char m_version[0x40];
	char m_data170[0x20];
	char m_platform[0x20];
	int m_join;
	int m_field1B4;
	int m_field1B8;
	int m_field1BC;
	int m_field1C0;
	int m_field1C4;
	int m_field1C8;
	int m_field1CC;
	int m_field1D0;
	int m_field1D4;
	int m_field1D8;
	int m_field1DC;
	int m_field1E0;
	int m_field1E4;
	int m_field1E8;
	int m_field1EC;
	int m_field1F0;
	int m_field1F4;
	int m_field1F8;
	int m_field1FC;
	int m_field200;
	int m_field204;
	int m_field208;
	int m_field20C;
	int m_field210;
	int m_field214;
	int m_field218;
	int m_field21C;
	int m_field220;
	int m_field224;
	int m_field228;
	int m_field22C;
	int m_field230;
	int m_field234;
	int m_field238;
	int m_field23C;
	int m_field240;
	int m_field244;
	int m_field248;
	int m_field24C;
	int m_field250;
	int m_field254;
	int m_field258;
	int m_field25C;
	int m_field260;
	int m_field264;
	int m_field268;
	int m_field26C;
	int m_field270;
	int m_field274;
	int m_field278;
	int m_field27C;
	int m_field280;
	int m_field284;
	int m_field288;
	int m_field28C;
	int m_field290;
	int m_field294;
	int m_field298;
	int m_field29C;
	int m_field2A0;
	int m_field2A4;
	int m_field2A8;
	int m_field2AC;
};

class Rva00800290Buffer
{
public:
	void addPadded( int size );
	void addString( const char *text );
	void allocate();

	char *m_ptr;
	int m_size;
	int m_used;
};

class Rva00800460Arena
{
public:
	void *claim( int size, bool align );
	char *append( const char *text );

	char *m_base;
	unsigned m_capacity;
	unsigned m_used;
};

class Rva007FBC60Game
{
public:
	char *rva007FBE70();
	bool rva007FBE80( const char *key, char *dest, unsigned size );

	int m_lid;
	int m_gid;
	void *m_message;
	int m_ap;
	int m_jp;
	int m_qp;
	int m_mp;
	int m_p;
	int m_nf;
	bool m_flag;
	bool m_password;
	char m_name[0x80];
	char m_hostName[0x80];
	__int64 m_host;
	char m_version[0x40];
	char m_data170[0x20];
	char m_platform[0x20];
	int m_join;
};

class Rva00801670Host
{
public:
	struct Vector
	{
		int *m_start;
		int m_count;
	};

	int *rva007F76D0( Vector *vector, int index );

	char m_pad00[0x2A8];
	Vector m_gameKeys;
};

class BfmeThingVHW
{
public:
	void rva00801670( Rva007FBC60Game *record );

	void *m_vptr;
	Rva00801670Host *m_host;
	char m_pad08[8];
	Rva00800290Buffer m_buffer;
};

class Rva7F4CC0Child
{
public:
	void construct();
};

#pragma comment(linker, "/alternatename:?construct@Rva7F4CC0Child@@QAEXXZ=?d_007e86b0@@YAXXZ")

class Rva00801CB0Message : public Rva7F4CC0Child
{
public:
	void configure( void *value, void *cookie );

	void *m_vptr;
	int m_kind;
	char m_pad08[0x1C];
};

#pragma comment(linker, "/alternatename:?configure@Rva00801CB0Message@@QAEXPAX0@Z=?d_007e8730@@YAXXZ")

class Rva00801CB0Addr : public Rva7F4CC0Child
{
public:
	void parse( const char *text, int extra );

	void *m_vptr;
	void *m_value08;
	void *m_value0C;
};

class Rva00801B70State
{
public:
	void update( int value );
};

#pragma comment(linker, "/alternatename:?update@Rva00801B70State@@QAEXH@Z=?d_00801b70@@YAXXZ")

struct Rva00802A90Elem
{
public:
	void notify( Rva00802A90Query *, void *context, int flag, int id );

	void *m_vptr;
	Rva00801670Host *m_host;
	int m_gid;
	int m_lid;
	Rva00800290Buffer m_buffer;
	char m_pad1C[0x0C];
	char *m_name;
	char *m_hostName;
	char *m_version;
	char **m_keys;
	char m_pad38[0x0C];
	int m_field44;
	int m_field48;
	char m_pad4C[4];
	int m_field50;
	int m_field54;
	int m_field58;
	int m_field5C;
	void *m_message;
	char m_field64;
	char m_field65;
	char m_pad66[2];
	int m_field68;
	char m_pad6C[4];
	int m_field70;
	int m_field74;
	int m_field78;
};

void Rva00802A90Elem::notify( Rva00802A90Query *query, void *context,
	int initialize, int )
{
	Rva007FBC60Game *record = (Rva007FBC60Game *)query;
	m_host = (Rva00801670Host *)context;
	m_lid = query->m_lid;
	m_gid = query->m_gid;
	((BfmeThingVHW *)this)->rva00801670( record );

	Rva00800460Arena *arena = (Rva00800460Arena *)&m_buffer;
	((Rva00800290Buffer *)arena)->allocate();
	m_name = arena->append( record->m_name );
	m_hostName = arena->append( record->m_hostName );
	m_version = arena->append( record->m_version );

	char *platform = record->rva007FBE70();
	if( platform )
	{
		void *message = arena->claim( 0x28, true );
		m_message = message;
		if( message )
		{
			Rva7F4CC0Child *base = (Rva7F4CC0Child *)message;
			base->construct();
			*(int *)message = 0x0112B4B4;
			*(int *)((char *)message + 4) = 1;
			*(char *)((char *)message + 8) = 0;
			*(int *)((char *)message + 0x24) = 0;
		}
		((Rva00801CB0Message *)message)->configure( (void *)(unsigned)record->m_p, platform );
	}
	else
	{
		void *message = arena->claim( 0x10, true );
		m_message = message;
		if( message )
		{
			Rva7F4CC0Child *base = (Rva7F4CC0Child *)message;
			base->construct();
			*(int *)message = 0x011296B0;
			*(int *)((char *)message + 8) = 0;
			*(int *)((char *)message + 0xc) = 0;
			*(int *)((char *)message + 4) = 0;
		}
		((Rva00801CB0Addr *)message)->parse( record->m_data170, record->m_p );
	}

	Rva00801670Host *host = m_host;
	Rva00801670Host::Vector *vector = &host->m_gameKeys;
	int count = vector->m_count;
	m_keys = (char **)arena->claim( count * 4, true );
	for (int index = 0; index < count; ++index)
	{
		char *key = (char *)host->rva007F76D0( vector, index );
		char text[0x40];
		text[0] = 0;
		if (record->rva007FBE80( key, text, sizeof(text) ))
			m_keys[index] = arena->append( text );
		else
			m_keys[index] = 0;
	}

	m_field50 = record->m_mp;
	m_field54 = record->m_ap;
	m_field58 = record->m_jp;
	m_field5C = *(int *)((char *)record + 0x14);
	m_field64 = *(char *)((char *)record + 0x25);
	m_field65 = *(char *)((char *)record + 0x24);
	m_field68 = *(int *)((char *)record + 0x20);
	m_field70 = *(int *)((char *)record + 0x128);
	m_field74 = *(int *)((char *)record + 0x12C);
	m_field78 = record->m_join;
	if( !initialize )
	{
		((Rva00801B70State *)((char *)this + 0x3c))->update( m_field54 );
		m_field44 = 0;
		m_field48 = count;
	}
}
