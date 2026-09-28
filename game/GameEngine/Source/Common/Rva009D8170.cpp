// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Iinputs/vendor/stlport
// The bytes destroy the pair at node+4 then release a 0x14-byte node through
// STLport's existing __node_alloc<true, 0> entry. The owner stays address-derived.
#define _STLP_NO_EXCEPTIONS 1
#include <stl/_config.h>
#include <stl/_pair.h>

struct Gen_t_009d8230_p12cd
{
	int a[3];
	~Gen_t_009d8230_p12cd(void);
};

typedef _STL::pair<const int, Gen_t_009d8230_p12cd> Rva009D8170Pair;

struct Rva009D8170Node
{
	Rva009D8170Node *next;
	Rva009D8170Pair pair;
};

class Rva009D8170NodeAllocator;

namespace _STL
{
template <bool threads, int instance>
class __node_alloc
{
	static void _M_deallocate(void *memory, unsigned int bytes);
	friend class ::Rva009D8170NodeAllocator;
};
}

class Rva009D8170NodeAllocator
{
public:
	static void deallocate(void *memory, unsigned int bytes)
	{
		_STL::__node_alloc<true, 0>::_M_deallocate(memory, bytes);
	}
};

class Rva009D8170Owner
{
public:
	void m009D8170(Rva009D8170Node *node);
};

void Rva009D8170Owner::m009D8170(Rva009D8170Node *node)
{
	node->pair.~Rva009D8170Pair();
	if (node)
		Rva009D8170NodeAllocator::deallocate(node, 0x14);
}
