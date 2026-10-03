// cl: /O2 /GS
// ?handleGameLobbyReply@Rva007F65E0Owner@@QAEXPAVRva007E8810Message@@H@Z
// EA FESL client SDK ("jabba") -- game-detail reply handler for the game browser.
//
// Retail 0x007F65E0 (195 B, ret 8) is the thiscall body the 0x007F6870 lobby
// callback reaches with the message and a zero status, and the 0x007F6FC0 game
// wrapper reaches with the message and constant one: its two stack arguments
// are (message, flag) and the browser is ECX. The record built on entry is the
// 0x1B4-byte game record whose constructor is already matched at 0x007FBC60
// (Y4FeslGameDetailRecords.cpp); this row reads its first two fields as lid
// and gid. The lookup through [this+0x54] is the same polymorphic slot-21
// shape V2FeslBrowserLobbyCounts.cpp witnesses, and the listener slots are the
// same 0x1C notify / 0x14 onLobbyCounts pair.
//
// Byte evidence: dropping the banked `volatile` on the gid local is what makes
// this exact. The volatile bank kept gid memory-resident but scheduled the
// cookie store after the constructor-argument push; the plain local reproduces
// retail's push-ebp-before-cookie-store order at +0x18.

typedef __int64 FeslInt64;

class Rva007E88A0
{
public:
	bool method();
};

// 0x007E88B0 is the getter the ledger defines as ?m@Gen_007e88b0@@QAEHXZ
// (game/gen_small/fun_005.cpp); reach it through a cast like its other callers.
class Gen_007e88b0
{
public:
	int m( void );
};

class Rva007E8810Message
{
public:
	char m_head[ 0x28 ];
	int m_txn;
};

class Rva007FBC60Game
{
public:
	Rva007FBC60Game( Rva007E8810Message *msg );                       // 0x007FBC60

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
	FeslInt64 m_hu;                 // +0x128
	char m_v[ 0x40 ];               // +0x130
	char m_i[ 0x20 ];               // +0x170
	char m_platform[ 0x20 ];        // +0x190
	int m_join;                     // +0x1B0
};

struct Rva00802A90Query;

class Rva00802A90Owner
{
public:
	bool go( Rva00802A90Query *q, int flag, int id );                // 0x00802A90
};

class Rva007F65E0Listener
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void onLobbyCounts( int lid, int status );                // slot 5
	virtual void v6();
	virtual void notify( int lid, int gid, int status );              // slot 7
};

class Rva007F65E0Owner
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
	virtual Rva00802A90Owner *findGameLobby( int lid );               // slot 21

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
	if( ((Rva007E88A0 *)msg)->Rva007E88A0::method() )
		m_listener->notify( lid, gid, ((Gen_007e88b0 *)msg)->m() );
	if( Rva00802A90Owner *lobby = findGameLobby( lid ) )
	{
		msg = (Rva007E8810Message *)msg->m_txn;
		done = lobby->go( (Rva00802A90Query *)&game, flag, (int)msg );
	}
	m_listener->notify( lid, gid, 0 );
	if( done )
		m_listener->onLobbyCounts( lid, 0 );
}
