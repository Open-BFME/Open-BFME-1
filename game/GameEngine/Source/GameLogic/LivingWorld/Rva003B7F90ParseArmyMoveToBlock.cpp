// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: Rva003B7F90ParseArmyMoveToBlock (retail 0x003B7F90 202 B; a gap claimed through
// its own exception text).  With no INI or instance it throws INIException(3
// "ParseArmyMoveToBlock::Invalid data passed in."); otherwise the record below is built inline filled through
// INI::initFromINI with the table at VA 0x010ECFF0 and handed to the
// instance's append routine (0x00000000); the out-of-line destructor (the BfmeOwnVUO dtor row) runs after the append.  Address-derived names.

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

class Rva003B7F90Record
{
public:
	Rva003B7F90Record() : m_04( 0 ), m_08( 0 ), m_0C( 0 ), m_10( 0 ), m_14( 0 ), m_flag18( false ), m_flag19( false ), m_1C( 0 ), m_20( 0 ), m_24( 0 ), m_28( 0 ), m_flag2C( false ) {}
	virtual ~Rva003B7F90Record();

private:
	Int m_04, m_08, m_0C, m_10, m_14;
	bool m_flag18, m_flag19;
	Int m_1C, m_20, m_24, m_28;
	bool m_flag2C;
};

extern const FieldParse Rva003B7F90RecordFieldParseTable[];

class Rva003B7F90Owner
{
public:
	void append( Rva003B7F90Record *record );
};

// ?Rva003B7F90ParseArmyMoveToBlock@@YAXPAVINI@@PAX1PBX@Z
void Rva003B7F90ParseArmyMoveToBlock( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		Rva003B7F90Record record;
		ini->initFromINI( &record, Rva003B7F90RecordFieldParseTable );
		((Rva003B7F90Owner *)instance)->append( &record );
	}
	else
		throw INIException( 3, "ParseArmyMoveToBlock::Invalid data passed in." );
}
