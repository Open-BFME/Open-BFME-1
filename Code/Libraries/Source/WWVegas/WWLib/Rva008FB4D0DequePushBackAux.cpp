// cl: /DNDEBUG /MD /EHsc

// The caller at 0x008FBC30 copies five dwords inline before tail-calling the
// auxiliary path, proving a trivial 20-byte deque payload without its class name.
struct Gen_t_008fb4d0_p20pod
{
	int value[5];
};

namespace _STL
{
void *vectorSmallAllocate(unsigned int bytes);

template <class Destination, class Source>
static __forceinline void _Construct(Destination *destination, const Source &source)
{
	if (destination)
		*destination = source;
}

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
	iterator.last = iterator.first + 6;
}

template <class Type, class Allocator>
class deque
{
public:
	void push_back(const Type &value);

protected:
	void _M_push_back_aux_v(const Type &value);
	void _M_reallocate_map(unsigned int nodesToAdd, bool addAtFront);

	DequeIterator<Type> start;
	DequeIterator<Type> finish;
	Type **map;
	unsigned int mapSize;
};

template <class Type, class Allocator>
void deque<Type, Allocator>::push_back(const Type &value)
{
	if (finish.current != finish.last - 1)
	{
		_Construct(finish.current, value);
		++finish.current;
	}
	else
	{
		_M_push_back_aux_v(value);
	}
}

template <class Type, class Allocator>
void deque<Type, Allocator>::_M_push_back_aux_v(const Type &value)
{
	Type copy = value;
	if (2 > mapSize - (unsigned int)(finish.node - map))
		_M_reallocate_map(1, false);

	*(finish.node + 1) = (Type *)vectorSmallAllocate(0x78);
	_Construct(finish.current, copy);
	setDequeNode(finish, finish.node + 1);
	finish.current = finish.first;
}

template void deque<Gen_t_008fb4d0_p20pod, allocator<Gen_t_008fb4d0_p20pod> >::_M_push_back_aux_v(
	const Gen_t_008fb4d0_p20pod &);
template void deque<Gen_t_008fb4d0_p20pod, allocator<Gen_t_008fb4d0_p20pod> >::push_back(
	const Gen_t_008fb4d0_p20pod &);
}

class Rva008FBCB0P20Queue
{
public:
	void append(int value1, int value2, int value3, int marker);

private:
	int base;
	char unknown[0x34];
	int offset;
	_STL::deque<Gen_t_008fb4d0_p20pod, _STL::allocator<Gen_t_008fb4d0_p20pod> > values;
};

void Rva008FBCB0P20Queue::append(int value1, int value2, int value3, int marker)
{
	if (marker != 0 && value3 >= 0)
	{
		Gen_t_008fb4d0_p20pod value;
		value.value[1] = value1;
		value.value[2] = value2;
		value.value[3] = value3;
		value.value[4] = marker & 0xffff;
		// This producer's field order preserves the retail compiler's register schedule.
		value.value[0] = base + offset;
		values.push_back(value);
	}
}
