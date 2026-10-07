class BfmeThingRF
{
public:
	void *bfmeGoRF( void *key, void *defaultValue );
};

// The lookup key passed to bfmeGoRF lives at 0x0112B568: retail holds "GID"
// there (between "SECRET" at 0x0112B560 and "MAX-PLAYERS" at 0x0112B56C). No
// name is recorded for it yet, so the address-derived g_0112B568 stands in.
char g_0112B568[] = "GID";

struct Rva00809500Sink
{
	char m_pad00[ 0x10 ];
	void *m_match;
};

struct Rva00809500Entry
{
	char m_pad00[ 4 ];
};

class Rva00809010Finder
{
public:
	Rva00809500Sink *find( Rva00809500Entry *entry );

	char m_pad00[ 0x18 ];
	Rva00809500Sink *m_sinks[ 16 ];
};

Rva00809500Sink *Rva00809010Finder::find( Rva00809500Entry *entry )
{
	void *match = reinterpret_cast< BfmeThingRF * >( entry )->bfmeGoRF(
		g_0112B568, 0 );
	for( int index = 0; index < 16; ++index )
	{
		Rva00809500Sink *sink = m_sinks[ index ];
		if( sink != 0 && sink->m_match == match )
			return sink;
	}
	return 0;
}
