// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: ParseMergeArmyBlock (retail 0x003B8500 157 B; a gap claimed through its
// own exception text).  With no INI or instance it throws INIException(3
// "ParseMergeArmyBlock::Invalid data passed in."); otherwise a 0x14-byte record built by
// the out-of-line constructor at 0x003B83C0 is filled through
// INI::initFromINI with the table at VA 0x010ED258 handed to the
// instance's append routine (0x003B19E0) and destroyed by the out-of-line
// destructor at 0x003B8450.  Address-derived names.

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

class Rva003B8500Record
{
public:
	Rva003B8500Record();
	~Rva003B8500Record();

private:
	char m_body[ 0x14 ];
};

extern const FieldParse Rva003B8500RecordFieldParseTable[];

class Rva003B8500Owner
{
public:
	void append( Rva003B8500Record *record );
};

// ?ParseMergeArmyBlock@@YAXPAVINI@@PAX1PBX@Z
void ParseMergeArmyBlock( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		Rva003B8500Record record;
		ini->initFromINI( &record, Rva003B8500RecordFieldParseTable );
		((Rva003B8500Owner *)instance)->append( &record );
	}
	else
		throw INIException( 3, "ParseMergeArmyBlock::Invalid data passed in." );
}
