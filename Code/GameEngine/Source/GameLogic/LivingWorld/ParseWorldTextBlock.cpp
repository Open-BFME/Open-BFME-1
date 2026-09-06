// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: ParseWorldTextBlock (retail 0x003B8610 174 B; a gap claimed through
// its own exception text).  With no INI or instance it throws INIException(3
// "ParseWorldTextBlock::Invalid data passed in."); otherwise the record below is built inline filled through
// INI::initFromINI with the table at VA 0x010ED300 and handed to the
// instance's append routine (0x00443167); the inline virtual destructor restores the vtable (VA 0x010EC784) and releases the string at +0xC.  Address-derived names.

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

class Rva003B8610Record
{
public:
	Rva003B8610Record() : m_04( 0 ), m_08( 0 ), m_flag10( false ) {}
	virtual ~Rva003B8610Record() {}

private:
	Int m_04;
	Int m_08;
	AsciiString m_text;
	bool m_flag10;
};

extern const FieldParse Rva003B8610RecordFieldParseTable[];

class Rva003B8610Owner
{
public:
	void append( Rva003B8610Record *record );
};

// ?ParseWorldTextBlock@@YAXPAVINI@@PAX1PBX@Z
void ParseWorldTextBlock( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		Rva003B8610Record record;
		ini->initFromINI( &record, Rva003B8610RecordFieldParseTable );
		((Rva003B8610Owner *)instance)->append( &record );
	}
	else
		throw INIException( 3, "ParseWorldTextBlock::Invalid data passed in." );
}
