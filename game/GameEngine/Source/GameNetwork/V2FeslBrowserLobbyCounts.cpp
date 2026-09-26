// EA FESL client SDK ("jabba") -- Aries browser lobby-count reply handler.
//
// Same translation-unit cluster as V2FeslTxnRequests.cpp; the browser and its
// listener are the ones V2FeslBrowserEvents.cpp describes.
//
// WHAT THE BYTES SHOW THAT THE OTHER BROWSER FILES DO NOT.  This row dispatches
// through `[this]` -- `mov edx,[esi] ; push arg ; mov ecx,esi ; call [edx+0x54]`
// -- so the browser object itself is POLYMORPHIC and carries a vptr at offset 0.
// V2FeslBrowserEvents.cpp and V2FeslBrowserRecords.cpp spell that same first
// dword; no member offset moves.  Slot 0x54/4 = 21 takes one int and returns a
// pointer that is null-tested before use, so it is a LOOKUP, not a fetch.
//
// The record built on entry is the sixteen-byte four-int record already claimed
// as Rva007F4F90LobbyCounts, and this row reads its SECOND field for the value
// it passes to the lookup and to the listener, and its FIRST field for the
// zero test that decides whether to notify.  Both are frame displacements into
// that object, so both are evidence.
//
// The listener slot here is 0x14/4 = 5, entered with two ints.
//
// WHAT THE BYTES CANNOT DECIDE.  Nothing names the browser, the listener slot,
// the lookup, or the element method at 0x00802CD0.  All names are address-derived.

class Rva007E8810Message
{
public:
	bool hasError( void );                                            // 0x007E88A0
	int getError( void );                                             // 0x007E88B0

	char m_head[ 0x28 ];
	int m_txn;
};

class Rva007F4F90LobbyCounts
{
public:
	Rva007F4F90LobbyCounts( Rva007E8810Message *msg );                // 0x007F4F90
	int m_numGames;
	int m_lid;
	int m_lobbyMaxGames;
	int m_lobbyNumGames;
};

class Rva00802CD0Element
{
public:
	void update( const Rva007F4F90LobbyCounts *counts, int txn );     // 0x00802CD0
	char m_pad[ 0x40 ];
};

class Rva007F7980Listener
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3( int status );
	virtual void v4( int status );
	virtual void onLobbyCounts( int lid, int status );                // slot 5
};

class Rva007F66B0Browser
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
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual Rva00802CD0Element *findLobby( int lid );                 // slot 21

	void onLobbyCounts( Rva007E8810Message *msg );

	char m_head[ 0x18 ];
	Rva007F7980Listener *m_listener;
};

void Rva007F66B0Browser::onLobbyCounts( Rva007E8810Message *msg )
{
	Rva007F4F90LobbyCounts counts( msg );

	int lid = counts.m_lid;
	if( msg->hasError() )
	{
		m_listener->onLobbyCounts( lid, msg->getError() );
		return;
	}

	Rva00802CD0Element *lobby = findLobby( lid );
	if( lobby )
		lobby->update( &counts, msg->m_txn );
	if( counts.m_numGames == 0 )
		m_listener->onLobbyCounts( lid, 0 );
}
