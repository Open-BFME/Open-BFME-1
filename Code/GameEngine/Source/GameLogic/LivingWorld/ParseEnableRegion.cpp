// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: ParseEnableRegion (retail 0x003B7BA0 162 B; a gap claimed through
// its own exception text).  With no INI or instance it throws INIException(3
// "ParseEnableRegion::Invalid data passed in."); otherwise the record below is built inline filled through
// INI::initFromINI with the table at VA 0x010ECE14 and handed to the
// instance's append routine (0x0043847E); the inline virtual destructor restores the vtable (VA 0x010EC76C) and releases the name.  Address-derived names.

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

class AsciiString
{
public:
	AsciiString() : m_data( 0 ) {}
	~AsciiString() { releaseBuffer(); }

private:
	void releaseBuffer( void );
	void *m_data;
};

class Rva003B7BA0Record
{
public:
	virtual ~Rva003B7BA0Record() {}

private:
	AsciiString m_name;
};

extern const FieldParse Rva003B7BA0RecordFieldParseTable[];

class Rva003B7BA0Owner
{
public:
	void append( Rva003B7BA0Record *record );
};

// ?ParseEnableRegion@@YAXPAVINI@@PAX1PBX@Z
void ParseEnableRegion( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		Rva003B7BA0Record record;
		ini->initFromINI( &record, Rva003B7BA0RecordFieldParseTable );
		((Rva003B7BA0Owner *)instance)->append( &record );
	}
	else
		throw INIException( 3, "ParseEnableRegion::Invalid data passed in." );
}
