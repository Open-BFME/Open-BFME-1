// cl: /GX- /GS
// FESL browser host: NAME/PORT/MAX-PLAYERS/TID/UGID attr pulls into sink@+0x18.
// Sibling of matched go @ 0x803730 (97B) and bfmeGoSA/SB/TCA. Large char
// buffers force /GS cookie frame (sub esp,0xB0) matching retail.

class Rva00803620Getter
{
};

// Retail calls this host's attr getters through the two ICF-folded bodies at
// RVA 0x007E8900 and 0x007E8A80, which the ledger owns under EA's own
// BfmeThingRF::bfmeGoRF and BfmeThingUPB::bfmeGoUPB (game/GameEngine/Source/
// Common/BfmeConv908.cpp and BfmeConv1339.cpp).  Both are thiscall with the
// receiver in ecx, exactly the shape the getter view used here had, so the
// calls are respelled to the defining names: the receiver pointer is unchanged
// and the DIR32 displacements stay put.  bfmeGoRF yields the raw int the old
// getInt view returned (eax is passed through) and bfmeGoUPB's third argument
// is the 0x80/0x25 buffer size the old getStr view took as an int.
class BfmeThingRF
{
public:
	void *bfmeGoRF( void *key, void *value );
};

class BfmeThingUPB
{
public:
	char bfmeGoUPB( void *key, char *out, void *size );
};

class Rva00803620Sink
{
public:
	void apply( int tid, char *name, int port, int maxPlayers, char *ugid );
};

class Rva00803620Host
{
public:
	void go( Rva00803620Getter *r );

	char m_pad[0x18];
	Rva00803620Sink *m_sink;
};

void Rva00803620Host::go( Rva00803620Getter *r )
{
	BfmeThingRF *rf = reinterpret_cast<BfmeThingRF *>(r);
	BfmeThingUPB *upb = reinterpret_cast<BfmeThingUPB *>(r);
	char name[0x80];
	char ugid[0x25];
	upb->bfmeGoUPB( (void *)"NAME", name, (void *)0x80 );
	int port = (int)rf->bfmeGoRF( (void *)"PORT", (void *)0 );
	int maxPlayers = (int)rf->bfmeGoRF( (void *)"MAX-PLAYERS", (void *)0 );
	int tid = (int)rf->bfmeGoRF( (void *)"TID", (void *)0 );
	upb->bfmeGoUPB( (void *)"UGID", ugid, (void *)0x25 );
	m_sink->apply( tid, name, port, maxPlayers, ugid );
}
