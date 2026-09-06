// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: INI block parser at 0x004255F0 (105 B): a zeroed (AsciiString
// name + 4-byte value) record local is filled through INI::initFromINI with
// the field table at VA 0x010F1B34 then inserted into the map the store
// argument points at (the red-black tree insert_unique at 0x00424BA0 whose
// pair result comes back through the hidden pointer) and destroyed by the
// record destructor at 0x00423280.  Address-derived names.

struct FieldParse;

class AsciiString
{
public:
	AsciiString() : m_data( 0 ) {}

private:
	void *m_data;
};

struct Rva004255F0Record
{
	Rva004255F0Record() : m_value( 0 ) {}
	~Rva004255F0Record();

	AsciiString m_name;
	int m_value;
};

struct Rva004255F0InsertResult
{
	void *m_where;
	bool m_inserted;
};

class Rva004255F0Map
{
public:
	Rva004255F0InsertResult insert_unique( const Rva004255F0Record &record );
};

class INI
{
public:
	void initFromINI( void *what, const FieldParse *parseTable );
};

extern const FieldParse Rva004255F0FieldParseTable[];

class Rva004255F0
{
public:
	static void parseRecordIntoMap( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseRecordIntoMap@Rva004255F0@@SAXPAVINI@@PAX1PBX@Z
void Rva004255F0::parseRecordIntoMap( INI *ini, void *, void *store, const void * )
{
	Rva004255F0Record record;
	ini->initFromINI( &record, Rva004255F0FieldParseTable );
	((Rva004255F0Map *)store)->insert_unique( record );
}
