// cl: /DNDEBUG /MD /EHsc

// The exact push_back caller at 0x008FBC70 proves this is its 8-byte payload's
// auxiliary path.  A distinct address-scoped payload avoids colliding with the
// generator's non-POD approximation of the same caller.
struct Gen_t_008fb570_p8pod
{
	int value[2];
};

namespace _STL
{
void *vectorSmallAllocate(unsigned int bytes);

template <class Destination, class Source>
void _Construct(Destination *, const Source &);

template <class Type>
class allocator
{
};

template <class Type>
struct DequeIterator
{
	Type *current;
	Type *first;
	Type *last;
	Type **node;
};

template <class Type>
static __forceinline void setDequeNode(DequeIterator<Type> &iterator, Type **newNode)
{
	iterator.node = newNode;
	iterator.first = *newNode;
	iterator.last = iterator.first + 16;
}

template <class Type, class Allocator>
class deque
{
protected:
	void _M_push_back_aux_v(const Type &value);
	void _M_reallocate_map(unsigned int nodesToAdd, bool addAtFront);

	DequeIterator<Type> start;
	DequeIterator<Type> finish;
	Type **map;
	unsigned int mapSize;
};

template <class Type, class Allocator>
void deque<Type, Allocator>::_M_push_back_aux_v(const Type &value)
{
	Type copy = value;
	if (2 > mapSize - (unsigned int)(finish.node - map))
		_M_reallocate_map(1, false);

	*(finish.node + 1) = (Type *)vectorSmallAllocate(0x80);
	_Construct(finish.current, copy);
	setDequeNode(finish, finish.node + 1);
	finish.current = finish.first;
}

template void deque<Gen_t_008fb570_p8pod, allocator<Gen_t_008fb570_p8pod> >::_M_push_back_aux_v(
	const Gen_t_008fb570_p8pod &);
}
