// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// Open-BFME5: no-SEH MapObject deque _M_create_nodes (0x78-byte nodes).

class MapObject
{
};

namespace _STL
{
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
		*p = reinterpret_cast<MapObject **>(::operator new(0x78));
		++p;
	}
}

template void _Deque_base<MapObject *, allocator<MapObject *> >::_M_create_nodes(MapObject ***, MapObject ***);
}
