// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: Rva003B82D0ParseArmyMoveToBlock (retail 0x003B82D0 183 B; a gap
// claimed through its own exception text -- one of several duplicate
// "ParseArmyMoveToBlock" bodies in retail, name already taken by
// 0x003B8190/0x003BAA70/0x003B7F90 so this one keeps its address-derived
// name).  With no INI or instance it throws INIException(3
// "ParseArmyMoveToBlock::Invalid data passed in."); otherwise a record
// (vtable BfmeEntVTA, an inline AsciiString token default-constructed from
// the shared empty-string literal at VA 0x0107301C, and a flag byte) is
// filled through INI::initFromINI with the table at VA 0x010ED1A0 and handed
// to the instance's append routine (thunk 0x00449B48); the AsciiString uses
// the retail BFMERetailAsciiString/StringBase<char> shim already landed in
// game/GameEngine/Source/Common/BfmeConv534.cpp (ctor at 0x00888BC0,
// releaseBuffer at 0x00887940).  Address-derived names.

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

class BFMERetailAsciiString;

template <typename T> class StringBase
{
	friend class BFMERetailAsciiString;

private:
	StringBase( const T *text );
	StringBase( const StringBase &other );
	void releaseBuffer();
	void *m_data;
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString( const char *text ) : StringBase<char>( text ) {}
	BFMERetailAsciiString( const BFMERetailAsciiString &other ) : StringBase<char>( other ) {}
	~BFMERetailAsciiString() { releaseBuffer(); }
};

class Rva003B82D0Record
{
public:
	Rva003B82D0Record() : m_token( (const char *)0x0107301c ), m_flag08( false ) {}
	virtual ~Rva003B82D0Record() {}

private:
	BFMERetailAsciiString m_token;
	bool m_flag08;
};

extern const FieldParse Rva003B82D0RecordFieldParseTable[];

class Rva003B82D0Owner
{
public:
	void append( Rva003B82D0Record *record );
};

// ?Rva003B82D0ParseArmyMoveToBlock@@YAXPAVINI@@PAX1PBX@Z
void Rva003B82D0ParseArmyMoveToBlock( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		Rva003B82D0Record record;
		ini->initFromINI( &record, Rva003B82D0RecordFieldParseTable );
		((Rva003B82D0Owner *)instance)->append( &record );
	}
	else
		throw INIException( 3, "ParseArmyMoveToBlock::Invalid data passed in." );
}
