// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: BFMENetworkQueueItem deque growth helper at retail 0x0065BFA0.

#include <new>

void *__cdecl operator new(unsigned int size);

class BFMENetworkQueueItem
{
public:
	BFMENetworkQueueItem(const BFMENetworkQueueItem &other);
	~BFMENetworkQueueItem();

private:
	char m_body[0x210];
};

class PSPlayerStats
{
public:
	~PSPlayerStats();

private:
	char m_body[0x1e8];
};

class BFMENetworkQueueItem1
{
public:
	BFMENetworkQueueItem1(const BFMENetworkQueueItem1 &other);

private:
	int m_type;
	PSPlayerStats m_stats;
	char m_body[4];
};

namespace _STL
{
template <class T>
class allocator
{
public:
	T *allocate(unsigned int count)
	{
		return (T *)::operator new(count * sizeof(T));
	}
};

template <class T, class Allocator>
class _STLP_alloc_proxy : public Allocator
{
public:
	unsigned int _M_data;
};

template <class T>
struct _DequeIterator
{
	T *_M_cur;
	T *_M_first;
	T *_M_last;
	T **_M_node;

	void _M_set_node(T **newNode)
	{
		_M_node = newNode;
		_M_first = *newNode;
		_M_last = _M_first + buffer_size();
	}

	static unsigned int buffer_size()
	{
		return sizeof(T) < 512 ? 512 / sizeof(T) : 1;
	}
};

template <class T1, class T2>
inline void _Construct(T1 *destination, const T2 &value)
{
	new (destination) T1(value);
}

template <class T, class Allocator>
class deque
{
protected:
	void _M_push_back_aux_v(const T &value);
	void _M_reallocate_map(unsigned int nodesToAdd, bool addAtFront);

	void _M_reserve_map_at_back(unsigned int nodesToAdd)
	{
		if (nodesToAdd + 1 > _M_map_size._M_data - (unsigned int)(_M_finish._M_node - _M_map))
			_M_reallocate_map(nodesToAdd, false);
	}

	_DequeIterator<T> _M_start;
	_DequeIterator<T> _M_finish;
	T **_M_map;
	_STLP_alloc_proxy<T, Allocator> _M_map_size;
};

template <class T, class Allocator>
void deque<T, Allocator>::_M_push_back_aux_v(const T &value)
{
	T valueCopy = value;
	_M_reserve_map_at_back(1);
	*(_M_finish._M_node + 1) = _M_map_size.allocate(_DequeIterator<T>::buffer_size());
	_Construct(_M_finish._M_cur, valueCopy);
	_M_finish._M_set_node(_M_finish._M_node + 1);
	_M_finish._M_cur = _M_finish._M_first;
}

template void deque<BFMENetworkQueueItem, allocator<BFMENetworkQueueItem> >::_M_push_back_aux_v(
	const BFMENetworkQueueItem &);
template void deque<BFMENetworkQueueItem1, allocator<BFMENetworkQueueItem1> >::_M_push_back_aux_v(
	const BFMENetworkQueueItem1 &);
}
