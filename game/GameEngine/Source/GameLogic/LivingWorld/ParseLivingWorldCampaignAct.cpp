// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: ParseLivingWorldCampaignAct (retail 0x003B2BB0 286 B; a gap
// claimed through its exception texts).  With no INI or instance it throws
// INIException(3 "ParseLivingWorldCampaignAct::Invalid data passed in.") --
// written as an early throw so the two exception temporaries get their own
// frame slots; the act name is read into an AsciiString whose Int length
// (movzx of the word four bytes into the string data) must not be zero else
// INIException(3 "ParseLivingWorldCampaignAct::No act name specified.");
// a 0xDC-byte act record built by the out-of-line constructor at 0x003AA0F8
// from the name is filled through INI::initFromINI with the table at VA
// 0x010EC9B8 handed to the instance's append routine (0x00444A17) and
// destroyed by the out-of-line destructor at 0x0040817A before the name is
// released.  Address-derived names.

typedef int Int;

struct FieldParse;

struct Rva003B2BB0StringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_length;
	unsigned short m_pad;
};

class AsciiString
{
public:
	AsciiString( const char *text );
	~AsciiString() { releaseBuffer(); }
	Int getLength( void ) const { return m_data ? m_data->m_length : 0; }
	bool isEmpty( void ) const { return m_data == 0 || getLength() == 0; }

private:
	void releaseBuffer( void );
	Rva003B2BB0StringData *m_data;
};

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
	const char *getNextToken( const char *seps = 0 );
	void initFromINI( void *what, const FieldParse *parseTable );
};

class Rva003B2BB0Record
{
public:
	Rva003B2BB0Record( const AsciiString &name );
	~Rva003B2BB0Record();

private:
	char m_body[ 0xDC ];
};

extern const FieldParse Rva003B2BB0FieldParseTable[];

class Rva003B2BB0Owner
{
public:
	void append( Rva003B2BB0Record *record );
};

// ?ParseLivingWorldCampaignAct@@YAXPAVINI@@PAX1PBX@Z
void ParseLivingWorldCampaignAct( INI *ini, void *instance, void *, const void * )
{
	if( !ini || !instance )
		throw INIException( 3, "ParseLivingWorldCampaignAct::Invalid data passed in." );
	AsciiString name( ini->getNextToken() );
	Int length = name.getLength();
	if( !length )
		throw INIException( 3, "ParseLivingWorldCampaignAct::No act name specified." );
	Rva003B2BB0Record record( name );
	ini->initFromINI( &record, Rva003B2BB0FieldParseTable );
	((Rva003B2BB0Owner *)instance)->append( &record );
}
