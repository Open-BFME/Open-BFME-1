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

class Rva007E8810Message
{
public:
	bool hasError( void );                                            // 0x007E88A0
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

class Rva00802DF0Element
{
public:
	void set( const Rva007F4E50Region *record, Rva007F7980Browser *browser ); // 0x00802DF0
	char m_pad[ 0x1C ];
};

class Rva00802810Element
{
public:
	void set( const Rva007F4EF0Lobby *record, Rva007F7980Browser *browser );  // 0x00802810
	char m_pad[ 0x40 ];
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
	if( msg->hasError() )
		return;
	if( msg->m_txn != m_regionTxn )
		return;

	Rva007F4E50Region record( msg );

	int index = m_regionIndex++;
	Rva00802DF0Element *slot = ( index >= m_regions.m_count )
		? 0
		: (Rva00802DF0Element *)( (char *)m_regions.m_array + index * 0x1C );
	slot->set( &record, this );
	if( m_regionIndex >= m_regions.m_count )
		m_listener->onRegionCountDone( 0 );
}

void Rva007F7980Browser::onLobby( Rva007E8810Message *msg )
{
	if( msg->hasError() )
		return;
	if( msg->m_txn != m_lobbyTxn )
		return;

	Rva007F4EF0Lobby record( msg );

	int index = m_lobbyIndex++;
	Rva00802810Element *slot = ( index >= m_lobbies.m_count )
		? 0
		: (Rva00802810Element *)( (char *)m_lobbies.m_array + index * 0x40 );
	slot->set( &record, this );
	if( m_lobbyIndex >= m_lobbies.m_count )
		m_listener->onLobbyCountDone( 0 );
}
