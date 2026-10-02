// cl: /GS
// EA FESL client SDK ("jabba") -- Aries browser record reply handlers.
//
// Same translation-unit cluster as V2FeslTxnRequests.cpp; the browser object and
// its listener are the ones V2FeslBrowserEvents.cpp describes, and the record
// types are the ones V2FeslAriesRecords.cpp claims.
//
// WHY THIS FILE CARRIES /GS.  Both rows build a record BY VALUE on the stack --
// 0x94 bytes for the region record, 0xA0 for the lobby record -- and both open
// by stashing the dword at 0x012DBDB0 in the slot immediately above that buffer
// and end by handing it to 0x009F74F4 in ecx.  That is MSVC 7.1's /GS
// instrumentation, and the frame sizes (0x98 and 0xA4) are exactly record plus
// cookie, which is how the record SIZES corroborate the layouts already landed
// in V2FeslAriesRecords.cpp.
//
// WHAT THE BYTES SHOW.  Each row: bail if the message carries an error; bail if
// the message's transaction word at +0x28 does not match the one the browser
// recorded when it sized the array; build the record; take the next array slot
// with a bounds test that yields a NULL pointer when the index has run past the
// count (the `jl` reaches the address computation, the fall-through zeroes eax);
// hand record and browser to the element; and notify the listener once the index
// has reached the count.  Element strides 0x1C and 0x40 are immediates, and they
// are the same two strides the allocators in V2FeslArrayBlocks.cpp use for the
// same two arrays.
//
// WHAT THE BYTES CANNOT DECIDE.  Nothing names the element types or the methods.
// All names are address-derived.

// 0x007E88A0 is DEFINED in the ledger as ?valid@W3DVideoBuffer@@UAE_NXZ, and
// the matched ?videoBufferValue@Rva007F5A70Owner@@QAEHPAVW3DVideoBuffer@@@Z at
// 0x007F5A80 calls it directly on a W3DVideoBuffer*, so the qualified
// non-virtual call below is the spelling that mangles to the defining name.
// No game/ header declares W3DVideoBuffer.
class W3DVideoBuffer
{
public:
	virtual bool valid( void );                                       // 0x007E88A0
};

class Rva007E8810Message
{
public:
	int getError( void );                                             // 0x007E88B0
	int getInt( const char *key, int defaultValue );                  // 0x007E8900
	bool getString( const char *key, char *dest, int destSize );      // 0x007E8A80

	char m_head[ 0x28 ];
	int m_txn;
};

class Rva007F4E50Region
{
public:
	Rva007F4E50Region( Rva007E8810Message *msg );                     // 0x007F4E50
	int m_rid;
	int m_numGames;
	int m_numPlayers;
	char m_name[ 0x80 ];
	char m_locale[ 8 ];
};

class Rva007F4EF0Lobby
{
public:
	Rva007F4EF0Lobby( Rva007E8810Message *msg );                      // 0x007F4EF0
	int m_lid;
	int m_passing;
	int m_favoriteGames;
	int m_favoritePlayers;
	int m_maxGames;
	int m_numGames;
	char m_name[ 0x80 ];
	char m_locale[ 8 ];
};

class Rva007F6BA0
{
public:
	void clear();                                                     // 0x007F6BA0
	void *m_array;
	int m_count;
};

class Rva007F6C60
{
public:
	void clear();                                                     // 0x007F6C60
	void *m_array;
	int m_count;
};

class Rva007F77B0Block : public Rva007F6BA0
{
public:
	void allocate( int count );                                       // 0x007F77B0
};

class Rva007F7810Block : public Rva007F6C60
{
public:
	void allocate( int count );                                       // 0x007F7810
};

class Rva007F7980Browser;

struct Rva00802DF0Source
{
	int m_field0;
	char m_pad004[ 8 ];
	char m_name[ 0x80 ];
	char m_text[ 1 ];
};

class Rva00800290Buffer
{
public:
	void reset();
	void addPadded( int size );
	void addString( const char *text );
	void allocate();
	void append( const char *text );

	char *m_ptr;
	int m_size;
};

