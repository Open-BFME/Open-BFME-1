// ?parseTemplateNameCountListEntry@Rva0014C8E0@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.95 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: INI field parser at 0x0014C8E0 (196 B): INI::parseThingTemplate
// and INI::parseInt scan a template pointer and a count into locals then an
// (AsciiString name Int count) entry (count value-initialised) is filled and
// pushed only when the template exists and its name at +0x20 is not empty
// (the inline isNotEmpty reads the length word four bytes into the string
// data) onto the list the store argument's first pointer
// designates (STLport exceptions off: node from the static allocator the
// element copied by the out-of-line pair _Construct body at 0x0014BBC0).
// Address-derived names.

typedef int Int;

struct Rva0014C8E0StringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_length;
	unsigned short m_pad;
};

class Rva0014C8E0String
{
public:
	Rva0014C8E0String() : m_data( 0 ) {}
	~Rva0014C8E0String() { releaseBuffer(); }
	void set( const Rva0014C8E0String &other );
	bool isNotEmpty( void ) const { return m_data != 0 && m_data->m_length != 0; }

private:
	void releaseBuffer( void );
	Rva0014C8E0StringData *m_data;
};

class INI
{
public:
	static void parseThingTemplate( INI *ini, void *instance, void *store, const void *userData );
	static void parseInt( INI *ini, void *instance, void *store, const void *userData );
};

struct Rva0014C8E0Template
{
	char m_unreconstructed[ 0x20 ];
	Rva0014C8E0String m_name;
};

struct Rva0014C8E0Entry
{
	Rva0014C8E0Entry() : m_count( 0 ) {}

	Rva0014C8E0String m_name;
	Int m_count;
};

void *__cdecl Rva0082E540NodeAllocate( unsigned int bytes );
void __cdecl Rva0014BBC0Construct( Rva0014C8E0Entry *where, const Rva0014C8E0Entry &value );

struct Rva0014C8E0ListNode
{
	Rva0014C8E0ListNode *m_next;
	Rva0014C8E0ListNode *m_prev;
	Rva0014C8E0Entry m_data;
};

class Rva0014C8E0List
{
public:
	void push_back( const Rva0014C8E0Entry &value )
	{
		Rva0014C8E0ListNode *position = m_node;
		Rva0014C8E0ListNode *node = (Rva0014C8E0ListNode *)Rva0082E540NodeAllocate( sizeof( Rva0014C8E0ListNode ) );
		Rva0014BBC0Construct( &node->m_data, value );
		Rva0014C8E0ListNode *previous = position->m_prev;
		node->m_next = position;
		node->m_prev = previous;
		previous->m_next = node;
		position->m_prev = node;
	}

private:
	Rva0014C8E0ListNode *m_node;
};

struct Rva0014C8E0Owner
{
	Rva0014C8E0List *m_entries;
};

class Rva0014C8E0
{
public:
	static void parseTemplateNameCountListEntry( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseTemplateNameCountListEntry@Rva0014C8E0@@SAXPAVINI@@PAX1PBX@Z
void Rva0014C8E0::parseTemplateNameCountListEntry( INI *ini, void *, void *store, const void * )
{
	const Rva0014C8E0Template *thingTemplate;
	Int count;
	INI::parseThingTemplate( ini, 0, &thingTemplate, 0 );
	INI::parseInt( ini, 0, &count, 0 );
	Rva0014C8E0Entry entry;
	if( thingTemplate && thingTemplate->m_name.isNotEmpty() )
	{
		entry.m_name.set( thingTemplate->m_name );
		Rva0014C8E0List *entries = ((Rva0014C8E0Owner *)store)->m_entries;
		entry.m_count = count;
		entries->push_back( entry );
	}
}
