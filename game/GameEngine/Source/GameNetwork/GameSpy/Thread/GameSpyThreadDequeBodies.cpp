// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// The four STLport deque bodies the GameSpy peer and persistent-storage
// threads instantiate, written against the hand model of the container rather
// than the real header:
//
//   deque<PeerResponse>::pop_front           0x00648760   80 B   public   QAE
//   deque<PeerResponse>::_M_pop_front_aux    0x00647A80   55 B   protected IAE
//   deque<PeerResponse>::_M_push_back_aux_v  0x00648920  214 B   protected IAE
//   deque<PSRequest>::_M_pop_front_aux       0x00655190   55 B   protected IAE
//
// The access specifiers are load-bearing -- QAE and IAE are in the mangled
// names -- so pop_front stays public and the two aux bodies stay protected.
//
// Split one body per file, three of the four files carried their own cut-down
// deque: a bare four-pointer class that was really just the _M_start iterator,
// with `last = first + 1` written out as a literal because nothing in that file
// said where the 1 came from. It is buffer_size(): STLport gives an element of
// 512 bytes or more a one-element block, and both elements here qualify
// (PeerResponse 0x330, PSRequest 0x210). Declared once against the real shape,
// the same four bodies compile from the model that shows why.
//
// pop_front still spells out the tail that _M_pop_front_aux also holds. That
// duplication is retail's: its pop_front inlines the aux body rather than
// calling it, which is what makes it 80 bytes.

#include <new>

void *__cdecl operator new(unsigned int size);
void __cdecl operator delete( void *memory );

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerThread.h
// The full field-by-field reconstruction is in PeerResponseCopies.cpp; here
// only the stride and the two out-of-line calls matter, so the body stays
// opaque -- spelling out the std::string members would make the destructor
// these bodies call inline, which is not what retail emitted.
class PeerResponse
{
public:
	PeerResponse(const PeerResponse &other);		// ILT 0x0001E74F
	~PeerResponse();					// ILT 0x00044733

private:
	unsigned char m_unreconstructed[0x330];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PersistentStorageThread.h
class PSRequest
{
public:
	~PSRequest();

private:
	char m_data[0x210];
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
public:
	void pop_front();

protected:
	void _M_pop_front_aux();
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
void deque<T, Allocator>::pop_front()
{
	if (_M_start._M_cur != _M_start._M_last - 1)
	{
		_M_start._M_cur->~T();
		++_M_start._M_cur;
		return;
	}

	_M_start._M_cur->~T();
	if (_M_start._M_first != 0)
		::operator delete( _M_start._M_first );
	_M_start._M_set_node(_M_start._M_node + 1);
	_M_start._M_cur = _M_start._M_first;
}

template <class T, class Allocator>
void deque<T, Allocator>::_M_pop_front_aux()
{
	_M_start._M_cur->~T();
	if (_M_start._M_first != 0)
		::operator delete( _M_start._M_first );
	_M_start._M_set_node(_M_start._M_node + 1);
	_M_start._M_cur = _M_start._M_first;
}

// Near-twin of deque<BFMENetworkQueueItem>::_M_push_back_aux_v at 0x0065BFA0
// (game/GameEngine/Source/GameNetwork/BFMENetworkQueueDequePushBackAux.cpp):
// same STLport growth body. The destructor call goes through the ILT at
// 0x00044733 to the byte-identical ??1PeerResponse@@QAE@XZ body at 0x004DAC70;
// the copy ctor call goes through the ILT at 0x0001E74F to the still-dumped
// body at 0x004FB2E0; the map-reserve call goes through the ILT at 0x000040A2
// to the shared _M_reallocate_map body at 0x00645C10.
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

template void deque<PeerResponse, allocator<PeerResponse> >::pop_front();
template void deque<PeerResponse, allocator<PeerResponse> >::_M_pop_front_aux();
template void deque<PeerResponse, allocator<PeerResponse> >::_M_push_back_aux_v(
	const PeerResponse &);
template void deque<PSRequest, allocator<PSRequest> >::_M_pop_front_aux();

}
