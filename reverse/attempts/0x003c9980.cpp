// ?parseNamedSubBlock@Rva003C9980@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.2 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc

// Open-BFME7: INI field parser at 0x003C9980 (241 B). Reads a name token,
// builds an AsciiString temporary from it, allocates a 244-byte object and
// placement-constructs it (through the still-unmatched 0x0061AF80, 304 B
// dump -- the null-check-and-state-byte shape of a "new X(name)" call with
// EH) taking the AsciiString by reference, releases the temporary, then
// calls a wrapper on the new object with the INI pointer (0x00036F9D,
// resolving to the already-matched trivial forwarder
// BfmeThingDCG::bfmeGoDCG shape, i.e. obj->initFromINI-style recursion)
// and finally push_back's the object pointer into the instance's vector
// at +0x30 (overflow thunk 0x00010596 resolves to the true_type 4-byte
// element _M_insert_overflow at 0x003C8F80). The callee at 0x0061AF80 is
// itself unmatched, so this body cannot be more than a rough skeleton
// until that lands; not yet byte-verified.

class INI;

class AsciiString
{
public:
	AsciiString( const char *s );
	~AsciiString();
};

class Rva003C9980Entry
{
public:
	Rva003C9980Entry( const AsciiString &name );
	void bfmeInitFromINI( INI *ini );
};

namespace _STL
{
struct __true_type
{
};

template <class Type>
class allocator
{
};
}

class Rva003C9980Store
{
public:
	char m_bfmeHead[ 0x30 ];
	Rva003C9980Entry **_M_start;
	Rva003C9980Entry **_M_finish;
	Rva003C9980Entry **_M_end_of_storage;

	void _M_insert_overflow( Rva003C9980Entry **position, Rva003C9980Entry *const &value,
		const _STL::__true_type &, unsigned int fillLength, bool atEnd );
};

class Rva003C9980
{
public:
	static void parseNamedSubBlock( INI *ini, void *instance, void *, const void * );
};

class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
};

// ?parseNamedSubBlock@Rva003C9980@@SAXPAVINI@@PAX1PBX@Z
void Rva003C9980::parseNamedSubBlock( INI *ini, void *instance, void *, const void * )
{
	const char *token = ini->getNextToken();
	Rva003C9980Entry *entry;

	{
		AsciiString name( token );
		entry = new Rva003C9980Entry( name );
	}

	entry->bfmeInitFromINI( ini );

	Rva003C9980Store *self = (Rva003C9980Store *)instance;
	if( self->_M_finish != self->_M_end_of_storage )
	{
		*self->_M_finish = entry;
		++self->_M_finish;
	}
	else
	{
		self->_M_insert_overflow( self->_M_finish, entry,
			_STL::__true_type(), 1, true );
	}
}
