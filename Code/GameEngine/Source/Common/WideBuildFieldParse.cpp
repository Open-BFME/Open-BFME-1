// Seventy-six 30-byte __cdecl statics of the shape
//
//     push esi / mov esi,[esp+8] / push esi / call REL32 / add esp,4
//     push 0 / push offset TABLE / mov ecx,esi / call REL32 / pop esi / ret
//
// WHAT THE BYTES SHOW.  The single stack argument is passed straight on to a
// __cdecl callee (one push, `add esp,4` by us), then handed to a __thiscall
// two-argument member of a SECOND callee whose `this` is that same argument,
// with a fixed .rdata address as the first argument and a literal 0 as the
// second.  The second callee is the SAME function for all seventy-six members:
// 0x00850920, which reads a count at [this+0x80], bails at 16, stores the two
// arguments into two parallel 16-entry arrays at [this] and [this+0x40],
// bumps the count and `ret 8`.  That is a bounded pair-of-arrays appender.
//
// The .rdata block each member pushes is a table of 16-byte records
// {const char *token, void (*proc)(), const void *userData, unsigned offset}
// terminated by an all-zero record -- e.g. 0x00C899C8 is
// {"TimeForFullHeal", 0x0043D9B0, 0, 0x168}, {0,0,0,0}.  This is the
// engine's INI field-parse table, and the shape is the well-known
//
//     static void X::buildFieldParse( MultiIniFieldParse &p )
//     { Base::buildFieldParse( p ); p.add( theFieldParseTable, 0 ); }
//
// THE VARYING AXIS IS THE FIRST REL32 -- the base class's buildFieldParse.
// Seventy-six members over seventeen distinct base callees.  The table address
// also varies, but it is a DIR32 site: it is read from retail, not asserted.
//
// IDENTITY IS NOT RECOVERED.  Every name here is derived from an address, and
// the table contents are not modelled at all -- each table is an undefined
// extern whose only role is to make the compiler emit `push offset`.

class WideFieldParse
{
public:
	const char *m_token;
	void (*m_parse)();
	const void *m_userData;
	unsigned int m_offset;
};

class WideMulti
{
public:
	void add( const WideFieldParse *fields, unsigned int extraOffset );
};

#define WIDE_FIELD_PARSE_BASE( ADDR )                                     	class Gen##ADDR                                                       	{                                                                     	public:                                                               		static void buildFieldParse( WideMulti &p );                      	};

#define WIDE_FIELD_PARSE( NAME, BASE )                                    	extern const WideFieldParse WideTbl##NAME[];                          	class Rva##NAME                                                       	{                                                                     	public:                                                               		static void buildFieldParse( WideMulti &p );                      	};                                                                    	void Rva##NAME::buildFieldParse( WideMulti &p )                       	{                                                                     		Gen##BASE::buildFieldParse( p );                                  		p.add( WideTbl##NAME, 0 );                                        	}

WIDE_FIELD_PARSE_BASE( 00004052 )
WIDE_FIELD_PARSE_BASE( 00005245 )
WIDE_FIELD_PARSE_BASE( 00005B46 )
WIDE_FIELD_PARSE_BASE( 0000629E )
WIDE_FIELD_PARSE_BASE( 00012355 )
WIDE_FIELD_PARSE_BASE( 00012742 )
WIDE_FIELD_PARSE_BASE( 00015654 )
WIDE_FIELD_PARSE_BASE( 00019772 )
WIDE_FIELD_PARSE_BASE( 00022584 )
WIDE_FIELD_PARSE_BASE( 0002AF8B )
WIDE_FIELD_PARSE_BASE( 00031A20 )
WIDE_FIELD_PARSE_BASE( 000334F6 )
WIDE_FIELD_PARSE_BASE( 0003572E )
WIDE_FIELD_PARSE_BASE( 0003B7F0 )
WIDE_FIELD_PARSE_BASE( 0003BD86 )
WIDE_FIELD_PARSE_BASE( 0004B650 )

