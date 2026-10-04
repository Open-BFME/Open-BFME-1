// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Open-BFME: function-curve INI loader at retail RVA 0x0006AF00.
// Its neighbouring addKey/final-key bodies establish the accumulator layout;
// the three field names and the BFME padding-name table are the shipped
// literals used by this loader.

typedef int Int;

struct FieldParse;

class INI
{
public:
	static void parseIndexList( INI *, void *, void *, const void * );
	void initFromINI( void *, const FieldParse * );
};

typedef void (__cdecl *INIFieldParseProc)( INI *, void *, void *, const void * );

struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	Int offset;
};

class Rva0006AB10Curve
{
};

extern void j_0003a562();

// Null-terminated padding names used by INI::parseIndexList.
const char *g_012A718C[] =
{
	"HOLD", "EXTRAPOLATE", "CYCLE", "CYCLE_OFFSET", "MIRROR", 0
};

class Rva0006AB90FunctionCurve
{
public:
	Rva0006AB90FunctionCurve( Rva0006AB10Curve *curve ) :
		m_curve( curve ),
		m_firstKey( true ),
		m_lastTime( 0.0f ),
		m_lastValue( 0.0f ),
		m_inTangent( 0.0f ),
		m_outTangent( 0.0f ),
		m_haveInTangent( false ),
		m_haveOutTangent( false )
	{
	}
	private:
	Rva0006AB10Curve *m_curve;
	bool m_firstKey;
	float m_lastTime;
	float m_lastValue;
	float m_inTangent;
	float m_outTangent;
	bool m_haveInTangent;
	bool m_haveOutTangent;
};

// The shipped j-thunk is the independently recovered final-key body at
// 0x00024000 -> 0x0006ACF0; this typed member call routes there through the
// ILT thunk directly, with no linker alias.
extern void j_00024000();

class Rva0006AF00FunctionCurve
{
public:
	void parse( INI *ini );
};

// ?parse@Rva0006AF00FunctionCurve@@QAEXPAVINI@@@Z
void Rva0006AF00FunctionCurve::parse( INI *ini )
{
	Rva0006AB90FunctionCurve accumulator( (Rva0006AB10Curve *)this );
	FieldParse fields[] =
	{
		{ "InPadding", INI::parseIndexList, g_012A718C, 0 },
		{ "OutPadding", INI::parseIndexList, g_012A718C, 4 },
		{ "Key", (INIFieldParseProc)j_0003a562, &accumulator, 8 },
		{ 0, 0, 0, 0 }
	};

	ini->initFromINI( this, fields );
	typedef void (Rva0006AB90FunctionCurve::*Fn)();
	union { void (*fn)(); Fn call; } u = { j_00024000 };
	(accumulator.*u.call)();
}