class Rva00802DF0Owner
{
public:
	void set( Rva00802DF0Source *source, int value );

	int m_field0;
	int m_field4;
	int m_field8;
	Rva00800290Buffer m_name;
	Rva00800290Buffer m_text;
};

struct BfmeSrcVCB
{
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	char m_bfmeTextA[ 0x80 ];
	char m_bfmeTextB[ 4 ];
};

class BfmeBufVCB
{
public:
	void bfmeAppendVCB( const char *s );
	char m_bfmePad[ 8 ];
};

class BfmeThingVCB
{
public:
	void bfmeInitVCB( BfmeSrcVCB *s, int a );
	char m_bfmePad[ 4 ];
	int m_bfme04;
	int m_bfme08;
	BfmeBufVCB m_bfmeBufA;
	BfmeBufVCB m_bfmeBufB;
	char m_bfmePad2[ 0x10 ];
	int m_bfme2c;
	int m_bfme30;
	int m_bfme34;
	int m_bfme38;
	int m_bfme3c;
};

class Rva007F7980Listener
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void onRegionCountDone( int status );                     // slot 3
	virtual void onLobbyCountDone( int status );                      // slot 4
};

class Rva007F7980Browser
{
public:
	void onRegion( Rva007E8810Message *msg );
	void onLobby( Rva007E8810Message *msg );

	void *m_vptr;
	char m_head[ 0x18 ];
	Rva007F7980Listener *m_listener;
	char m_pad[ 0x18 ];
	Rva007F77B0Block m_regions;
	int m_regionIndex;
	int m_regionTxn;
	Rva007F7810Block m_lobbies;
	int m_lobbyIndex;
	int m_lobbyTxn;
};

void Rva007F7980Browser::onRegion( Rva007E8810Message *msg )
{
	if( ((W3DVideoBuffer *)msg)->W3DVideoBuffer::valid() )
		return;
	if( msg->m_txn != m_regionTxn )
		return;

	Rva007F4E50Region record( msg );

	int index = m_regionIndex++;
	Rva00802DF0Owner *slot = ( index >= m_regions.m_count )
		? 0
		: (Rva00802DF0Owner *)( (char *)m_regions.m_array + index * 0x1C );
	slot->set( (Rva00802DF0Source *)&record, (int)this );
	if( m_regionIndex >= m_regions.m_count )
		m_listener->onRegionCountDone( 0 );
}

void Rva007F7980Browser::onLobby( Rva007E8810Message *msg )
{
	if( ((W3DVideoBuffer *)msg)->W3DVideoBuffer::valid() )
		return;
	if( msg->m_txn != m_lobbyTxn )
		return;

	Rva007F4EF0Lobby record( msg );

	int index = m_lobbyIndex++;
	BfmeThingVCB *slot = ( index >= m_lobbies.m_count )
		? 0
		: (BfmeThingVCB *)( (char *)m_lobbies.m_array + index * 0x40 );
	slot->bfmeInitVCB( (BfmeSrcVCB *)&record, (int)this );
	if( m_lobbyIndex >= m_lobbies.m_count )
		m_listener->onLobbyCountDone( 0 );
}

// Three C callback entries are distinct retail bodies separated by INT3 bytes.
// The old 49-byte generated claim incorrectly joined all three.
void Rva007F6FA0BrowserRegionReply( Rva007E8810Message *msg, Rva007F7980Browser *browser )
{
	browser->onRegion( msg );
}

void Rva007F6FB0BrowserLobbyReply( Rva007E8810Message *msg, Rva007F7980Browser *browser )
{
	browser->onLobby( msg );
}

// The third entry calls the game-detail handler at 0x007F65E0
// (Rva007F65E0GameReply.cpp). The message and constant one are its two stack
// arguments; the browser is ECX.
class Rva007F65E0Owner
{
public:
	void handleGameLobbyReply( Rva007E8810Message *msg, int flag );
};
void Rva007F6FC0BrowserGameReply( Rva007E8810Message *msg, Rva007F7980Browser *browser )
{
	((Rva007F65E0Owner *)browser)->handleGameLobbyReply( msg, 1 );
}
