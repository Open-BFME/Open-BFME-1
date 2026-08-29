// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Six vector operations over a twenty-byte element, landed as
// relocation-blind twins of the two bodies
// Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp already owns
// (0x00771F60 and 0x00779E00).  Four are the assignment operator and two are
// the two-iterator erase; each differs from its model only in which
// instantiations of _M_allocate_and_copy, _M_clear, __copy,
// __uninitialized_copy and the element destructor it reaches.
//
// The element's SIZE is what the bytes fix: the erase walks its destructor
// loop with `add esi,0x14`, so the element is twenty bytes, and it has both a
// non-trivial copy and a destructor.  Nothing here says what it is, so each
// instantiation is named after the body's address.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

class Open2Elem138090
{
public:
	Open2Elem138090( const Open2Elem138090 &other );
	~Open2Elem138090();

private:
	char m_storage[ 20 ];
};


class Open2Elem3B5860
{
public:
	Open2Elem3B5860( const Open2Elem3B5860 &other );
	~Open2Elem3B5860();

private:
	char m_storage[ 20 ];
};


class Open2Elem3B59D0
{
public:
	Open2Elem3B59D0( const Open2Elem3B59D0 &other );
	~Open2Elem3B59D0();

private:
	char m_storage[ 20 ];
};


class Open2Elem771DF0
{
public:
	Open2Elem771DF0( const Open2Elem771DF0 &other );
	~Open2Elem771DF0();

private:
	char m_storage[ 20 ];
};


class Open2Elem2EB190
{
public:
	Open2Elem2EB190( const Open2Elem2EB190 &other );
	~Open2Elem2EB190();

private:
	char m_storage[ 20 ];
};


class Open2Elem7716A0
{
public:
	Open2Elem7716A0( const Open2Elem7716A0 &other );
	~Open2Elem7716A0();

private:
	char m_storage[ 20 ];
};

void Open2AssignAnchor138090( _STL::vector<Open2Elem138090> &target,
	const _STL::vector<Open2Elem138090> &source )
{
	target = source;
}

void Open2AssignAnchor3B5860( _STL::vector<Open2Elem3B5860> &target,
	const _STL::vector<Open2Elem3B5860> &source )
{
	target = source;
}

void Open2AssignAnchor3B59D0( _STL::vector<Open2Elem3B59D0> &target,
	const _STL::vector<Open2Elem3B59D0> &source )
{
	target = source;
}

void Open2AssignAnchor771DF0( _STL::vector<Open2Elem771DF0> &target,
	const _STL::vector<Open2Elem771DF0> &source )
{
	target = source;
}

void Open2EraseAnchor2EB190( _STL::vector<Open2Elem2EB190> &target,
	Open2Elem2EB190 *first, Open2Elem2EB190 *last )
{
	target.erase( first, last );
}

void Open2EraseAnchor7716A0( _STL::vector<Open2Elem7716A0> &target,
	Open2Elem7716A0 *first, Open2Elem7716A0 *last )
{
	target.erase( first, last );
}
