// ?parseFCurveOrReal@Rva000BD900@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.2 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc

// Open-BFME7: INI field parser at 0x000BD900 (180 B), BFME-only (no Zero
// Hour twin -- "FCurve" does not appear in the reference tree). Reads a
// token; if it equals the literal "FCurve" (VA 0x1082F44, seven-byte
// compare) it appends a curve-reference entry to a list at instance+0xc
// (growth check on instance+8/+0xc, insert via j_0001e6a5) and stores 0
// at instance+0/+4; otherwise it scans the token as a float with the
// imported bfmeScanDYG(s, "%f", &out) (VA 0x1082F4C) and, on success,
// appends the constant value the same way (j_00032e9d); a token that is
// neither throws INIException(5, "'FCurve' expected", VA 0x1082F2C).
// Names and field layout are address-derived.

typedef int Int;
typedef float Real3264;

extern "C" __declspec(dllimport) int __cdecl bfmeScanDYG(const char *s, const char *fmt, void *out);
extern "C" __declspec(dllimport) int __cdecl strcmp(const char *a, const char *b);

class INIException
{
public:
	INIException(Int code, const char *msg, ...);
	INIException(const INIException &other);
};

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
};

class Rva000BD900Store
{
public:
	Int m_field0;
	Int m_field4;
	void *m_field8;
	void *m_fieldC;
};

extern "C" void __cdecl Rva000BD900AppendCurve( Rva000BD900Store *store, const char *token );
extern "C" void __cdecl Rva000BD900AppendConstant( Rva000BD900Store *store, Real3264 value );

class Rva000BD900
{
public:
	static void parseFCurveOrReal( INI *ini, void *instance, void *, const void * );
};

// ?parseFCurveOrReal@Rva000BD900@@SAXPAVINI@@PAX1PBX@Z
void Rva000BD900::parseFCurveOrReal( INI *ini, void *instance, void *, const void * )
{
	const char *token = ini->getNextToken();
	Rva000BD900Store *store = (Rva000BD900Store *)instance;

	Real3264 value = 0.0f;
	if( bfmeScanDYG( token, "%f", &value ) == 1 )
	{
		store->m_field0 = 0;
		store->m_field4 = 0;
		Rva000BD900AppendConstant( store, value );
		return;
	}

	if( token && strcmp( token, "FCurve" ) == 0 )
	{
		Rva000BD900AppendCurve( store, token );
		return;
	}

	throw INIException( 5, "'FCurve' expected" );
}
