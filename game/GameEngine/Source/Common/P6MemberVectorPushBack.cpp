// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: sixteen STLport vector<T>::push_back bodies, each inlined into
// a one-line member of the class that owns the vector.
//
// Rva000BD360VectorPushBackBody.cpp lands this shape where the vector IS the
// receiver.  Here it is a MEMBER: every body opens `mov eax,[ecx+K+4]` /
// `lea esi,[ecx+K]`, so `this` is the owner and K is where its vector sits.
//
// TWO SPELLING FACTS, EACH WORTH A FEW BYTES.
//
// The parameter must belong to the OUTER function.  Routing through a real
// push_back taking `const Type *` and letting MSVC inline it costs four bytes:
// the dispatch tag is aliased onto the value parameter's own stack slot, and
// when that parameter belongs to the INLINED function the compiler first
// copies the caller's argument into it (`mov edx,[esp+4]` / `mov [esp+8],edx`)
// before taking its address.  Written directly in the owner's member, the
// aliased slot IS the incoming argument and the copy disappears.
//
// And the vector must be named ONCE, as a reference.  Spelled `m_bfmeItems.`
// at every use, MSVC materialises `this` in esi and reads the fields at
// +0x34/+0x38; retail materialises the VECTOR's address instead -- `lea
// esi,[ecx+0x30]` and then +4/+8 -- while still folding the very first read
// back onto ecx as `[ecx+0x34]`, because esi is not live yet.  Binding
// `vector &items = m_bfmeItems;` once and using `items.` throughout gives
// exactly that, and it is the difference between 65 bytes and 63.
//
// Two paths and nothing else.  With room left it constructs at the finish
// pointer and steps it by the element width -- RELOADING the finish pointer
// from the object afterwards rather than reusing the copy it had, which is
// what a plain `++_M_finish` on a member produces.  With no room it hands
// everything to _M_insert_overflow with a fill length of one and the at-end
// flag set.
//
// FOUR AXES, ALL READ DIRECTLY: the vector's offset in its owner, the element
// width, and the two ILT slots.  No two of the sixteen share a construct or an
// overflow slot, so these are sixteen distinct element types; the widths
// repeat (0x20 three times, 0xC three times, 0x14 and 0x10 twice each) and the
// offsets do not, which is what tells the two apart.
//
// The 61/63/67 split in length is not a fifth axis: an offset or width needing
// an imm32 rather than an imm8 costs three bytes at each of its uses.
//
// IDENTITY IS NOT RECOVERED.  Owner and element are named for the address of
// the body; `char m_body[WIDTH]` carries the width and `char m_bfmeHead[K]`
// the offset, and neither is a claim about fields.

struct Rva001E9020Element
{
	char m_body[ 0x08 ];
};

