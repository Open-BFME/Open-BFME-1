// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: ParseEyeTowerPointData (retail 0x003BAE20 157 B; a gap claimed through its
// own exception text).  With no INI or instance it throws INIException(3
// "ParseEyeTowerPointData::Invalid data passed in."); otherwise a 0xc-byte record built by
// the out-of-line constructor at 0x00033488 is filled through
// INI::initFromINI with the table at VA 0x010ED784 handed to the
// instance's append routine (0x0004A354) and destroyed by the out-of-line
// destructor at 0x000195FB.  Address-derived names.

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

class Rva003BAE20Record
{
public:
	Rva003BAE20Record();
	~Rva003BAE20Record();

private:
	char m_body[ 0xc ];
};

extern const FieldParse Rva003BAE20RecordFieldParseTable[];

class Rva003BAE20Owner
{
public:
	void append( Rva003BAE20Record *record );
};

// ?ParseEyeTowerPointData@@YAXPAVINI@@PAX1PBX@Z
void ParseEyeTowerPointData( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		Rva003BAE20Record record;
		ini->initFromINI( &record, Rva003BAE20RecordFieldParseTable );
		((Rva003BAE20Owner *)instance)->append( &record );
	}
	else
		throw INIException( 3, "ParseEyeTowerPointData::Invalid data passed in." );
}
