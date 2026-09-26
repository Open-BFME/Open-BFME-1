// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: ParseMoveCameraBlock (retail 0x003B7650 161 B; a gap claimed
// through its own exception text).  With no INI or instance it throws
// INIException(3 "ParseMoveCameraBlock::Invalid data passed in."); otherwise a
// 0x20-byte polymorphic record (vtable at VA 0x010EC764 six zeroed dwords and
// a zeroed flag byte) is filled through INI::initFromINI with the table at VA
// 0x010ECD18 and handed to the instance's add routine (thunk 0x00401564).
// Address-derived names.

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

class Rva003B7650Record
{
public:
	Rva003B7650Record() : m_04( 0 ), m_08( 0 ), m_0C( 0 ), m_10( 0 ), m_14( 0 ), m_18( 0 ), m_flag1C( false ) {}
	virtual ~Rva003B7650Record() {}

private:
	Int m_04, m_08, m_0C, m_10, m_14, m_18;
	bool m_flag1C;
};

extern const FieldParse Rva003B7650FieldParseTable[];

class Rva003B7650Owner
{
public:
	void addMoveCamera( Rva003B7650Record *record );
};

// ?ParseMoveCameraBlock@@YAXPAVINI@@PAX1PBX@Z
void ParseMoveCameraBlock( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		Rva003B7650Record record;
		ini->initFromINI( &record, Rva003B7650FieldParseTable );
		((Rva003B7650Owner *)instance)->addMoveCamera( &record );
	}
	else
		throw INIException( 3, "ParseMoveCameraBlock::Invalid data passed in." );
}
