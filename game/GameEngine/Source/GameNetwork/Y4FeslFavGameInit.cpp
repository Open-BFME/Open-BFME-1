// cl: /DNDEBUG /MD
//
// Retail 0x0080A940: fill a FESL game-browser record from a message -- TID,
// FAV-GAME-UID, then two clock samples off Rva007E9B70Get vslot 2.

// Retail's integer field lookup is the one FESL attribute getter body at
// 0x007E8900, matched as BfmeThingRF::bfmeGoRF (Common/BfmeConv908.cpp); every
// other matched FESL caller spells it that way (see Y4FeslGameDetailRecords.cpp).
class BfmeThingRF
{
public:
	void *bfmeGoRF( void *key, void *defaultValue );
};

// Retail's string field lookup is the FESL getter body at 0x007E8A80, matched
// as BfmeThingUPB::bfmeGoUPB (Common/BfmeConv1339.cpp).  Retail calls it
// directly (mov ecx, msg) with the same three pushed arguments this call site
// builds, so the TU-local `getString` spelling is only an alias for it.
class BfmeThingUPB
{
public:
	char bfmeGoUPB( void *key, char *dest, void *destSize );
};

class Rva007E8810Message
{
public:
	char getString( const char *key, char *dest, int destSize );
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
	bool finish();

	char m_gap00[ 0x5C ];
	unsigned int m_t0;       // +0x5C
	unsigned int m_t1;       // +0x60
	int m_tid;               // +0x64
	char m_favGameUid[ 0x100 ]; // +0x68
	char m_gap168[ 1 ];      // +0x168
};

void Rva0080A940Owner::initFromMessage( Rva007E8810Message *msg )
{
	m_tid = (int)(long)((BfmeThingRF *)msg)->bfmeGoRF( (void *)"TID", (void *)0 );
	((BfmeThingUPB *)msg)->bfmeGoUPB( (void *)"FAV-GAME-UID", m_favGameUid, (void *)0x100 );
	m_t0 = Rva007E9B70Get()->now() + 0x5DC;
	m_t1 = Rva007E9B70Get()->now() + 0x64;
	m_gap168[ 0 ] = 0;
	finish();
}
