// ?append@Rva003A3B50Owner@@QAEXPBURva003A3B50Input@@@Z
// partial score=0.35 date=2026-09-15
// Scratch-only reconstruction of retail RVA 0x003A3B50 (206 bytes).
// The owning class and method identity are not recovered; the address-derived
// names are intentional.  The vector and element contracts are evidenced by
// the matched STLport family sources and the four retail call targets.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <new>

struct Rva003A3B50Input
{
	int x, y, z;
};

struct Rva003A35A0Element
{
	unsigned char m_prefix[0xA4];
	Rva003A3B50Input m_point;
	unsigned char m_tail[8];

	// The retail default constructor is the unresolved ILT 0x00022F0C
	// (body 0x003A18D0); leave its exact decorated name for the root pin.
	Rva003A35A0Element();
	Rva003A35A0Element( const Rva003A35A0Element & );
	~Rva003A35A0Element();
	Rva003A35A0Element &operator=( const Rva003A35A0Element &other );
};

// This is the same TU-local STLport vector surface used by the matched
// Rva003A35A0 push_back witness.  Here inlining and a real dispatch-tag object
// reproduce retail's full local-element frame and placement-copy lifetime.
// The helper bodies remain existing ledgered targets, but the default ctor's
// address-derived alias is intentionally unresolved until independently pinned.
namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type, class Allocator = allocator<Type> >
class vector
{
public:
	__forceinline void push_back( const Type *value );

protected:
	void _M_insert_overflow( Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd );

	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};

template <class Type, class Allocator>
void vector<Type, Allocator>::push_back( const Type *value )
{
	if ( _M_finish != _M_end_of_storage )
	{
		::new ( static_cast<void *>( _M_finish ) ) Type( *value );
		++_M_finish;
	}
	else
	{
		_M_insert_overflow( _M_finish, *value,
			__false_type(), 1, true );
	}
}
}

class Rva003A3B50Owner
{
public:
	void append( const Rva003A3B50Input *value );

private:
	char m_unreconstructed_00[ 0x2C ];
	_STL::vector<Rva003A35A0Element> m_elements;
};

// ?append@Rva003A3B50Owner@@QAEXPBURva003A3B50Input@@@Z
void Rva003A3B50Owner::append( const Rva003A3B50Input *value )
{
	Rva003A35A0Element element;
	element.m_point = *value;
	m_elements.push_back( &element );
}
