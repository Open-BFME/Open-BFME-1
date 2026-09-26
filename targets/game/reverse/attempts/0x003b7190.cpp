// ?ParseFlashRegionsEvent@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.9517 date=2026-09-26
// ?ParseFlashRegionsEvent@@YAXPAVINI@@PAX1PBX@Z
// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Retail 0x003B7190..0x003B7221. The 24-byte local wrapper places the
// parse record at the retail stack offset and leaves only frame-size drift.
// This compiler reserves 0x20 bytes; retail reserves 0x18. The frame's
// eight trailing bytes have no independently proven semantic identity.
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

class Rva003B7190Record
{
public:
	Rva003B7190Record() : m_04( 0 ), m_flag08( false ), m_0C( 0 ) {}
	virtual ~Rva003B7190Record() {}

private:
	Int m_04;
	bool m_flag08;
	Int m_0C;
};

extern const FieldParse Rva003B7190RecordFieldParseTable[];

class Rva003B7190Owner
{
public:
	void add( Rva003B7190Record *record );
};

// ?ParseFlashRegionsEvent@@YAXPAVINI@@PAX1PBX@Z
void ParseFlashRegionsEvent( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		struct Frame { Rva003B7190Record record; char pad[8]; };
		Frame frame;
		Rva003B7190Record &record = frame.record;
		ini->initFromINI( &record, Rva003B7190RecordFieldParseTable );
		((Rva003B7190Owner *)instance)->add( &record );
	}
	else
		throw INIException( 3, "ParseFlashRegionsEvent::Invalid data passed in." );
}
