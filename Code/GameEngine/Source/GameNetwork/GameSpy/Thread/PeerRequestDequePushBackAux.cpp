// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: deque<PeerRequest>::_M_push_back_aux, retail 0x00648810 (214 B).
// Near-twin of deque<BFMENetworkQueueItem1>::_M_push_back_aux_v at 0x0065C0B0
// (Code/GameEngine/Source/GameNetwork/BFMENetworkQueueDequePushBackAux.cpp):
// same STLport growth body, sized for the 0x194-byte PeerRequest element
// (see Code/GameEngine/Source/GameNetwork/GameSpy/PeerRequestDequePopFront.cpp,
// which names the element from its own destructor ILT at 0x00016BD5). The
// copy ctor call goes through the ILT at 0x0003C308 to ??0PeerRequest@@QAE@ABV0@@Z.

#include <new>

void *__cdecl operator new(unsigned int size);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerThread.h
class PeerRequest
{
public:
	PeerRequest(const PeerRequest &other);	// ILT 0x0003C308
	~PeerRequest();							// ILT 0x00016BD5

private:
	char m_bfmeBody[0x194];
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

template void deque<PeerRequest, allocator<PeerRequest> >::_M_push_back_aux_v(
	const PeerRequest &);
}
