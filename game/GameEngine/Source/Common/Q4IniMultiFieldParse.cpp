// Ten 96-byte __cdecl INI parse callbacks, each of which builds a
// MultiIniFieldParse on the stack from two field tables and hands it to
// INI::initFromINIMulti:
//
//     MultiIniFieldParse fields;                 (0x84 bytes, zeroed inline)
//     fields.add( <shared base table>() );
//     fields.add( <this callback's table> );
//     ini->initFromINIMulti( instance, fields );
//
// WHAT THE BYTES SHOW, AND WHY THE IDENTITY IS REAL HERE.  Two of the three
// callees are already named in the ledger and their signatures fit the call
// sites exactly: 0x00850920 is
// ?add@MultiIniFieldParse@@QAEXPBUFieldParse@@I@Z (__thiscall, two stack
// arguments, both call sites push a table and a zero) and 0x00851910 is
// ?initFromINIMulti@INI@@QAEXPAXABVMultiIniFieldParse@@@Z (__thiscall on the
// FIRST stack argument, taking the second argument and the address of the
// local).  The 0x84-byte local is MultiIniFieldParse to the byte: sixteen
// pointers, sixteen unsigned offsets, one count.  The zero-fill proves the
// field order as well as the size -- `mov [esp+0x84],esi` before the loop is
// `Count = 0` written FIRST, and the loop body stores [esp+i*4+0x44] before
// [esp+i*4+4], i.e. `Offsets[i] = 0;` before `Fields[i] = 0;`.  Reordering
// either pair changes the bytes.
//
// THE RECEIVER IS A STACK ARGUMENT, NOT ecx.  `mov ecx,[esp+0x94]` reloads the
// first argument into ecx immediately before the call, so these functions are
// __cdecl free functions that call a member on their first parameter -- not
// members themselves.
//
// ARITY IS NOT DECIDED.  A __cdecl `ret` pops nothing, so nothing here
// distinguishes the two arguments the body reads from the four-argument INI
// parse-callback signature these normally have.  Two is spelled because it
// asserts less; if the surrounding family turns out to be
// (INI*, void*, void*, const void*) the body is unchanged.
//
// THE VARYING AXIS IS ONE FIELD AND IT IS NOT EVIDENCE: the address of the
// second field table.  It is a DIR32 operand build.py copies from retail, so
// the ten rows differ in nothing that the comparison can see -- what makes
// them ten rows is that they are ten separate bodies, each naming a different
// table.  The first table comes from a shared niladic getter at 0x002DEEB0
// whose entire body is `mov eax,<table>; ret`, and all ten call it.
//
// IDENTITY IS NOT RECOVERED for the ten callbacks themselves, for their field
// tables, or for the getter; those names are address-derived.  MultiIniFieldParse
// and INI carry their recovered names because the ledger already pins those two
// members at these addresses.

class INI;
typedef void (*INIFieldParseProc)( INI *ini, void *instance, void *store, const void *userData );

struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class MultiIniFieldParse
{
public:
	MultiIniFieldParse()
	{
		Count = 0;
		for( int i = 0; i < 16; ++i )
		{
			Offsets[ i ] = 0;
			Fields[ i ] = 0;
		}
	}
	void add( const FieldParse *, unsigned int = 0 );

private:
	const FieldParse *Fields[ 16 ];
	unsigned int Offsets[ 16 ];
	unsigned int Count;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMulti( void *, const MultiIniFieldParse & );

	static void parseReal( INI *ini, void *instance, void *store, const void *userData );
	static void parseAngleReal( INI *ini, void *instance, void *store, const void *userData );
	static void parseBool( INI *ini, void *instance, void *store, const void *userData );
	static void parseVelocityReal( INI *ini, void *instance, void *store, const void *userData );
	static void parseDurationUnsignedInt( INI *ini, void *instance, void *store, const void *userData );
};

const FieldParse *q4BaseFields002DEEB0();

#define Q4_INI_MULTI_PARSE( T )                                           	extern const FieldParse q4Fields##T[];                                	void Rva##T( INI *ini, void *instance )                               	{                                                                     		MultiIniFieldParse fields;                                        		fields.add( q4BaseFields002DEEB0() );                             		fields.add( q4Fields##T );                                        		ini->initFromINIMulti( instance, fields );                        	}

Q4_INI_MULTI_PARSE( 002DA6F0 )
Q4_INI_MULTI_PARSE( 002DAD80 )
Q4_INI_MULTI_PARSE( 002DC7B0 )
Q4_INI_MULTI_PARSE( 002DC830 )
Q4_INI_MULTI_PARSE( 002DCC80 )
Q4_INI_MULTI_PARSE( 002DD2B0 )
Q4_INI_MULTI_PARSE( 002DDCE0 )
Q4_INI_MULTI_PARSE( 002DE280 )
Q4_INI_MULTI_PARSE( 002DE890 )
Q4_INI_MULTI_PARSE( 002DEC40 )
Q4_INI_MULTI_PARSE( 002DF520 )

// Retail .rdata VA 0x010CEE68 (176 B), the table Rva002DD2B0 adds: ten
// entries plus a zero terminator. ShockWaveAmount/ShockWaveSpeed go through the
// parseVelocityReal ILT 0x00038708 (body 0x000B9D20) and DelayTime through the
// parseDurationUnsignedInt ILT 0x000324DE (body 0x000B9C60).
const FieldParse q4Fields002DD2B0[] =
{
	{ "ShockWaveAmount", INI::parseVelocityReal, 0, 0x58 },
	{ "ShockWaveRadius", INI::parseReal, 0, 0x5C },
	{ "ShockWaveArc", INI::parseAngleReal, 0, 0x60 },
	{ "ShockWaveTaperOff", INI::parseReal, 0, 0x64 },
	{ "ShockWaveSpeed", INI::parseVelocityReal, 0, 0x68 },
	{ "ShockWaveZMult", INI::parseReal, 0, 0x6C },
	{ "DelayTime", INI::parseDurationUnsignedInt, 0, 0x70 },
	{ "InvertShockWave", INI::parseBool, 0, 0x74 },
	{ "FlipDirection", INI::parseBool, 0, 0x75 },
	{ "HeroResist", INI::parseReal, 0, 0x78 },
	{ 0, 0, 0, 0 }
};
