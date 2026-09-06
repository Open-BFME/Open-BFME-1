// ?parseBuffNuggetBone@Rva00773170@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the buff-nugget bone field parser at 0x00773170 (204 B): a
// quoted bone token then an optional quoted mesh token; when the mesh token
// is "ExtraMesh" (imported _stricmp) and the following Bool token scans true
// the existing bone list at instance+0x28 is kept else it is cleared
// (erase(begin end) out of line) and the bone name is pushed (the retail
// vector<AsciiString> keeps push_back out of line: modelled as a shell).
// Address-derived names.

extern "C" __declspec(dllimport) int __cdecl _stricmp( const char *a, const char *b );

class AsciiString
{
public:
	AsciiString( const char *text );
	~AsciiString() { releaseBuffer(); }

private:
	void releaseBuffer( void );
	void *m_data;
};

class INI
{
public:
	const char *getNextTokenOrNull( const char *seps );
	static bool scanBool( const char *token );

	char m_unreconstructed[ 0x414 ];
	const char *m_seps;
	const char *m_sepsColon;
	const char *m_sepsQuote;
	const char *m_sepsPercent;
};

class Rva00773170StringVector
{
public:
	void push_back( const AsciiString &value );
	AsciiString *erase( AsciiString *first, AsciiString *last );
	void clear( void ) { erase( m_start, m_finish ); }

private:
	AsciiString *m_start;
	AsciiString *m_finish;
	AsciiString *m_endOfStorage;
};

struct Rva00773170Owner
{
	char m_unreconstructed[ 0x28 ];
	Rva00773170StringVector m_bones;
};

class Rva00773170
{
public:
	static void parseBuffNuggetBone( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseBuffNuggetBone@Rva00773170@@SAXPAVINI@@PAX1PBX@Z
void Rva00773170::parseBuffNuggetBone( INI *ini, void *instance, void *, const void * )
{
	Rva00773170Owner *self = (Rva00773170Owner *)instance;
	if( !self )
		return;
	const char *bone = ini->getNextTokenOrNull( ini->m_sepsQuote );
	if( !bone )
		return;
	const char *mesh = ini->getNextTokenOrNull( ini->m_sepsQuote );
	bool keep = false;
	if( mesh && _stricmp( mesh, "ExtraMesh" ) == 0 )
	{
		const char *flag = ini->getNextTokenOrNull( 0 );
		if( flag && INI::scanBool( flag ) )
			keep = true;
	}
	if( !keep )
		self->m_bones.clear();
	AsciiString name( bone );
	self->m_bones.push_back( name );
}
