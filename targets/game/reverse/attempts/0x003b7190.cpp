// ?ParseFlashRegionsEvent@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.85 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: ParseFlashRegionsEvent (retail 0x003B7190 145 B; a gap claimed
// through its own exception text -- the target-table estimate 0x003B71D6/75
// landed on the throw tail, the real start is the byte after the previous
// 0xCC run at 0x003B7190).  With no INI or instance it throws INIException(3
// "ParseFlashRegionsEvent::Invalid data passed in."); otherwise a record
// (vtable, one dword, one flag byte, one dword, all zeroed by the inline
// constructor) is filled through INI::initFromINI with the table at VA
// 0x010ECC38 and handed to the instance's add routine (thunk 0x00403F3A).
// The virtual destructor's body is empty, so the compiler elides the call.
//
// BLOCKER (frame-size lever, unsolved): retail reserves sub esp,0x18 (24)
// with the record's own bytes occupying only the LAST 16 of those 24 (the
// record's "this" sits at frame+8, not frame+0 -- confirmed by walking the
// EH-prologue math both ways).  A local cl.exe here reproduces the retail
// pattern only when the POD record is >= 20 bytes (sub esp becomes
// sizeof(record)+8, e.g. 20B record -> sub esp 0x1c, 24B record -> sub esp
// 0x20) and reproduces NO extra 8 bytes when the record is <= 16 bytes (sub
// esp == sizeof(record) exactly, no slack).  There is no POD record size
// that lands on retail's exact 0x18: the 16B/20B/24B rungs give 0x10/0x1c/
// 0x20.  This looks like a GS-cookie-style small-object threshold that
// differs between this toolchain and the original compiler, OR the record
// has a non-POD member (e.g. an AsciiString) that would explain the extra 8
// bytes without changing the write pattern IF its ctor/dtor calls could be
// proven side-effect-free and elided -- but any AsciiString modeled per the
// landed ParseWorldTextBlock.cpp shape has an out-of-line releaseBuffer()
// dtor call that is NOT observed in the retail bytes, so a plain 3-member
// AsciiString substitution will not work as-is. A worker with more time
// should try: (1) shape_levers.md's EH-state / throw() lessons in case the
// two initFromINI/add calls being marked throw() changes the reserved slack,
// (2) a differently-shaped record (e.g. 2 fields + a wider flag) to probe
// the exact rung transition between 16 and 20 bytes, (3) checking whether
// the missing 8 bytes are actually a caller-frame artifact of the two
// leading null-checks (ini/instance) rather than the record at all.
//
// Diff at last probe: 11 non-reloc bytes differ (of 145), first divergence
// at +0x1b (sub esp immediate); everything else -- both null checks, the
// initFromINI/add calls, the throw tail and the exact exception string --
// matches byte-for-byte modulo relocations.  t=35min model=sonnet

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
		Rva003B7190Record record;
		ini->initFromINI( &record, Rva003B7190RecordFieldParseTable );
		((Rva003B7190Owner *)instance)->add( &record );
	}
	else
		throw INIException( 3, "ParseFlashRegionsEvent::Invalid data passed in." );
}
