// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport queue<T>::queue(), 15 bodies of 44 bytes.  Every one
// carried only a machine byte-dump row; the same shape is already converted at
// 0x00660EB0, 0x00660EF0 and 0x0065A990.
//
// A queue is one deque and nothing else, so this is the deque's default
// constructor inlined into it: forty bytes of the object zeroed a dword at a
// time -- the two iterators' four members each, the map pointer and the map
// size -- and then one call, _M_initialize_map with a count of zero, which is
// what actually buys the first node.
//
// sizeof(T) never appears.  The deque's buffer arithmetic lives in
// _M_initialize_map and in _M_allocate_node, not here, so these 44 bytes are
// the same for every element type and say nothing whatever about T -- not even
// its width.
//
// _M_initialize_map does say it, and nine of them are converted in
// RvaDequeInitializeMap.cpp: the shift it divides the element count by is
// 128/sizeof(T),
// STLport's buffer size -- 128 bytes of node divided by the element -- so a
// `shr 5` is a four-byte element and a `shr 2` a 32-byte one.  Ten elements carry the width their callee proves -- the
// tenth callee is still a dump, but its shift is just as readable.  The five
// whose _M_initialize_map is not a dump at all keep a nominal four bytes, which
// is all that is needed to instantiate the deque and all that is claimed.

#include <queue>
#include <new>

struct Rva00089CA0Element
{
	char m_body[ 4 ];
};

typedef _STL::queue<Rva00089CA0Element> Rva00089CA0Queue;

// retail 0x00089CA0
void BfmeQueueCtorAnchor00089CA0( void *place )
{
	new ( place ) Rva00089CA0Queue();
}

struct Rva0035A900Element
{
	char m_body[ 4 ];
};

typedef _STL::queue<Rva0035A900Element> Rva0035A900Queue;

// retail 0x0035A900
void BfmeQueueCtorAnchor0035A900( void *place )
{
	new ( place ) Rva0035A900Queue();
}

struct Rva0035A940Element
{
	char m_body[ 4 ];
};

typedef _STL::queue<Rva0035A940Element> Rva0035A940Queue;

// retail 0x0035A940
void BfmeQueueCtorAnchor0035A940( void *place )
{
	new ( place ) Rva0035A940Queue();
}

struct Rva0035AF40Element
{
	char m_body[ 4 ];
};

typedef _STL::queue<Rva0035AF40Element> Rva0035AF40Queue;

// retail 0x0035AF40
void BfmeQueueCtorAnchor0035AF40( void *place )
{
	new ( place ) Rva0035AF40Queue();
}

struct Rva0035AF80Element
{
	char m_body[ 4 ];
};

typedef _STL::queue<Rva0035AF80Element> Rva0035AF80Queue;

// retail 0x0035AF80
void BfmeQueueCtorAnchor0035AF80( void *place )
{
	new ( place ) Rva0035AF80Queue();
}

struct Rva00369550Element
{
	char m_body[ 4 ];
};

typedef _STL::queue<Rva00369550Element> Rva00369550Queue;

// retail 0x00369550
void BfmeQueueCtorAnchor00369550( void *place )
{
	new ( place ) Rva00369550Queue();
}

struct Rva0063DF60Element
{
	int m_body;
};

typedef _STL::queue<Rva0063DF60Element> Rva0063DF60Queue;

// retail 0x0063DF60
void BfmeQueueCtorAnchor0063DF60( void *place )
{
	new ( place ) Rva0063DF60Queue();
}

struct Rva0063DFA0Element
{
	int m_body;
};

typedef _STL::queue<Rva0063DFA0Element> Rva0063DFA0Queue;

// retail 0x0063DFA0
void BfmeQueueCtorAnchor0063DFA0( void *place )
{
	new ( place ) Rva0063DFA0Queue();
}

struct Rva00642060Element
{
	char m_body[ 32 ];
};

typedef _STL::queue<Rva00642060Element> Rva00642060Queue;

// retail 0x00642060
void BfmeQueueCtorAnchor00642060( void *place )
{
	new ( place ) Rva00642060Queue();
}

struct Rva006420A0Element
{
	char m_body[ 16 ];
};

typedef _STL::queue<Rva006420A0Element> Rva006420A0Queue;

// retail 0x006420A0
void BfmeQueueCtorAnchor006420A0( void *place )
{
	new ( place ) Rva006420A0Queue();
}

struct Rva00647200Element
{
	char m_body[ 4 ];
};

typedef _STL::queue<Rva00647200Element> Rva00647200Queue;

// retail 0x00647200
void BfmeQueueCtorAnchor00647200( void *place )
{
	new ( place ) Rva00647200Queue();
}

struct Rva0064CA60Element
{
	int m_body;
};

typedef _STL::queue<Rva0064CA60Element> Rva0064CA60Queue;

// retail 0x0064CA60
void BfmeQueueCtorAnchor0064CA60( void *place )
{
	new ( place ) Rva0064CA60Queue();
}

struct Rva0064CAF0Element
{
	int m_body;
};

typedef _STL::queue<Rva0064CAF0Element> Rva0064CAF0Queue;

// retail 0x0064CAF0
void BfmeQueueCtorAnchor0064CAF0( void *place )
{
	new ( place ) Rva0064CAF0Queue();
}

struct Rva0065A950Element
{
	int m_body;
};

typedef _STL::queue<Rva0065A950Element> Rva0065A950Queue;

// retail 0x0065A950
void BfmeQueueCtorAnchor0065A950( void *place )
{
	new ( place ) Rva0065A950Queue();
}

struct Rva006AADB0Element
{
	char m_body[ 4 ];
};

typedef _STL::queue<Rva006AADB0Element> Rva006AADB0Queue;

// retail 0x006AADB0
void BfmeQueueCtorAnchor006AADB0( void *place )
{
	new ( place ) Rva006AADB0Queue();
}

