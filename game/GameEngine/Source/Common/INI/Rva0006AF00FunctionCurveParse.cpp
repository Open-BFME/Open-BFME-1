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
	void finish();

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
// 0x00024000 -> 0x0006ACF0; map only this typed member call to that thunk.
#pragma comment(linker, "/alternatename:?finish@Rva0006AB90FunctionCurve@@QAEXXZ=?j_00024000@@YAXXZ")

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
		{ (const char *)0x01075AB8, INI::parseIndexList, (const void *)0x012A718C, 0 },
		{ (const char *)0x01075AA8, INI::parseIndexList, (const void *)0x012A718C, 4 },
		{ (const char *)0x01075AA4, (INIFieldParseProc)j_0003a562, &accumulator, 8 },
		{ 0, 0, 0, 0 }
	};

	ini->initFromINI( this, fields );
	accumulator.finish();
}
