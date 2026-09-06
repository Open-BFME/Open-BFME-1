// ?parseNameRealVector@Rva0025CDB0@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.35 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME7: INI field parser at 0x0025CDB0 (231 B): reads a name token
// then hands the instance/store address of a fresh (name value) entry's
// Real slot straight to the generic INI::parseReal helper (it re-reads the
// next token itself and stores the scanned real), sets the layout-string
// name from the first token (RetailLayoutString::set with an inline
// strlen guarded against a null token) and pushes the finished entry onto
// the instance's vector at +0x210 -- the same element type, offset and
// overflow routine as the landed neighbour Gen0025CD50::bfmeAppend, so the
// push_back shape is duplicated here rather than called (it is inlined at
// this call site, out of line at that one). Names are address-derived.

typedef int Int;
typedef float Real;

extern "C" __declspec(dllimport) unsigned int __stdcall strlen(const char *s);

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
};

class RetailLayoutString
{
public:
	RetailLayoutString()
	{
		m_data = 0;
	}

	~RetailLayoutString();

	void set(const char *text, int length);

private:
	char *m_data;
};

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type>
void __cdecl _Construct(Type *destination, const Type &value);

struct Rva0025CB00Element
{
	RetailLayoutString m_name;
	Real m_value;
};

template <class Type, class Allocator>
class vector
{
public:
	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;

	void _M_insert_overflow( Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd );
};

template <>
class vector<Rva0025CB00Element, allocator<Rva0025CB00Element> >
{
public:
	Rva0025CB00Element *_M_start;
	Rva0025CB00Element *_M_finish;
	Rva0025CB00Element *_M_end_of_storage;

protected:
	void _M_insert_overflow( Rva0025CB00Element *, const Rva0025CB00Element &,
		const __false_type &, unsigned int, bool );
};

template <class Type, class Allocator>
class public_vector : public vector<Type, Allocator>
{
public:
	using vector<Type, Allocator>::_M_insert_overflow;
};
}

class Rva0025CDB0Store
{
public:
	char m_bfmeHead[ 0x210 ];
	_STL::public_vector<_STL::Rva0025CB00Element, _STL::allocator<_STL::Rva0025CB00Element> > m_bfmeItems;
};

class Rva0025CDB0
{
public:
	static void parseNameRealVector( INI *ini, void *instance, void *, const void * );
};

// ?parseNameRealVector@Rva0025CDB0@@SAXPAVINI@@PAX1PBX@Z
void Rva0025CDB0::parseNameRealVector( INI *ini, void *instance, void *, const void * )
{
	_STL::Rva0025CB00Element entry;
	const char *token = ini->getNextToken();
	INI::parseReal( ini, instance, &entry.m_value, 0 );
	entry.m_name.set( token, token ? (int)strlen( token ) : 0 );

	Rva0025CDB0Store *self = (Rva0025CDB0Store *)instance;
	_STL::public_vector<_STL::Rva0025CB00Element, _STL::allocator<_STL::Rva0025CB00Element> > &items = self->m_bfmeItems;

	if ( items._M_finish != items._M_end_of_storage )
	{
		_STL::_Construct( items._M_finish, entry );
		++items._M_finish;
	}
	else
	{
		items._M_insert_overflow( items._M_finish, entry,
			reinterpret_cast<const _STL::__false_type &>( entry ), 1, true );
	}
}
