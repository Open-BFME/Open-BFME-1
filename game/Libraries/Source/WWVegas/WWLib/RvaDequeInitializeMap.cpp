// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport _Deque_base<T>::_M_initialize_map, 9 bodies.  Every one
// carried only a machine byte-dump row, and every one is the callee of a queue
// constructor converted in RvaQueueDefaultCtor.cpp -- that call is what found
// these addresses and what named their element types.
//
// The map is the deque's vector of node pointers.  _M_initialize_map sizes it
// to the number of nodes the requested element count needs plus two, floors
// that at STLport's initial eight, allocates it, centres the used run inside
// it, and buys one node per slot in that run.
//
// The element width is not hidden here the way it is in the constructor: the
// first thing the body does is divide the element count by the buffer size,
// and STLport's buffer size is 128 bytes of node divided by the element.  A
// `shr 5` is therefore a four-byte element, `shr 3` a 16-byte one and `shr 2`
// a 32-byte one -- and the last of
// those is eight bytes shorter overall because four nodes' worth of pointer
// arithmetic folds differently.
//
// This TU is built WITHOUT exceptions.  Retail has no unwind frame around the
// node loop, and with /EHsc STLport wraps it in a try and the body comes out
// 278 bytes rather than 203.  The queue constructors in RvaQueueDefaultCtor.cpp
// keep their own flags; the two files declare the same element types.

#define _STLP_NO_EXCEPTIONS 1
#include <deque>
#include <new>

struct Rva00089CA0Element
{
	char m_body[ 4 ];
};

// retail 0x00089190, reached from the queue constructor at 0x00089CA0
void BfmeDequeInitAnchor00089CA0( void *place )
{
	new ( place ) _STL::deque<Rva00089CA0Element>();
}

struct Rva0035A900Element
{
	char m_body[ 4 ];
};

// retail 0x003546E0, reached from the queue constructor at 0x0035A900
void BfmeDequeInitAnchor0035A900( void *place )
{
	new ( place ) _STL::deque<Rva0035A900Element>();
}

struct Rva0035A940Element
{
	char m_body[ 4 ];
};

// retail 0x00354890, reached from the queue constructor at 0x0035A940
void BfmeDequeInitAnchor0035A940( void *place )
{
	new ( place ) _STL::deque<Rva0035A940Element>();
}

struct Rva0035AF40Element
{
	char m_body[ 4 ];
};

// retail 0x00354D50, reached from the queue constructor at 0x0035AF40
void BfmeDequeInitAnchor0035AF40( void *place )
{
	new ( place ) _STL::deque<Rva0035AF40Element>();
}

struct Rva0035AF80Element
{
	char m_body[ 4 ];
};

// retail 0x00354F00, reached from the queue constructor at 0x0035AF80
void BfmeDequeInitAnchor0035AF80( void *place )
{
	new ( place ) _STL::deque<Rva0035AF80Element>();
}

struct Rva00369550Element
{
	char m_body[ 4 ];
};

// retail 0x003684C0, reached from the queue constructor at 0x00369550
void BfmeDequeInitAnchor00369550( void *place )
{
	new ( place ) _STL::deque<Rva00369550Element>();
}

struct Rva006420A0Element
{
	char m_body[ 16 ];
};

// retail 0x00640B50, reached from the queue constructor at 0x006420A0
void BfmeDequeInitAnchor006420A0( void *place )
{
	new ( place ) _STL::deque<Rva006420A0Element>();
}

struct Rva00647200Element
{
	char m_body[ 4 ];
};

// retail 0x00645010, reached from the queue constructor at 0x00647200
void BfmeDequeInitAnchor00647200( void *place )
{
	new ( place ) _STL::deque<Rva00647200Element>();
}

struct Rva006AADB0Element
{
	char m_body[ 4 ];
};

// retail 0x0069C140, reached from the queue constructor at 0x006AADB0
void BfmeDequeInitAnchor006AADB0( void *place )
{
	new ( place ) _STL::deque<Rva006AADB0Element>();
}

