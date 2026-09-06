// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: Rva003B88F0ParseAnimObjectUpdate (retail 0x003B88F0 154 B; a gap claimed through
// its own exception text).  With no INI or instance it throws INIException(3
// "ParseAnimObjectUpdate::Invalid data passed in."); otherwise the record below is built inline filled through
// INI::initFromINI with the table at VA 0x010ED420 and handed to the
// instance's append routine (0x00000000); the out-of-line destructor at 0x003B8850 runs after the append.  Address-derived names.

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

struct Rva003B88F0Record
{
	Rva003B88F0Record() : m_00( 0 ), m_04( 0 ), m_08( 0 ) {}
	~Rva003B88F0Record();

	Int m_00, m_04, m_08;
};

extern const FieldParse Rva003B88F0RecordFieldParseTable[];

class Rva003B88F0Owner
{
public:
	void append( Rva003B88F0Record *record );
};

// ?Rva003B88F0ParseAnimObjectUpdate@@YAXPAVINI@@PAX1PBX@Z
void Rva003B88F0ParseAnimObjectUpdate( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		Rva003B88F0Record record;
		ini->initFromINI( &record, Rva003B88F0RecordFieldParseTable );
		((Rva003B88F0Owner *)instance)->append( &record );
	}
	else
		throw INIException( 3, "ParseAnimObjectUpdate::Invalid data passed in." );
}
