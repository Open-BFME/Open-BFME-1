// cl: /DNDEBUG /MD
//
// Retail 0x0080A940: fill a FESL game-browser record from a message -- TID,
// FAV-GAME-UID, then two clock samples off Rva007E9B70Get vslot 2.

class Rva007E8810Message
{
public:
	int getInt( const char *key, int defaultValue );
	bool getString( const char *key, char *dest, int destSize );
};

struct Rva007E9B70Obj
{
	virtual void v0();
	virtual void v1();
	virtual unsigned int now();
};

Rva007E9B70Obj *Rva007E9B70Get();

class Rva0080A940Owner
{
public:
	void initFromMessage( Rva007E8810Message *msg );
	void finish();

	char m_gap00[ 0x5C ];
	unsigned int m_t0;       // +0x5C
	unsigned int m_t1;       // +0x60
	int m_tid;               // +0x64
	char m_favGameUid[ 0x100 ]; // +0x68
	char m_gap168[ 1 ];      // +0x168
};

void Rva0080A940Owner::initFromMessage( Rva007E8810Message *msg )
{
	m_tid = msg->getInt( "TID", 0 );
	msg->getString( "FAV-GAME-UID", m_favGameUid, 0x100 );
	m_t0 = Rva007E9B70Get()->now() + 0x5DC;
	m_t1 = Rva007E9B70Get()->now() + 0x64;
	m_gap168[ 0 ] = 0;
	finish();
}
