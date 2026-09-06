// ?parseNameRealVector@Rva000A8820@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.35 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME7: INI field parser at 0x000A8820 (222 B): same shape as the
// sibling at 0x0025CDB0 (name token, INI::parseReal storing straight into
// the entry's Real slot, RetailLayoutString name set with an inline
// strlen guarded against a null token) but the vector sits at instance
// +0x24/+0x28/+0x2c and the landed neighbour Gen000A87D0::bfmeAppend
// (P6MemberVectorPushBack.cpp) is the out-of-line copy of the same
// push_back this body inlines. Names are address-derived.

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

struct Rva000A8500Element
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
class vector<Rva000A8500Element, allocator<Rva000A8500Element> >
{
public:
	Rva000A8500Element *_M_start;
	Rva000A8500Element *_M_finish;
	Rva000A8500Element *_M_end_of_storage;

protected:
	void _M_insert_overflow( Rva000A8500Element *, const Rva000A8500Element &,
		const __false_type &, unsigned int, bool );
};

template <class Type, class Allocator>
class public_vector : public vector<Type, Allocator>
{
public:
	using vector<Type, Allocator>::_M_insert_overflow;
};
}

class Rva000A8820Store
{
public:
	char m_bfmeHead[ 0x24 ];
	_STL::public_vector<_STL::Rva000A8500Element, _STL::allocator<_STL::Rva000A8500Element> > m_bfmeItems;
};

class Rva000A8820
{
public:
	static void parseNameRealVector( INI *ini, void *instance, void *, const void * );
};

// ?parseNameRealVector@Rva000A8820@@SAXPAVINI@@PAX1PBX@Z
void Rva000A8820::parseNameRealVector( INI *ini, void *instance, void *, const void * )
{
	_STL::Rva000A8500Element entry;
	const char *token = ini->getNextToken();
	const void *userData = 0;
	INI::parseReal( ini, instance, &entry.m_value, userData );
	entry.m_name.set( token, token ? (int)strlen( token ) : 0 );

	Rva000A8820Store *self = (Rva000A8820Store *)instance;
	_STL::public_vector<_STL::Rva000A8500Element, _STL::allocator<_STL::Rva000A8500Element> > &items = self->m_bfmeItems;

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
