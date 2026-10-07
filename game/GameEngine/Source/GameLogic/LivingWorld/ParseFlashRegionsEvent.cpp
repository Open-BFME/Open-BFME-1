// cl: /DNDEBUG /DWIN32 /MD /EHsc
// ParseFlashRegionsEvent: retail RVA 0x003B7190, 145 bytes through the
// _CxxThrowException call. The following int3 is alignment, not body coverage.
// Identity: exact exception literal ParseFlashRegionsEvent::Invalid data passed in.
// Record: ctor 0x003B7160 and copies at 0x003A6360/0x003B1B40 witness
// vtable VA 0x010EC760, dword +4, byte +8, dword +0xC; sizeof is 16.
// Parse table VA 0x010ECC38; append call via ILT 0x00003F3A to 0x003B1B40.
// The early throwing guard keeps the native record in function scope;
// VC7.1 reserves separate 8-byte exception and 16-byte record slots.
typedef int Int;

class INI;
typedef void (*INIFieldParseProc)( INI *, void *, void *, const void * );
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	Int offset;
};

class INIException
{
public:
	INIException( Int code, const char *msg, ... );
	INIException( const INIException &other );
	~INIException();

private:
	char *mFailureMessage;
	Int m_argCount;
};

class INI
{
public:
	void initFromINI( void *what, const FieldParse *parseTable );
	static void parseBool( INI *ini, void *instance, void *store, const void *userData );
	static void parseSecondsToMillis( INI *ini, void *instance, void *store, const void *userData );
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

// Retail keeps the field names as separate .rdata strings ahead of the table.
extern const char g_Va010ECBE0[] = "DelayFromActStart";
extern const char g_Va010ECBD4[] = "FlashTime";
extern const char g_Va010ECBC4[] = "SummaryEvent";

// Retail .rdata VA 0x010ECC38, 64 bytes: three entries plus the null row.
extern const FieldParse Rva003B7190RecordFieldParseTable[] =
{
	{ g_Va010ECBE0, INI::parseSecondsToMillis, 0, 0x04 },
	{ g_Va010ECBD4, INI::parseSecondsToMillis, 0, 0x0C },
	{ g_Va010ECBC4, INI::parseBool, 0, 0x08 },
	{ 0, 0, 0, 0 }
};

class BfmeItemXN;

class Gen003B1B40
{
public:
	void bfmeAppend( BfmeItemXN *record );
};

// ?ParseFlashRegionsEvent@@YAXPAVINI@@PAX1PBX@Z
void ParseFlashRegionsEvent(INI *ini, void *instance, void *, const void *)
{
    if (!ini || !instance)
        throw INIException(3, "ParseFlashRegionsEvent::Invalid data passed in.");

    Rva003B7190Record record;
    ini->initFromINI(&record, Rva003B7190RecordFieldParseTable);
    static_cast<Gen003B1B40 *>(instance)->bfmeAppend(
        reinterpret_cast<BfmeItemXN *>(&record));
}
