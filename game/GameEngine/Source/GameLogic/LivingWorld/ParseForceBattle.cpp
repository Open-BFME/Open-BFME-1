// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: ParseForceBattle (retail 0x003B7DC0 157 B; a gap claimed through its
// own exception text).  With no INI or instance it throws INIException(3
// "ParseForceBattle::Invalid data passed in."); otherwise a 0x28-byte record built by
// the out-of-line constructor at 0x003B7C70 is filled through
// INI::initFromINI with the table at VA 0x010ECEC8 handed to the
// instance's append routine (0x003B18A0) and destroyed by the out-of-line
// destructor at 0x003B7D30.  Address-derived names.

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

class Rva003B7DC0Record
{
public:
	Rva003B7DC0Record();
	~Rva003B7DC0Record();

private:
	char m_body[ 0x28 ];
};

extern const FieldParse Rva003B7DC0RecordFieldParseTable[];

class Rva003B7DC0Owner
{
public:
	void append( Rva003B7DC0Record *record );
};

// ?ParseForceBattle@@YAXPAVINI@@PAX1PBX@Z
void ParseForceBattle( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		Rva003B7DC0Record record;
		ini->initFromINI( &record, Rva003B7DC0RecordFieldParseTable );
		((Rva003B7DC0Owner *)instance)->append( &record );
	}
	else
		throw INIException( 3, "ParseForceBattle::Invalid data passed in." );
}
