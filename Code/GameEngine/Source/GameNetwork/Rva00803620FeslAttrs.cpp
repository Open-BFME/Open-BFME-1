// cl: /GX- /GS
// FESL browser host: NAME/PORT/MAX-PLAYERS/TID/UGID attr pulls into sink@+0x18.
// Sibling of matched go @ 0x803730 (97B) and bfmeGoSA/SB/TCA. Large char
// buffers force /GS cookie frame (sub esp,0xB0) matching retail.

class Rva00803620Getter
{
public:
	char getStr( void *key, char *out, int size );
	void *getPtr( void *key, void *fallback );
};

class Rva00803620Sink
{
public:
	void apply( void *tid, char *name, void *port, void *maxPlayers, char *ugid );
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
	char name[0x80];
	char ugid[0x25];
	r->getStr( (void *)"NAME", name, 0x80 );
	void *port = r->getPtr( (void *)"PORT", 0 );
	void *maxPlayers = r->getPtr( (void *)"MAX-PLAYERS", 0 );
	void *tid = r->getPtr( (void *)"TID", 0 );
	r->getStr( (void *)"UGID", ugid, 0x25 );
	m_sink->apply( tid, name, port, maxPlayers, ugid );
}
