// ?rva007F7640@BfmeThingZI@@QAEXPAVRva007E8810Message@@@Z
// partial score=0.87 date=2026-09-13
// Open-BFME5: BfmeThingZI method, retail 0x007F7640. Builds an
// Rva007FBC30GameKey (Y4FeslGameRecords.cpp) from the incoming message,
// resolves two VHC listener callbacks through the message's own bfmeGoRF
// (BfmeThingRF::bfmeGoRF, BfmeConv908.cpp), looks the key up via the matched
// bfmeFindZI (BfmeOneHundredFiftyEight.cpp), asserts "peri" in
// gamebrowser.cpp:0x5DF when the entry is missing, otherwise stores both
// listener results into the entry and notifies m_listener (vtable slot 11).

class Rva007E8810Message
{
public:
	void *bfmeGoRF( void *a, void *b );   // BfmeThingRF::bfmeGoRF, 0x007E8900
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
	unsigned char m_pad0[0xc];
	void *m_listenerB;   // +0xc
	void *m_listenerA;   // +0x10
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
	virtual void onEntry( BfmeEntryZI *entry, int flag );   // slot 11, +0x2c
};

extern int g_bfmeKeyAVHC;
extern int g_bfmeKeyBVHC;

class Rva007EB810Diag
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

	char m_bfmePad[0x1c];
	BfmeListenerZI *m_listener;
};

void BfmeThingZI::rva007F7640( Rva007E8810Message *msg )
{
	Rva007FBC30GameKey key( msg );
	void * volatile resultA;
	void * volatile resultBSpill;
	resultA = msg->bfmeGoRF( &g_bfmeKeyAVHC, 0 );
	void *resultB = msg->bfmeGoRF( &g_bfmeKeyBVHC, 0 );
	resultBSpill = resultB;
	BfmeEntryZI *entry = bfmeFindZI( key.m_lid, key.m_gid );

	if( entry == 0 )
	{
		Rva007EB810Get()->fail( "peri",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowser.cpp",
			0x5df );
		return;
	}

	entry->m_listenerB = resultB;
	entry->m_listenerA = resultA;
	m_listener->onEntry( entry, 0 );
}
