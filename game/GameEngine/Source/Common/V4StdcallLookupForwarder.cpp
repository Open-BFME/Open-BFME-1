// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include "ascii_string.h"
#include <vector>

// One 29-byte __stdcall free function: look one object up by its first argument
// and, when the lookup answers something, pass the second argument to it.
//
//     mov eax,[esp+4] / push eax / call <lookup>
//     test eax,eax / je .out
//     mov ecx,[esp+8] / push ecx / mov ecx,eax / call <set>
//   .out: ret 8
//
// WHAT THE BYTES SHOW.  The incoming ecx is never read and is overwritten before
// the second call, so nothing arrives in a register: this is a free function,
// and `ret 8` gives it exactly two dword stack arguments.  The lookup's argument
// is pushed and NOT cleaned up by this function, so the lookup is __stdcall too;
// the second call loads its receiver from eax -- the lookup's own result -- so it
// is a __thiscall member of whatever came back.  The second argument is moved as
// a DWORD, so it is a dword-sized type, not a narrower one widened for the push.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the callee
// pins are address-derived and additive.

class Open2Rec3A4420
{
public:
	Open2Rec3A4420() : m_at08(), m_at0c() {}
	Open2Rec3A4420( const Open2Rec3A4420 &source );
	~Open2Rec3A4420();

	int m_at00;
	int m_at04;
	AsciiString m_at08;
	AsciiString m_at0c;
	int m_at10;
};

struct Gen_uwt_0002aaa9;
inline void *operator new( unsigned int, Gen_uwt_0002aaa9 *place )
{
	return place;
}
void operator delete( void *, Gen_uwt_0002aaa9 * );

namespace _STL
{
struct Rva003A5500Element
{
	char m_body[ 20 ];
};

#define BFME_OPEN2_ELEMENT_CONSTRUCT \
	template <> \
	__forceinline void _Construct<Rva003A5500Element, Rva003A5500Element>( \
		Rva003A5500Element *destination, const Rva003A5500Element &source ) \
	{ \
		new ( (Gen_uwt_0002aaa9 *)destination ) Open2Rec3A4420( \
			reinterpret_cast<const Open2Rec3A4420 &>( source ) ); \
	}
BFME_OPEN2_ELEMENT_CONSTRUCT
#undef BFME_OPEN2_ELEMENT_CONSTRUCT

template <typename T, typename Allocator>
class public_vector : public vector<T, Allocator>
{
public:
	using vector<T, Allocator>::_M_finish;
	using vector<T, Allocator>::_M_end_of_storage;
	using vector<T, Allocator>::_M_insert_overflow;
};
}

struct Rva006122A0Item
{
};

class Rva006122A0Mgr
{
public:
	Rva006122A0Item *find( const AsciiString &name );
};

class Rva0060A910
{
public:
	void run();
};

class BfmeGameCW
{
};

extern BfmeGameCW *g_bfmeGameCW;

class Gen003C0110Result
{
public:
	void set( int value );
	void apply( int a, int b, int c, int d, int e );
	char m_pad00[ 0x1F ];
	bool m_at1F;
	char m_pad20[ 0x08 ];
	_STL::public_vector<_STL::Rva003A5500Element,
		_STL::allocator<_STL::Rva003A5500Element> > m_entries;
};

Gen003C0110Result * __stdcall Gen003C0110Lookup( void * key );

void __stdcall Rva003C0220( void * key, int value )
{
	Gen003C0110Result *found = Gen003C0110Lookup( key );
	if( found )
		found->set( value );
}

// ------------------------------------------------------- same lookup, six args
// 0x003C0250 opens with the same `mov eax,[esp+4] / push eax / call` into the
// same lookup and, like the row above, does nothing when it answers null -- but
// it answers a BOOL rather than nothing, and `ret 0x18` gives it six dword
// arguments.  Five of them are forwarded to a __thiscall member of the result
// alongside a literal zero; the sixth is tested as a BYTE (`mov cl,[esp+0x10]`)
// and only decides whether a flag at +0x1F of the result is set.  `mov al,1` is
// hoisted ABOVE that branch, so the true result is shared by both paths: the
// function answers true whenever the lookup found anything.

bool __stdcall Rva003C0250( void * key, int a, bool flag, int b, int c, int d )
{
	Gen003C0110Result *found = Gen003C0110Lookup( key );
	if( !found )
		return false;
	found->apply( a, b, c, 0, d );
	if( flag )
		found->m_at1F = true;
	return true;
}

void Gen003C0110Result::apply( int first, int second, int third,
	int callback, int last )
{
#define BFME_OPEN2_CONSTRUCT_CALL _STL::_Construct
	Gen003C0110Result *self = this;
	Open2Rec3A4420 local;
	local.m_at00 = ((int *)first)[0];
	local.m_at04 = ((int *)first)[1];
	local.m_at08.set( *(const AsciiString *)second );
	local.m_at0c.set( *(const AsciiString *)third );
	_STL::public_vector<_STL::Rva003A5500Element,
		_STL::allocator<_STL::Rva003A5500Element> > *entries =
		&self->m_entries;
	local.m_at10 = last;
	if ( entries->_M_finish != entries->_M_end_of_storage._M_data )
	{
		BFME_OPEN2_CONSTRUCT_CALL( entries->_M_finish,
			*(const _STL::Rva003A5500Element *)(void *)&local );
		++entries->_M_finish;
	}
	else
	{
		entries->_M_insert_overflow( entries->_M_finish,
			*(const _STL::Rva003A5500Element *)(void *)&local,
			reinterpret_cast<const _STL::__false_type &>( callback ),
			1UL, true );
	}

	if ( *(const unsigned char *)&callback )
	{
		Rva006122A0Item *item =
			((Rva006122A0Mgr *)g_bfmeGameCW)->find(
				*(const AsciiString *)((char *)self + 8) );
		((Rva0060A910 *)item)->run();
	}
#undef BFME_OPEN2_CONSTRUCT_CALL
}
