// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: ParseRegionReinforcementBlock (retail 0x003BABE0 157 B; a gap claimed through its
// own exception text).  With no INI or instance it throws INIException(3
// "ParseRegionReinforcementBlock::Invalid data passed in."); otherwise a 0x24-byte record built by
// the out-of-line constructor at 0x003BAB40 is filled through
// INI::initFromINI with the table at VA 0x010ED6A0 handed to the
// instance's append routine (0x003B25D0) and destroyed by the out-of-line
// destructor at 0x003BA580.  Address-derived names.

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

class Rva003BABE0Record
{
public:
	Rva003BABE0Record();
	~Rva003BABE0Record();

private:
	char m_body[ 0x24 ];
};

extern const FieldParse Rva003BABE0RecordFieldParseTable[];

class Rva003BABE0Owner
{
public:
	void append( Rva003BABE0Record *record );
};

// ?ParseRegionReinforcementBlock@@YAXPAVINI@@PAX1PBX@Z
void ParseRegionReinforcementBlock( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		Rva003BABE0Record record;
		ini->initFromINI( &record, Rva003BABE0RecordFieldParseTable );
		((Rva003BABE0Owner *)instance)->append( &record );
	}
	else
		throw INIException( 3, "ParseRegionReinforcementBlock::Invalid data passed in." );
}
