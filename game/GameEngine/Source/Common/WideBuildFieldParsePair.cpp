// Thirty-three 35-byte __cdecl statics that append TWO tables instead of one:
//
//     push esi / mov esi,[esp+8]
//     push IMM8 / push offset TABLE_A / mov ecx,esi / call 0x00850920
//     push IMM8 / push offset TABLE_B / mov ecx,esi / call 0x00850920
//     pop esi / ret
//
// WHAT THE BYTES SHOW.  Same single __cdecl pointer argument and the same
// callee as the one-table builders in WideBuildFieldParse.cpp -- 0x00850920,
// the bounded pair-of-arrays appender (count at [this+0x80], refuses at 16,
// two 16-entry arrays at [this] and [this+0x40], ret 8).  BOTH calls in every
// one of the thirty-three members go to that same address; there is NO base
// class call here, so this is a builder that contributes two field-parse
// tables of its own rather than chaining to a parent.
//
// THE VARYING AXIS IS THE TWO IMM8 SECOND ARGUMENTS.  Everything else is
// either constant (both rel32 targets) or a DIR32 site read from retail (the
// two table addresses).  The observed second arguments are 0, 8, 16 and 40 --
// byte offsets added to every record's field offset, which is exactly what a
// shared sub-block of parse records embedded at a fixed offset needs.  One
// member (0x002D6D60) carries the shared table SECOND rather than first, and
// twenty-one of the 0x00427xxx members share one table as their second
// argument, which is what makes the "shared block plus own block" reading
// concrete rather than decorative.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived; the tables are
// undefined externs whose only role is to make cl emit `push offset`.

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

#define WIDE_FIELD_PARSE_PAIR( NAME, FIRST, SECOND )                      	extern const WideFieldParse WideTblA##NAME[];                         	extern const WideFieldParse WideTblB##NAME[];                         	class Rva##NAME                                                       	{                                                                     	public:                                                               		static void buildFieldParse( WideMulti &p );                      	};                                                                    	void Rva##NAME::buildFieldParse( WideMulti &p )                       	{                                                                     		p.add( WideTblA##NAME, FIRST );                                   		p.add( WideTblB##NAME, SECOND );                                  	}

WIDE_FIELD_PARSE_PAIR( 001246A0, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 001FAB70, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002800A0, 40, 0 )
WIDE_FIELD_PARSE_PAIR( 002D2E80, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D37D0, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D3E00, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D4170, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D4B00, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D4FA0, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D5580, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D5EE0, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D66A0, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D6D60, 0, 16 )
WIDE_FIELD_PARSE_PAIR( 002D7740, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D7A70, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D9310, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D93B0, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D9730, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 00427490, 0, 0 )
WIDE_FIELD_PARSE_PAIR( 004274C0, 0, 0 )
WIDE_FIELD_PARSE_PAIR( 004274F0, 0, 0 )
WIDE_FIELD_PARSE_PAIR( 00427520, 0, 0 )
WIDE_FIELD_PARSE_PAIR( 00427550, 0, 0 )
WIDE_FIELD_PARSE_PAIR( 00427580, 0, 0 )
WIDE_FIELD_PARSE_PAIR( 004275B0, 0, 0 )
WIDE_FIELD_PARSE_PAIR( 004275E0, 0, 0 )
WIDE_FIELD_PARSE_PAIR( 00427640, 0, 0 )
WIDE_FIELD_PARSE_PAIR( 00427780, 0, 0 )
WIDE_FIELD_PARSE_PAIR( 004277B0, 0, 0 )
WIDE_FIELD_PARSE_PAIR( 004277E0, 0, 0 )
WIDE_FIELD_PARSE_PAIR( 00427810, 0, 0 )
WIDE_FIELD_PARSE_PAIR( 00427C80, 0, 0 )
WIDE_FIELD_PARSE_PAIR( 00427CB0, 0, 0 )
