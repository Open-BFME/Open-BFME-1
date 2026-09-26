// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: Rva00365B40 (retail 0x00365B40 178 B; a gap claimed through its
// own exception text -- the target-table estimate 0x00365BAC/70 landed
// mid-body, the real start is the byte after the previous 0xCC run at
// 0x00365B40).  The name "ParseEnableRegion" from the exception literal is
// already claimed by a distinct landed body at 0x003B7BA0 (same message text,
// different function), so this one keeps its address-derived name.  With no
// INI or instance it throws INIException(3
// "ParseEnableRegion::Invalid data passed in."); otherwise a 0xB4-byte record
// built by the out-of-line constructor is filled through INI::initFromINI
// with the table at VA 0x010E8FE8, handed to the instance's append routine,
// and destroyed by the out-of-line destructor.  Address-derived names.

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

class Rva00365B40Record
{
public:
	Rva00365B40Record();
	~Rva00365B40Record();

private:
	char m_body[ 0xB4 ];
};

extern const FieldParse Rva00365B40RecordFieldParseTable[];

class Rva00365B40Owner
{
public:
	void append( Rva00365B40Record *record );
};

// ?Rva00365B40@@YAXPAVINI@@PAX1PBX@Z
void Rva00365B40( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		Rva00365B40Record record;
		ini->initFromINI( &record, Rva00365B40RecordFieldParseTable );
		((Rva00365B40Owner *)instance)->append( &record );
	}
	else
		throw INIException( 3, "ParseEnableRegion::Invalid data passed in." );
}
