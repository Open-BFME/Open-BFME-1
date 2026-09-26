// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: SplineEffect::ParseINIBlock (retail 0x003BB730 214 B; a gap
// claimed through its own exception text -- despite the "::" the entry point
// takes no `this`.  Unlike its neighbours it checks THREE arguments for
// null, not two: ini, instance, and the third parameter, which here is not
// an opaque store pointer but a `const char *name` (it is fed straight into
// the AsciiString constructor as the text pointer).  With any of the three
// null it throws INIException(3
// "SplineEffect::ParseINIBlock::Invalid data passed in."); otherwise it
// copies the name into a local AsciiString, heap-allocates a 0x28-byte
// record with the plain global `operator new` (constructing it only if the
// allocation succeeds -- the classic MSVC "if (p) ctor(p);" shape for a bare
// `new T()`, matching Path::appendNode's node allocation), fills it through
// INI::initFromINI with the table at VA 0x010ED888 (called even if the
// allocation failed and the record pointer is null -- replicated as-is),
// hands the name and the (possibly heap-allocated, possibly null) record to
// the instance's add routine (thunk 0x0001FD4D), and releases the local
// name's buffer.  The record is never freed here: ownership passes to the
// instance.  Address-derived names.

typedef int Int;
typedef unsigned int UInt;

void *operator new( UInt size );

class INIException
{
public:
	INIException( Int code, const char *msg, ... );
	INIException( const INIException &other );

private:
	Int m_code;
	const char *m_msg;
};

struct FieldParse;

class INI
{
public:
	void initFromINI( void *what, const FieldParse *parseTable );
};

class AsciiString;

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const T *text );
	void releaseBuffer();
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	~AsciiString() { releaseBuffer(); }
};

class Rva003BB730Record
{
public:
	Rva003BB730Record();

private:
	char m_body[ 0x28 ];
};

extern const FieldParse Rva003BB730RecordFieldParseTable[];

class Rva003BB730Owner
{
public:
	void addEffect( AsciiString &name, Rva003BB730Record *record );
};

// ?SplineEffectParseINIBlock@@YAXPAVINI@@PAX1PBD@Z
void SplineEffectParseINIBlock( INI *ini, void *instance, void *, const char *name )
{
	if( ini && instance && name )
	{
		AsciiString token( name );
		Rva003BB730Record *record = new Rva003BB730Record();
		ini->initFromINI( record, Rva003BB730RecordFieldParseTable );
		( (Rva003BB730Owner *)instance )->addEffect( token, record );
	}
	else
		throw INIException( 3, "SplineEffect::ParseINIBlock::Invalid data passed in." );
}
