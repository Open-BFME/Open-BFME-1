// ?parseQuotedNameLookup@Rva0061A0A0@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME7: INI field parser at 0x0061A0A0 (54 B): reads one token with the
// quote separator set (the INI member at +0x41C: m_seps sits at +0x414 and
// Zero Hour orders m_seps m_sepsColon m_sepsQuote m_sepsPercent) into an
// AsciiString and stores the result of the cdecl lookup at 0x00619FF0 into
// the dword the store argument points at.  MSVC parks the AsciiString local
// in the dead ini argument slot and tail-jumps to its releaseBuffer; the TU
// was built with exceptions off (no EH frame around the string local).
// Address-derived names.

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

	char m_unreconstructed[ 0x414 ];
	const char *m_seps;
	const char *m_sepsColon;
	const char *m_sepsQuote;
	const char *m_sepsPercent;
};

int __cdecl Rva00619FF0LookupByName( const AsciiString &name );

class Rva0061A0A0
{
public:
	static void parseQuotedNameLookup( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseQuotedNameLookup@Rva0061A0A0@@SAXPAVINI@@PAX1PBX@Z
void Rva0061A0A0::parseQuotedNameLookup( INI *ini, void *, void *store, const void * )
{
	AsciiString name( ini->getNextTokenOrNull( ini->m_sepsQuote ) );
	*(int *)store = Rva00619FF0LookupByName( name );
}