namespace _STL
{
struct __false_type
{
};

template <class Type>
void __cdecl _Construct( Type *destination, const Type &value );

template <class Type>
class allocator
{
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
}

namespace _STL
{
struct Rva000A8500Element
{
	char m_body[ 0x08 ];
};

struct Rva0025CB00Element
{
	char m_body[ 0x08 ];
};

struct Rva003B0060Element
{
	char m_body[ 0x08 ];
};

typedef ::Rva001E9020Element Rva001E9020Element;

void __cdecl BfmeRva001E9020Construct( Rva001E9020Element *destination,
	const Rva001E9020Element &value );

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

template <>
class vector<Rva003B0060Element, allocator<Rva003B0060Element> >
{
public:
	Rva003B0060Element *_M_start;
	Rva003B0060Element *_M_finish;
	Rva003B0060Element *_M_end_of_storage;

protected:
	void _M_insert_overflow( Rva003B0060Element *, const Rva003B0060Element &,
		const __false_type &, unsigned int, bool );
};

template <>
class vector<Rva001E9020Element, allocator<Rva001E9020Element> >
{
public:
	Rva001E9020Element *_M_start;
	Rva001E9020Element *_M_finish;
	Rva001E9020Element *_M_end_of_storage;

protected:
	void _M_insert_overflow( Rva001E9020Element *, const Rva001E9020Element &,
		const __false_type &, unsigned int, bool );
};

template <class Type, class Allocator>
class public_vector : public vector<Type, Allocator>
{
public:
	using vector<Type, Allocator>::_M_insert_overflow;
};
}

struct P6Elem00365520
{
	char m_body[ 0xB4 ];
};

void __cdecl Bfme00365520Construct( P6Elem00365520 *destination, const P6Elem00365520 &value );	// ILT 0x00003193

struct P6Elem003AC1C0
{
	char m_body[ 0xDC ];
};

void __cdecl Bfme003AC1C0Construct( P6Elem003AC1C0 *destination, const P6Elem003AC1C0 &value );	// ILT 0x00015C85

struct P6Elem003B18A0
{
	char m_body[ 0x28 ];
};

void __cdecl Bfme003B18A0Construct( P6Elem003B18A0 *destination, const P6Elem003B18A0 &value );	// ILT 0x000181A6

struct P6Elem003B18F0
{
	char m_body[ 0x30 ];
};

void __cdecl Bfme003B18F0Construct( P6Elem003B18F0 *destination, const P6Elem003B18F0 &value );	// ILT 0x000200BD

struct P6Elem003B1940
{
	char m_body[ 0x20 ];
};

void __cdecl Bfme003B1940Construct( P6Elem003B1940 *destination, const P6Elem003B1940 &value );	// ILT 0x0003CA24

struct P6Elem003B1990
{
	char m_body[ 0xC ];
};

void __cdecl Bfme003B1990Construct( P6Elem003B1990 *destination, const P6Elem003B1990 &value );	// ILT 0x000140E2

struct P6Elem003B19E0
{
	char m_body[ 0x14 ];
};

void __cdecl Bfme003B19E0Construct( P6Elem003B19E0 *destination, const P6Elem003B19E0 &value );	// ILT 0x0003D843

struct P6Elem003B1A30
{
	char m_body[ 0x20 ];
};

void __cdecl Bfme003B1A30Construct( P6Elem003B1A30 *destination, const P6Elem003B1A30 &value );	// ILT 0x0000F9A2

struct P6Elem003B1A80
{
	char m_body[ 0x10 ];
};

void __cdecl Bfme003B1A80Construct( P6Elem003B1A80 *destination, const P6Elem003B1A80 &value );	// ILT 0x00013B79

struct P6Elem003B1AE0
{
	char m_body[ 0x14 ];
};

void __cdecl Bfme003B1AE0Construct( P6Elem003B1AE0 *destination, const P6Elem003B1AE0 &value );	// ILT 0x00031DA4

struct P6Elem003B1DF0
{
	char m_body[ 0x10 ];
};

void __cdecl Bfme003B1DF0Construct( P6Elem003B1DF0 *destination, const P6Elem003B1DF0 &value );	// ILT 0x0000927D

struct P6Elem003B1E50
{
	char m_body[ 0xC ];
};

void __cdecl Bfme003B1E50Construct( P6Elem003B1E50 *destination, const P6Elem003B1E50 &value );	// ILT 0x00049F49

struct P6Elem003B2060
{
	char m_body[ 0xC ];
};

void __cdecl Bfme003B2060Construct( P6Elem003B2060 *destination, const P6Elem003B2060 &value );	// ILT 0x0003C1A0

struct P6Elem003B2890
{
	char m_body[ 0x18 ];
};

void __cdecl Bfme003B2890Construct( P6Elem003B2890 *destination, const P6Elem003B2890 &value );	// ILT 0x000027A2

struct P6Elem003B7030
{
	char m_body[ 0x20 ];
};

void __cdecl Bfme003B7030Construct( P6Elem003B7030 *destination, const P6Elem003B7030 &value );	// ILT 0x00031791

struct P6Elem003C3B50
{
	char m_body[ 0x60 ];
};

void __cdecl Bfme003C3B50Construct( P6Elem003C3B50 *destination, const P6Elem003C3B50 &value );	// ILT 0x0002E3BB

class Gen00365520
{
public:
	void bfmeAppend( const P6Elem00365520 *value );

private:
	char m_bfmeHead[ 0x30 ];
	_STL::public_vector<P6Elem00365520, _STL::allocator<P6Elem00365520> > m_bfmeItems;	// +0x30
};

class Gen003AC1C0
{
public:
	void bfmeAppend( const P6Elem003AC1C0 *value );

private:
	char m_bfmeHead[ 0xC ];
	_STL::public_vector<P6Elem003AC1C0, _STL::allocator<P6Elem003AC1C0> > m_bfmeItems;	// +0x0C
};

class Gen003B18A0
{
public:
	void bfmeAppend( const P6Elem003B18A0 *value );

private:
	char m_bfmeHead[ 0x14 ];
	_STL::public_vector<P6Elem003B18A0, _STL::allocator<P6Elem003B18A0> > m_bfmeItems;	// +0x14
};

class Gen003B18F0
{
public:
	void bfmeAppend( const P6Elem003B18F0 *value );

private:
	char m_bfmeHead[ 0x20 ];
	_STL::public_vector<P6Elem003B18F0, _STL::allocator<P6Elem003B18F0> > m_bfmeItems;	// +0x20
};

class Gen003B1940
{
public:
	void bfmeAppend( const P6Elem003B1940 *value );

private:
	char m_bfmeHead[ 0x2C ];
	_STL::public_vector<P6Elem003B1940, _STL::allocator<P6Elem003B1940> > m_bfmeItems;	// +0x2C
};

class Gen003B1990
{
public:
	void bfmeAppend( const P6Elem003B1990 *value );

private:
	char m_bfmeHead[ 0x54 ];
	_STL::public_vector<P6Elem003B1990, _STL::allocator<P6Elem003B1990> > m_bfmeItems;	// +0x54
};

class Gen003B19E0
{
public:
	void bfmeAppend( const P6Elem003B19E0 *value );

private:
	char m_bfmeHead[ 0x6C ];
	_STL::public_vector<P6Elem003B19E0, _STL::allocator<P6Elem003B19E0> > m_bfmeItems;	// +0x6C
};

class Gen003B1A30
{
public:
	void bfmeAppend( const P6Elem003B1A30 *value );

private:
	char m_bfmeHead[ 0x78 ];
	_STL::public_vector<P6Elem003B1A30, _STL::allocator<P6Elem003B1A30> > m_bfmeItems;	// +0x78
};

class Gen003B1A80
{
public:
	void bfmeAppend( const P6Elem003B1A80 *value );

private:
	char m_bfmeHead[ 0x9C ];
	_STL::public_vector<P6Elem003B1A80, _STL::allocator<P6Elem003B1A80> > m_bfmeItems;	// +0x9C
};

class Gen003B1AE0
{
public:
	void bfmeAppend( const P6Elem003B1AE0 *value );

private:
	char m_bfmeHead[ 0x90 ];
	_STL::public_vector<P6Elem003B1AE0, _STL::allocator<P6Elem003B1AE0> > m_bfmeItems;	// +0x90
};

class Gen003B1DF0
{
public:
	void bfmeAppend( const P6Elem003B1DF0 *value );

private:
	char m_bfmeHead[ 0xB4 ];
	_STL::public_vector<P6Elem003B1DF0, _STL::allocator<P6Elem003B1DF0> > m_bfmeItems;	// +0xB4
};

class Gen003B1E50
{
public:
	void bfmeAppend( const P6Elem003B1E50 *value );

private:
	char m_bfmeHead[ 0xCC ];
	_STL::public_vector<P6Elem003B1E50, _STL::allocator<P6Elem003B1E50> > m_bfmeItems;	// +0xCC
};

class Gen003B2060
{
public:
	void bfmeAppend( const P6Elem003B2060 *value );

private:
	char m_bfmeHead[ 0xC0 ];
	_STL::public_vector<P6Elem003B2060, _STL::allocator<P6Elem003B2060> > m_bfmeItems;	// +0xC0
};

class Gen003B2890
{
public:
	void bfmeAppend( const P6Elem003B2890 *value );

private:
	char m_bfmeHead[ 0x84 ];
	_STL::public_vector<P6Elem003B2890, _STL::allocator<P6Elem003B2890> > m_bfmeItems;	// +0x84
};

class Gen003B7030
{
public:
	void bfmeAppend( const P6Elem003B7030 *value );

private:
	char m_bfmeHead[ 0x10 ];
	_STL::public_vector<P6Elem003B7030, _STL::allocator<P6Elem003B7030> > m_bfmeItems;	// +0x10
};

class Gen003C3B50
{
public:
	void bfmeAppend( const P6Elem003C3B50 *value );

private:
	char m_bfmeHead[ 0x68 ];
	_STL::public_vector<P6Elem003C3B50, _STL::allocator<P6Elem003C3B50> > m_bfmeItems;	// +0x68
};

class Gen000A87D0
{
public:
	void bfmeAppend( const _STL::Rva000A8500Element *value );

private:
	char m_bfmeHead[ 0x24 ];
	_STL::public_vector<_STL::Rva000A8500Element, _STL::allocator<_STL::Rva000A8500Element> > m_bfmeItems;
};

class Gen0025CD50
{
public:
	void bfmeAppend( const _STL::Rva0025CB00Element *value );

private:
	char m_bfmeHead[ 0x210 ];
	_STL::public_vector<_STL::Rva0025CB00Element, _STL::allocator<_STL::Rva0025CB00Element> > m_bfmeItems;
};

class Gen003B1850
{
public:
	void bfmeAppend( const _STL::Rva003B0060Element *value );

private:
	char m_bfmeHead[ 0x08 ];
	_STL::public_vector<_STL::Rva003B0060Element, _STL::allocator<_STL::Rva003B0060Element> > m_bfmeItems;
};

class Gen0060CF90
{
public:
	void bfmeAppend( const _STL::Rva001E9020Element *value );

private:
	char m_bfmeHead[ 0x3C ];
	_STL::public_vector<_STL::Rva001E9020Element, _STL::allocator<_STL::Rva001E9020Element> > m_bfmeItems;
};

// ?bfmeAppend@Gen00365520@@QAEXPBUP6Elem00365520@@@Z		63B
void Gen00365520::bfmeAppend( const P6Elem00365520 *value )
{
	_STL::public_vector<P6Elem00365520, _STL::allocator<P6Elem00365520> > &items = m_bfmeItems;

	if ( items._M_finish != items._M_end_of_storage )
	{
		Bfme00365520Construct( items._M_finish, *value );
		++items._M_finish;
	}
	else
	{
		items._M_insert_overflow( items._M_finish, *value,
			reinterpret_cast<const _STL::__false_type &>( value ), 1, true );
	}
}

// ?bfmeAppend@Gen003AC1C0@@QAEXPBUP6Elem003AC1C0@@@Z		63B
void Gen003AC1C0::bfmeAppend( const P6Elem003AC1C0 *value )
{
	_STL::public_vector<P6Elem003AC1C0, _STL::allocator<P6Elem003AC1C0> > &items = m_bfmeItems;

	if ( items._M_finish != items._M_end_of_storage )
	{
		Bfme003AC1C0Construct( items._M_finish, *value );
		++items._M_finish;
	}
	else
	{
		items._M_insert_overflow( items._M_finish, *value,
			reinterpret_cast<const _STL::__false_type &>( value ), 1, true );
	}
}

// ?bfmeAppend@Gen003B18A0@@QAEXPBUP6Elem003B18A0@@@Z		61B
void Gen003B18A0::bfmeAppend( const P6Elem003B18A0 *value )
{
	_STL::public_vector<P6Elem003B18A0, _STL::allocator<P6Elem003B18A0> > &items = m_bfmeItems;

	if ( items._M_finish != items._M_end_of_storage )
	{
		Bfme003B18A0Construct( items._M_finish, *value );
		++items._M_finish;
	}
	else
	{
		items._M_insert_overflow( items._M_finish, *value,
			reinterpret_cast<const _STL::__false_type &>( value ), 1, true );
	}
}

// ?bfmeAppend@Gen003B18F0@@QAEXPBUP6Elem003B18F0@@@Z		61B
void Gen003B18F0::bfmeAppend( const P6Elem003B18F0 *value )
{
	_STL::public_vector<P6Elem003B18F0, _STL::allocator<P6Elem003B18F0> > &items = m_bfmeItems;

	if ( items._M_finish != items._M_end_of_storage )
	{
		Bfme003B18F0Construct( items._M_finish, *value );
		++items._M_finish;
	}
	else
	{
		items._M_insert_overflow( items._M_finish, *value,
			reinterpret_cast<const _STL::__false_type &>( value ), 1, true );
	}
}

// ?bfmeAppend@Gen003B1940@@QAEXPBUP6Elem003B1940@@@Z		61B
void Gen003B1940::bfmeAppend( const P6Elem003B1940 *value )
{
	_STL::public_vector<P6Elem003B1940, _STL::allocator<P6Elem003B1940> > &items = m_bfmeItems;

	if ( items._M_finish != items._M_end_of_storage )
	{
		Bfme003B1940Construct( items._M_finish, *value );
		++items._M_finish;
	}
	else
	{
		items._M_insert_overflow( items._M_finish, *value,
			reinterpret_cast<const _STL::__false_type &>( value ), 1, true );
	}
}

// ?bfmeAppend@Gen003B1990@@QAEXPBUP6Elem003B1990@@@Z		61B
void Gen003B1990::bfmeAppend( const P6Elem003B1990 *value )
{
	_STL::public_vector<P6Elem003B1990, _STL::allocator<P6Elem003B1990> > &items = m_bfmeItems;

	if ( items._M_finish != items._M_end_of_storage )
	{
		Bfme003B1990Construct( items._M_finish, *value );
		++items._M_finish;
	}
	else
	{
		items._M_insert_overflow( items._M_finish, *value,
			reinterpret_cast<const _STL::__false_type &>( value ), 1, true );
	}
}

// ?bfmeAppend@Gen003B19E0@@QAEXPBUP6Elem003B19E0@@@Z		61B
void Gen003B19E0::bfmeAppend( const P6Elem003B19E0 *value )
{
	_STL::public_vector<P6Elem003B19E0, _STL::allocator<P6Elem003B19E0> > &items = m_bfmeItems;

	if ( items._M_finish != items._M_end_of_storage )
	{
		Bfme003B19E0Construct( items._M_finish, *value );
		++items._M_finish;
	}
	else
	{
		items._M_insert_overflow( items._M_finish, *value,
			reinterpret_cast<const _STL::__false_type &>( value ), 1, true );
	}
}

// ?bfmeAppend@Gen003B1A30@@QAEXPBUP6Elem003B1A30@@@Z		61B
void Gen003B1A30::bfmeAppend( const P6Elem003B1A30 *value )
{
	_STL::public_vector<P6Elem003B1A30, _STL::allocator<P6Elem003B1A30> > &items = m_bfmeItems;

	if ( items._M_finish != items._M_end_of_storage )
	{
		Bfme003B1A30Construct( items._M_finish, *value );
		++items._M_finish;
	}
	else
	{
		items._M_insert_overflow( items._M_finish, *value,
			reinterpret_cast<const _STL::__false_type &>( value ), 1, true );
	}
}

// ?bfmeAppend@Gen003B1A80@@QAEXPBUP6Elem003B1A80@@@Z		67B
void Gen003B1A80::bfmeAppend( const P6Elem003B1A80 *value )
{
	_STL::public_vector<P6Elem003B1A80, _STL::allocator<P6Elem003B1A80> > &items = m_bfmeItems;

	if ( items._M_finish != items._M_end_of_storage )
	{
		Bfme003B1A80Construct( items._M_finish, *value );
		++items._M_finish;
	}
	else
	{
		items._M_insert_overflow( items._M_finish, *value,
			reinterpret_cast<const _STL::__false_type &>( value ), 1, true );
	}
}

// ?bfmeAppend@Gen003B1AE0@@QAEXPBUP6Elem003B1AE0@@@Z		67B
void Gen003B1AE0::bfmeAppend( const P6Elem003B1AE0 *value )
{
	_STL::public_vector<P6Elem003B1AE0, _STL::allocator<P6Elem003B1AE0> > &items = m_bfmeItems;

	if ( items._M_finish != items._M_end_of_storage )
	{
		Bfme003B1AE0Construct( items._M_finish, *value );
		++items._M_finish;
	}
	else
	{
		items._M_insert_overflow( items._M_finish, *value,
			reinterpret_cast<const _STL::__false_type &>( value ), 1, true );
	}
}

// ?bfmeAppend@Gen003B1DF0@@QAEXPBUP6Elem003B1DF0@@@Z		67B
void Gen003B1DF0::bfmeAppend( const P6Elem003B1DF0 *value )
{
	_STL::public_vector<P6Elem003B1DF0, _STL::allocator<P6Elem003B1DF0> > &items = m_bfmeItems;

	if ( items._M_finish != items._M_end_of_storage )
	{
		Bfme003B1DF0Construct( items._M_finish, *value );
		++items._M_finish;
	}
	else
	{
		items._M_insert_overflow( items._M_finish, *value,
			reinterpret_cast<const _STL::__false_type &>( value ), 1, true );
	}
}

// ?bfmeAppend@Gen003B1E50@@QAEXPBUP6Elem003B1E50@@@Z		67B
void Gen003B1E50::bfmeAppend( const P6Elem003B1E50 *value )
{
	_STL::public_vector<P6Elem003B1E50, _STL::allocator<P6Elem003B1E50> > &items = m_bfmeItems;

	if ( items._M_finish != items._M_end_of_storage )
	{
		Bfme003B1E50Construct( items._M_finish, *value );
		++items._M_finish;
	}
	else
	{
		items._M_insert_overflow( items._M_finish, *value,
			reinterpret_cast<const _STL::__false_type &>( value ), 1, true );
	}
}

// ?bfmeAppend@Gen003B2060@@QAEXPBUP6Elem003B2060@@@Z		67B
void Gen003B2060::bfmeAppend( const P6Elem003B2060 *value )
{
	_STL::public_vector<P6Elem003B2060, _STL::allocator<P6Elem003B2060> > &items = m_bfmeItems;

	if ( items._M_finish != items._M_end_of_storage )
	{
		Bfme003B2060Construct( items._M_finish, *value );
		++items._M_finish;
	}
	else
	{
		items._M_insert_overflow( items._M_finish, *value,
			reinterpret_cast<const _STL::__false_type &>( value ), 1, true );
	}
}

// ?bfmeAppend@Gen003B2890@@QAEXPBUP6Elem003B2890@@@Z		67B
void Gen003B2890::bfmeAppend( const P6Elem003B2890 *value )
{
	_STL::public_vector<P6Elem003B2890, _STL::allocator<P6Elem003B2890> > &items = m_bfmeItems;

	if ( items._M_finish != items._M_end_of_storage )
	{
		Bfme003B2890Construct( items._M_finish, *value );
		++items._M_finish;
	}
	else
	{
		items._M_insert_overflow( items._M_finish, *value,
			reinterpret_cast<const _STL::__false_type &>( value ), 1, true );
	}
}

// ?bfmeAppend@Gen003B7030@@QAEXPBUP6Elem003B7030@@@Z		61B
void Gen003B7030::bfmeAppend( const P6Elem003B7030 *value )
{
	_STL::public_vector<P6Elem003B7030, _STL::allocator<P6Elem003B7030> > &items = m_bfmeItems;

	if ( items._M_finish != items._M_end_of_storage )
	{
		Bfme003B7030Construct( items._M_finish, *value );
		++items._M_finish;
	}
	else
	{
		items._M_insert_overflow( items._M_finish, *value,
			reinterpret_cast<const _STL::__false_type &>( value ), 1, true );
	}
}

// ?bfmeAppend@Gen003C3B50@@QAEXPBUP6Elem003C3B50@@@Z		61B
void Gen003C3B50::bfmeAppend( const P6Elem003C3B50 *value )
{
	_STL::public_vector<P6Elem003C3B50, _STL::allocator<P6Elem003C3B50> > &items = m_bfmeItems;

	if ( items._M_finish != items._M_end_of_storage )
	{
		Bfme003C3B50Construct( items._M_finish, *value );
		++items._M_finish;
	}
	else
	{
		items._M_insert_overflow( items._M_finish, *value,
			reinterpret_cast<const _STL::__false_type &>( value ), 1, true );
	}
}

// ?bfmeAppend@Gen000A87D0@@QAEXPBURva000A8500Element@@@Z		61B
void Gen000A87D0::bfmeAppend( const _STL::Rva000A8500Element *value )
{
	_STL::public_vector<_STL::Rva000A8500Element, _STL::allocator<_STL::Rva000A8500Element> > &items = m_bfmeItems;

	if ( items._M_finish != items._M_end_of_storage )
	{
		_STL::_Construct( items._M_finish, *value );
		++items._M_finish;
	}
	else
	{
		items._M_insert_overflow( items._M_finish, *value,
			reinterpret_cast<const _STL::__false_type &>( value ), 1, true );
	}
}

// ?bfmeAppend@Gen0025CD50@@QAEXPBURva0025CB00Element@@@Z		67B
void Gen0025CD50::bfmeAppend( const _STL::Rva0025CB00Element *value )
{
	_STL::public_vector<_STL::Rva0025CB00Element, _STL::allocator<_STL::Rva0025CB00Element> > &items = m_bfmeItems;

	if ( items._M_finish != items._M_end_of_storage )
	{
		_STL::_Construct( items._M_finish, *value );
		++items._M_finish;
	}
	else
	{
		items._M_insert_overflow( items._M_finish, *value,
			reinterpret_cast<const _STL::__false_type &>( value ), 1, true );
	}
}

// ?bfmeAppend@Gen003B1850@@QAEXPBURva003B0060Element@@@Z		61B
void Gen003B1850::bfmeAppend( const _STL::Rva003B0060Element *value )
{
	_STL::public_vector<_STL::Rva003B0060Element, _STL::allocator<_STL::Rva003B0060Element> > &items = m_bfmeItems;

	if ( items._M_finish != items._M_end_of_storage )
	{
		_STL::_Construct( items._M_finish, *value );
		++items._M_finish;
	}
	else
	{
		items._M_insert_overflow( items._M_finish, *value,
			reinterpret_cast<const _STL::__false_type &>( value ), 1, true );
	}
}

// ?bfmeAppend@Gen0060CF90@@QAEXPBURva001E9020Element@@@Z		61B
void Gen0060CF90::bfmeAppend( const _STL::Rva001E9020Element *value )
{
	_STL::public_vector<_STL::Rva001E9020Element, _STL::allocator<_STL::Rva001E9020Element> > &items = m_bfmeItems;

	if ( items._M_finish != items._M_end_of_storage )
	{
		_STL::BfmeRva001E9020Construct( items._M_finish, *value );
		++items._M_finish;
	}
	else
	{
		items._M_insert_overflow( items._M_finish, *value,
			reinterpret_cast<const _STL::__false_type &>( value ), 1, true );
	}
}