WIDE_FIELD_PARSE( 00115A80, 00019772 )
WIDE_FIELD_PARSE( 00116500, 00019772 )
WIDE_FIELD_PARSE( 00116960, 0003572E )
WIDE_FIELD_PARSE( 00118640, 0003572E )
WIDE_FIELD_PARSE( 001187C0, 0003572E )
WIDE_FIELD_PARSE( 00118E80, 0000629E )
WIDE_FIELD_PARSE( 00118FC0, 0000629E )
WIDE_FIELD_PARSE( 00119100, 0000629E )
WIDE_FIELD_PARSE( 00119240, 0000629E )
WIDE_FIELD_PARSE( 00119380, 0000629E )
WIDE_FIELD_PARSE( 0011B900, 0003572E )
WIDE_FIELD_PARSE( 0011BE30, 0003572E )
WIDE_FIELD_PARSE( 0011C030, 0003572E )
WIDE_FIELD_PARSE( 0011C860, 0000629E )
WIDE_FIELD_PARSE( 0011C9B0, 0000629E )
WIDE_FIELD_PARSE( 0011CD10, 0000629E )
WIDE_FIELD_PARSE( 0011EED0, 00012742 )
WIDE_FIELD_PARSE( 0011F000, 00012742 )
WIDE_FIELD_PARSE( 0011F0B0, 00012742 )
WIDE_FIELD_PARSE( 0011F160, 00012742 )
WIDE_FIELD_PARSE( 0011F5B0, 00012355 )
WIDE_FIELD_PARSE( 0011F660, 00012355 )
WIDE_FIELD_PARSE( 001210A0, 0000629E )
WIDE_FIELD_PARSE( 001F6EA0, 0003BD86 )
WIDE_FIELD_PARSE( 001FFB10, 0003BD86 )
WIDE_FIELD_PARSE( 002127E0, 0004B650 )
WIDE_FIELD_PARSE( 00213280, 0004B650 )
WIDE_FIELD_PARSE( 00214140, 00012355 )
WIDE_FIELD_PARSE( 00214620, 00012355 )
WIDE_FIELD_PARSE( 0021A280, 00015654 )
WIDE_FIELD_PARSE( 00220160, 00019772 )
WIDE_FIELD_PARSE( 0022B3B0, 00031A20 )
WIDE_FIELD_PARSE( 0022DB70, 00019772 )
WIDE_FIELD_PARSE( 0022F8A0, 000334F6 )
WIDE_FIELD_PARSE( 002469A0, 00031A20 )
WIDE_FIELD_PARSE( 00249D20, 00005245 )
WIDE_FIELD_PARSE( 0024E6C0, 00015654 )
WIDE_FIELD_PARSE( 00258FB0, 0002AF8B )
WIDE_FIELD_PARSE( 00258FE0, 0002AF8B )
WIDE_FIELD_PARSE( 002596C0, 0002AF8B )
WIDE_FIELD_PARSE( 00259B50, 0002AF8B )
WIDE_FIELD_PARSE( 00259F20, 0002AF8B )
WIDE_FIELD_PARSE( 0025A180, 00005B46 )
WIDE_FIELD_PARSE( 0025ACC0, 0000629E )
WIDE_FIELD_PARSE( 0025CED0, 0002AF8B )
WIDE_FIELD_PARSE( 0025D560, 0002AF8B )
WIDE_FIELD_PARSE( 0025D970, 0000629E )
WIDE_FIELD_PARSE( 0025E7F0, 0000629E )
WIDE_FIELD_PARSE( 0025F0B0, 0002AF8B )
WIDE_FIELD_PARSE( 0025FCF0, 0000629E )
WIDE_FIELD_PARSE( 00263970, 0002AF8B )
WIDE_FIELD_PARSE( 002639A0, 0002AF8B )
WIDE_FIELD_PARSE( 002643F0, 0002AF8B )
WIDE_FIELD_PARSE( 00264420, 0002AF8B )
WIDE_FIELD_PARSE( 002647C0, 0002AF8B )
WIDE_FIELD_PARSE( 00264AC0, 0000629E )
WIDE_FIELD_PARSE( 00265880, 0002AF8B )
WIDE_FIELD_PARSE( 00265AF0, 00005B46 )
WIDE_FIELD_PARSE( 00266210, 00005B46 )
WIDE_FIELD_PARSE( 0026B310, 0002AF8B )
WIDE_FIELD_PARSE( 0026B620, 0002AF8B )
WIDE_FIELD_PARSE( 0026CC50, 0002AF8B )
WIDE_FIELD_PARSE( 0026DF80, 0000629E )
WIDE_FIELD_PARSE( 002B2A80, 00005B46 )
WIDE_FIELD_PARSE( 002B65E0, 0003572E )
WIDE_FIELD_PARSE( 002BC1E0, 0003572E )
WIDE_FIELD_PARSE( 002C5300, 0003572E )
WIDE_FIELD_PARSE( 002CDA00, 00004052 )
WIDE_FIELD_PARSE( 00751690, 0003B7F0 )
WIDE_FIELD_PARSE( 00759700, 00022584 )
WIDE_FIELD_PARSE( 0077DB40, 00022584 )
WIDE_FIELD_PARSE( 0077E070, 00022584 )
