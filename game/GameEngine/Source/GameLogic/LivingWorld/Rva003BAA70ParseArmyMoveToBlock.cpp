// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: Rva003BAA70ParseArmyMoveToBlock (retail 0x003BAA70 157 B; a gap claimed through its
// own exception text).  With no INI or instance it throws INIException(3
// "ParseArmyMoveToBlock::Invalid data passed in."); otherwise a 0x24-byte record built by
// the out-of-line constructor at 0x0002D3A8 is filled through
// INI::initFromINI with the table at VA 0x010ED540 handed to the
// instance's append routine (0x00020E64) and destroyed by the out-of-line
// destructor at 0x00044BB1.  Address-derived names.

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

class Rva003BAA70Record
{
public:
	Rva003BAA70Record();
	~Rva003BAA70Record();

private:
	char m_body[ 0x24 ];
};

extern const FieldParse Rva003BAA70RecordFieldParseTable[];

class Rva003BAA70Owner
{
public:
	void append( Rva003BAA70Record *record );
};

// ?Rva003BAA70ParseArmyMoveToBlock@@YAXPAVINI@@PAX1PBX@Z
void Rva003BAA70ParseArmyMoveToBlock( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		Rva003BAA70Record record;
		ini->initFromINI( &record, Rva003BAA70RecordFieldParseTable );
		((Rva003BAA70Owner *)instance)->append( &record );
	}
	else
		throw INIException( 3, "ParseArmyMoveToBlock::Invalid data passed in." );
}
