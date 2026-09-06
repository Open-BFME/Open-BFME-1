// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: ParseAnimObjectUpdate (retail 0x003B8770 158 B; a gap claimed through
// its own exception text).  With no INI or instance it throws INIException(3
// "ParseAnimObjectUpdate::Invalid data passed in."); otherwise the record below is built inline filled through
// INI::initFromINI with the table at VA 0x010ED3B8 and handed to the
// instance's append routine (0x00000000); the out-of-line destructor at 0x003B8710 runs after the append.  Address-derived names.

typedef int Int;

struct FieldParse;

class INIException
{
public:
	INIException( Int code, const char *msg, ... );
	INIException( const INIException &other );

private:
	Int m_code;
	const char *m_msg;
};

class INI
{
public:
	void initFromINI( void *what, const FieldParse *parseTable );
};

struct Rva003B8770Record
{
	Rva003B8770Record() : m_00( 0 ), m_04( 0 ), m_08( 0 ), m_0C( 0 ) {}
	~Rva003B8770Record();

	Int m_00, m_04, m_08, m_0C;
};

extern const FieldParse Rva003B8770RecordFieldParseTable[];

class Rva003B8770Owner
{
public:
	void append( Rva003B8770Record *record );
};

// ?ParseAnimObjectUpdate@@YAXPAVINI@@PAX1PBX@Z
void ParseAnimObjectUpdate( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		Rva003B8770Record record;
		ini->initFromINI( &record, Rva003B8770RecordFieldParseTable );
		((Rva003B8770Owner *)instance)->append( &record );
	}
	else
		throw INIException( 3, "ParseAnimObjectUpdate::Invalid data passed in." );
}
