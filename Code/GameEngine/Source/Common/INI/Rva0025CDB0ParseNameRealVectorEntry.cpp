// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: INI field parsers at 0x0025CDB0 (231 B) and its byte-twin
// 0x000A8820 (222 B; vector at instance+0x24 with its own copy-construct and
// overflow bodies at 0x000A87C0 / 0x000A85F0): a name token then a
// Real through INI::parseReal (scanned into its own local first) become a
// (name value) entry pushed onto the vector of eight-byte entries at
// instance+0x210.  The name is written with StringBase::set(text length)
// after the inline strlen; the vector push_back is inline (STLport exceptions
// off) around the out-of-line copy-construct grid body at 0x0025CD50 and the
// _M_insert_overflow at 0x0025CB00.  The separate Real local is what makes
// the frame 0xC bytes (a lane model without it came out 4 bytes short).
// Address-derived names.

typedef float Real;

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
	static void parseReal( INI *ini, void *instance, void *store, const void *userData );
};

struct Rva0025CDB0Entry
{
	RetailLayoutString m_name;
	Real m_value;
};

struct Rva0025CDB0FalseType
{
	Rva0025CDB0FalseType() {}
};

void __cdecl Rva0025CD50CopyConstruct( Rva0025CDB0Entry *where, const Rva0025CDB0Entry &value );

class Rva0025CDB0Vector
{
public:
	void push_back( const Rva0025CDB0Entry &value )
	{
		if( m_finish != m_endOfStorage )
		{
			Rva0025CD50CopyConstruct( m_finish, value );
			++m_finish;
		}
		else
			_M_insert_overflow( m_finish, value, Rva0025CDB0FalseType(), 1, true );
	}

private:
	void _M_insert_overflow( Rva0025CDB0Entry *pos, const Rva0025CDB0Entry &value, const Rva0025CDB0FalseType &, unsigned int n, bool atEnd );

	Rva0025CDB0Entry *m_start;
	Rva0025CDB0Entry *m_finish;
	Rva0025CDB0Entry *m_endOfStorage;
};

struct Rva0025CDB0Owner
{
	char m_unreconstructed[ 0x210 ];
	Rva0025CDB0Vector m_entries;
};

class Rva0025CDB0
{
public:
	static void parseNameRealVectorEntry( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseNameRealVectorEntry@Rva0025CDB0@@SAXPAVINI@@PAX1PBX@Z
void Rva0025CDB0::parseNameRealVectorEntry( INI *ini, void *instance, void *, const void *userData )
{
	const char *token = ini->getNextToken();
	Rva0025CDB0Owner *self = (Rva0025CDB0Owner *)instance;
	Real value = 0.0f;
	INI::parseReal( ini, instance, &value, userData );
	Rva0025CDB0Entry entry;
	entry.m_name.set( token, token ? (int)strlen( token ) : 0 );
	entry.m_value = value;
	self->m_entries.push_back( entry );
}

struct Rva000A8820Entry
{
	RetailLayoutString m_name;
	Real m_value;
};

void __cdecl Rva000A87C0CopyConstruct( Rva000A8820Entry *where, const Rva000A8820Entry &value );

class Rva000A8820Vector
{
public:
	void push_back( const Rva000A8820Entry &value )
	{
		if( m_finish != m_endOfStorage )
		{
			Rva000A87C0CopyConstruct( m_finish, value );
			++m_finish;
		}
		else
			_M_insert_overflow( m_finish, value, Rva0025CDB0FalseType(), 1, true );
	}

private:
	void _M_insert_overflow( Rva000A8820Entry *pos, const Rva000A8820Entry &value, const Rva0025CDB0FalseType &, unsigned int n, bool atEnd );

	Rva000A8820Entry *m_start;
	Rva000A8820Entry *m_finish;
	Rva000A8820Entry *m_endOfStorage;
};

struct Rva000A8820Owner
{
	char m_unreconstructed[ 0x24 ];
	Rva000A8820Vector m_entries;
};

class Rva000A8820
{
public:
	static void parseNameRealVectorEntry( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseNameRealVectorEntry@Rva000A8820@@SAXPAVINI@@PAX1PBX@Z
void Rva000A8820::parseNameRealVectorEntry( INI *ini, void *instance, void *, const void *userData )
{
	const char *token = ini->getNextToken();
	Rva000A8820Owner *self = (Rva000A8820Owner *)instance;
	Real value = 0.0f;
	INI::parseReal( ini, instance, &value, userData );
	Rva000A8820Entry entry;
	entry.m_name.set( token, token ? (int)strlen( token ) : 0 );
	entry.m_value = value;
	self->m_entries.push_back( entry );
}
