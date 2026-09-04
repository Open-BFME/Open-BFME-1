// cl: /GX-
// FESL browser host: pull TID / ALLOWED / PID / REASON from the attr getter,
// then forward to the +0x18 sink. Sibling of matched bfmeGoSA/SB @ 0x8037A0/E0
// and bfmeGoTCA @ 0x8036D0. Sink's second arg must be bool (not int) so MSVC
// stores al into the arg slot and keeps tid in ebx / pid in ebp.

class Rva00803730Getter
{
public:
	void *getPtr( void *key, void *fallback );
	bool getBool( const char *key, char flag );
};

class Rva00803730Sink
{
public:
	void apply( void *tid, bool allowed, void *pid, void *reason );
};

class Rva00803730Host
{
public:
	void go( Rva00803730Getter *r );

	char m_pad[0x18];
	Rva00803730Sink *m_sink;
};

void Rva00803730Host::go( Rva00803730Getter *r )
{
	void *tid = r->getPtr( (void *)"TID", 0 );
	bool allowed = r->getBool( "ALLOWED", 0 );
	void *pid = r->getPtr( (void *)"PID", 0 );
	void *reason = r->getPtr( (void *)"REASON", 0 );
	m_sink->apply( tid, allowed, pid, reason );
}
