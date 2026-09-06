// ?parseNameCountListEntry@Rva0022DA50@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: INI field parser at 0x0022DA50 (223 B): a name token and an
// optional count (INI::scanInt or 1 when the line ends: the Bfme5IniNamedValue
// shape) become an (AsciiString name Int count) entry pushed onto the
// list<entry> member at instance+0x174 (STLport exceptions off: node from the
// static allocator the element copied by the out-of-line body at 0x0022D610).
// Address-derived names.

typedef int Int;

extern "C" unsigned int __cdecl strlen( const char *s );
#pragma intrinsic( strlen )

class RetailLayoutString
{
public:
	RetailLayoutString() : m_data( 0 ) {}
	~RetailLayoutString() { releaseBuffer(); }
	void set( const char *s, int n );

private:
	void releaseBuffer( void );
	void *m_data;
};

class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	const char *getNextTokenOrNull( const char *seps = 0 );
	static Int scanInt( const char *token );
};

struct Rva0022DA50Entry
{
	Rva0022DA50Entry() : m_count( 0 ) {}

	RetailLayoutString m_name;
	Int m_count;
};

void *__cdecl Rva0082E540NodeAllocate( unsigned int bytes );
void __cdecl Rva0022D610Construct( Rva0022DA50Entry *where, const Rva0022DA50Entry &value );

struct Rva0022DA50ListNode
{
	Rva0022DA50ListNode *m_next;
	Rva0022DA50ListNode *m_prev;
	Rva0022DA50Entry m_data;
};

class Rva0022DA50List
{
public:
	void push_back( const Rva0022DA50Entry &value )
	{
		Rva0022DA50ListNode *position = m_node;
		Rva0022DA50ListNode *node = (Rva0022DA50ListNode *)Rva0082E540NodeAllocate( sizeof( Rva0022DA50ListNode ) );
		Rva0022D610Construct( &node->m_data, value );
		Rva0022DA50ListNode *previous = position->m_prev;
		node->m_next = position;
		node->m_prev = previous;
		previous->m_next = node;
		position->m_prev = node;
	}

private:
	Rva0022DA50ListNode *m_node;
};

struct Rva0022DA50Owner
{
	char m_unreconstructed[ 0x174 ];
	Rva0022DA50List m_entries;
};

class Rva0022DA50
{
public:
	static void parseNameCountListEntry( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseNameCountListEntry@Rva0022DA50@@SAXPAVINI@@PAX1PBX@Z
void Rva0022DA50::parseNameCountListEntry( INI *ini, void *instance, void *, const void * )
{
	const char *name = ini->getNextToken();
	const char *num = ini->getNextTokenOrNull();
	Int count = num ? INI::scanInt( num ) : 1;
	Rva0022DA50Entry entry;
	entry.m_name.set( name, name ? (int)strlen( name ) : 0 );
	Rva0022DA50List &entries = ((Rva0022DA50Owner *)instance)->m_entries;
	entry.m_count = count;
	entries.push_back( entry );
}
