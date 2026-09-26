// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: ParseArmyMoveToBlock (retail 0x003B8190 157 B; a gap claimed through its
// own exception text).  With no INI or instance it throws INIException(3
// "ParseArmyMoveToBlock::Invalid data passed in."); otherwise a 0x20-byte record built by
// the out-of-line constructor at 0x00044823 is filled through
// INI::initFromINI with the table at VA 0x010ED108 handed to the
// instance's append routine (0x00003ADA) and destroyed by the out-of-line
// destructor at 0x00023AFB.  Address-derived names.

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

class Rva003B8190Record
{
public:
	Rva003B8190Record();
	~Rva003B8190Record();

private:
	char m_body[ 0x20 ];
};

extern const FieldParse Rva003B8190RecordFieldParseTable[];

class Rva003B8190Owner
{
public:
	void append( Rva003B8190Record *record );
};

// ?ParseArmyMoveToBlock@@YAXPAVINI@@PAX1PBX@Z
void ParseArmyMoveToBlock( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		Rva003B8190Record record;
		ini->initFromINI( &record, Rva003B8190RecordFieldParseTable );
		((Rva003B8190Owner *)instance)->append( &record );
	}
	else
		throw INIException( 3, "ParseArmyMoveToBlock::Invalid data passed in." );
}
