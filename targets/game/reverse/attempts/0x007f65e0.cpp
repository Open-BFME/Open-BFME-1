// ?handleGameLobbyReply@Rva007F65E0Owner@@QAEXPAVRva007E8810Message@@H@Z
// partial score=0.33 date=2026-09-21
// cl: /GS
// 0x007F65E0: FESL game-browser lobby/game-detail reply handler.
//
// The on-stack Rva007FBC60Game temporary (ctor at 0x007FBC60, matched in
// Y4FeslGameDetailRecords.cpp), the message error accessors pinned at
// 0x007E88A0/0x007E88B0, the polymorphic `this` dispatch at vslot 0x54
// (matching the findLobby-shaped lookup in V2FeslBrowserLobbyCounts.cpp),
// and the returned object's go(Query*,int,int) call (matched at 0x00802A90
// in Rva00802A90FeslBrowserQuery.cpp) place this squarely in the same FESL
// gamebrowser reply cluster. No caller, string, or vtable install proves
// the owning class, listener interface, or method name, so the remaining
// names are address-derived.

class Rva007E8810Message
{
public:
	bool hasError( void );                                            // 0x007E88A0
	int getError( void );                                             // 0x007E88B0

	char m_head[ 0x28 ];
	int m_txn;
};

class Rva007FBC60Game
{
public:
	Rva007FBC60Game( Rva007E8810Message *msg );

	int m_lid;                      // +0x000
	int m_gid;                      // +0x004
	Rva007E8810Message *m_msg;      // +0x008
	int m_ap;                       // +0x00C
	int m_jp;                       // +0x010
	int m_qp;                       // +0x014
	int m_mp;                       // +0x018
	int m_p;                        // +0x01C
	int m_nf;                       // +0x020
	bool m_f;                       // +0x024
	bool m_pw;                      // +0x025
	char m_n[ 0x80 ];               // +0x026
	char m_hn[ 0x80 ];              // +0x0A6
	__int64 m_hu;                   // +0x128
	char m_v[ 0x40 ];               // +0x130
	char m_i[ 0x20 ];               // +0x170
	char m_platform[ 0x20 ];        // +0x190
	int m_join;                     // +0x1B0
};

struct Rva00802A90Query;

class Rva00802A90Owner
{
public:
	bool go( Rva00802A90Query *q, int flag, int id );
};

class Rva007F65E0Listener
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void onLobbyCounts( int lid, int status );      // slot 5  (0x14)
	virtual void v06();
	virtual void notify( int lid, int gid, int status );    // slot 7  (0x1c)
};

class Rva007F65E0Owner
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
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
	virtual Rva00802A90Owner *findGameLobby( int lid );      // slot 21 (0x54)

	void handleGameLobbyReply( Rva007E8810Message *msg, int flag );

private:
	char m_pad000[ 0x18 ];
	Rva007F65E0Listener *m_listener;
};

void Rva007F65E0Owner::handleGameLobbyReply( Rva007E8810Message *msg, int flag )
{
	Rva007FBC60Game game( msg );
	bool done = false;
	int gid = game.m_gid;
	int lid = game.m_lid;

	if( msg->hasError() )
		m_listener->notify( lid, gid, msg->getError() );

	if( Rva00802A90Owner *lobby = findGameLobby( lid ) )
		done = lobby->go( (Rva00802A90Query *)( (char *)&game + 8 ), flag, msg->m_txn );

	m_listener->notify( lid, gid, 0 );

	if( done )
		m_listener->onLobbyCounts( lid, 0 );
}
