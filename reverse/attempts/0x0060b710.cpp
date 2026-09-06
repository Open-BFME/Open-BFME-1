// ?ParseIconObjectBlock@@YAXPAVINI@@PAX@Z
// partial score=0.4 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME7: block parser at 0x0060B710 (209 B), BFME-only (no Zero Hour
// twin).  The name is the binary's own: the INIException it throws on a
// null INI pushes the literal "ParseIconObjectBlock::Invalid data passed
// in." (VA 0x1115D6C).  A 28-byte icon record is allocated and its small
// constructor is inlined (four zeroed dwords, one AsciiString field at
// +8 assigned from the first token, a float 1.0 at +0x10, three bool
// fields at +0x14..+0x16, a trailing zeroed dword at +0x18), then
// ini->initFromINI() runs the field table at VA 0x1115CC0 and the record
// pointer is pushed onto the instance's vector<Icon *> at +0xc (trivial
// pointer copy, matching the true_type _M_insert_overflow pinned at
// 0x0060B320).  The record class is address-derived: nothing in this body
// reads a member besides the name and the ctor-time defaults.

typedef int Int;
typedef float Real;
typedef bool Bool;

class INIException
{
public:
	INIException(Int code, const char *msg, ...);
	INIException(const INIException &other);
};

class INI;

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	AsciiString &operator=(const char *s);

private:
	char *m_data;
};

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	void initFromINI(void *instance, const struct FieldParse *table);
};

struct FieldParse;

class Rva0060B6E0IconObject
{
public:
	Int m_unk0;
	Int m_unk4;
	AsciiString m_name;
	Int m_unkC;
	Real m_alpha;
	Bool m_flag14;
	Bool m_flag15;
	Bool m_flag16;
	Int m_unk18;

	Rva0060B6E0IconObject()
	{
		m_unk0 = 0;
		m_unk4 = 0;
		m_unkC = 0;
		m_alpha = 1.0f;
		m_flag14 = false;
		m_flag15 = false;
		m_flag16 = false;
		m_unk18 = 0;
	}
};

extern const FieldParse Rva0060B710FieldParseTable[];

namespace _STL
{
struct __true_type
{
};

template <class Type>
class allocator
{
};

class Rva0060B710Store
{
public:
	char m_bfmeHead[ 0xc ];
	Rva0060B6E0IconObject **_M_start;
	Rva0060B6E0IconObject **_M_finish;
	Rva0060B6E0IconObject **_M_end_of_storage;

	void _M_insert_overflow( Rva0060B6E0IconObject **position, Rva0060B6E0IconObject *const &value,
		const __true_type &, unsigned int fillLength, bool atEnd );
};
}

// ?ParseIconObjectBlock@@YAXPAVINI@@PAX@Z
void ParseIconObjectBlock( INI *ini, void *instance )
{
	if( !ini )
		throw INIException( 3, "ParseIconObjectBlock::Invalid data passed in." );

	Rva0060B6E0IconObject *icon = new Rva0060B6E0IconObject();

	if( icon )
	{
		const char *token = ini->getNextToken();
		if( token )
			icon->m_name = token;

		ini->initFromINI( icon, Rva0060B710FieldParseTable );
	}

	_STL::Rva0060B710Store *self = (_STL::Rva0060B710Store *)instance;

	if( self->_M_finish != self->_M_end_of_storage )
	{
		*self->_M_finish = icon;
		++self->_M_finish;
	}
	else
	{
		self->_M_insert_overflow( self->_M_finish, icon,
			_STL::__true_type(), 1, true );
	}
}
