// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// Open-BFME5: no-SEH MapObject deque _M_create_nodes (0x78-byte nodes).

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MapObject.h
class MapObject
{
};

namespace _STL
{
// Retail takes this node from STLport's node pool, not ::operator new: the
// call at this site is __node_alloc<true,0>::_M_allocate (0x0082E540), which
// buckets by (n-1)>>3 into the free-list array at 0x0130B1C0.  Shape copied
// from inputs/vendor/stlport/stl/_alloc.h, including the ternary in allocate() --
// every node size here is a compile-time constant under _MAX_BYTES, so it
// folds and leaves retail's single direct call.
template <bool __threads, int __inst>
class __node_alloc
{
	enum { _MAX_BYTES = 128 };
	static void *__cdecl _M_allocate(unsigned int __n);

public:
	static void *__cdecl allocate(unsigned int __n)
	{ return (__n > (unsigned int)_MAX_BYTES) ? ::operator new(__n) : _M_allocate(__n); }
};

typedef __node_alloc<true, 0> _Node_alloc;

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class _Deque_base
{
protected:
	void _M_create_nodes(Type **, Type **);
};

// ?_M_create_nodes@?$_Deque_base@PAVMapObject@@V?$allocator@PAVMapObject@@@_STL@@@_STL@@IAEXPAPAPAVMapObject@@0@Z
void _Deque_base<MapObject *, allocator<MapObject *> >::_M_create_nodes(MapObject ***start, MapObject ***finish)
{
	MapObject ***p = start;
	while (p < finish)
	{
		*p = reinterpret_cast<MapObject **>(_Node_alloc::allocate(0x78));
		++p;
	}
}

template void _Deque_base<MapObject *, allocator<MapObject *> >::_M_create_nodes(MapObject ***, MapObject ***);
}
