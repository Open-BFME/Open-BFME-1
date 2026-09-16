// cl: /O2
// 0x007F7640: BfmeThingZI FESL game-browser entry reply handler.
//
// The retail caller and the 0x007FBC30 constructor establish the message and
// LID/GID key.  The 0x007F6A40 lookup establishes the entry type.  The "peri"
// assertion and the listener call at vtable slot 11 identify the remaining
// operations at this address.

class BfmeThingRF
{
public:
	void *bfmeGoRF( void *a, void *b );
};

class Rva007E8810Message : public BfmeThingRF
{
};

class Rva007FBC30GameKey
{
public:
	Rva007FBC30GameKey( Rva007E8810Message *msg );

	int m_lid;
	int m_gid;
};

struct BfmeEntryZI
{
	unsigned char m_pad0[ 0xc ];
	void *m_listenerB;
	void *m_listenerA;
};

struct Rva007F7640Results
{
	void *m_resultA;
	void * volatile m_resultBSpill;
};

struct Rva007F7640Locals
{
	Rva007FBC30GameKey m_key;
	Rva007F7640Results m_results;

	__forceinline Rva007F7640Locals( Rva007E8810Message *msg )
		: m_key( msg )
	{
	}
};

class BfmeListenerZI
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void onEntry( BfmeEntryZI *entry, int flag );
};

extern int g_bfmeKeyAVHC;
extern int g_bfmeKeyBVHC;

struct Rva007EB810Diag
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail( const char *expr, const char *file, int line );
};

extern Rva007EB810Diag *Rva007EB810Get();

class BfmeThingZI
{
public:
	BfmeEntryZI *bfmeFindZI( int key, int other );
	void rva007F7640( Rva007E8810Message *msg );

	char m_pad[ 0x1c ];
	BfmeListenerZI *m_listener;
};

void BfmeThingZI::rva007F7640( Rva007E8810Message *msg )
{
	Rva007F7640Locals locals( msg );
	locals.m_results.m_resultA = msg->bfmeGoRF( &g_bfmeKeyAVHC, 0 );
	void *resultB;
	resultB = msg->bfmeGoRF( &g_bfmeKeyBVHC, 0 );
	locals.m_results.m_resultBSpill = resultB;
	BfmeEntryZI *entry = bfmeFindZI( locals.m_key.m_lid, locals.m_key.m_gid );

	if( entry == 0 )
	{
		Rva007EB810Get()->fail(
			"peri",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowser.cpp",
			0x5df );
		return;
	}

	entry->m_listenerB = resultB;
	entry->m_listenerA = locals.m_results.m_resultA;
	m_listener->onEntry( entry, 0 );
}
