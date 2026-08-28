// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::deque<BuddyResponse>::_M_push_back_aux_v, retail
// 0x0063CE30, 137 bytes. The body carried only a machine byte-dump row;
// reverse/reloc_names.csv holds the name with identity=real.
//
// BuddyResponse is 0x864 bytes -- twice and a bit its BuddyRequest sibling at
// 0x0063CD80 -- which is what the frame reserves and what the buffer
// allocation asks for. STLport's buffer_size is 512 / sizeof(T) or 1
// when the element does not fit, so the deque holds exactly one element per
// node here -- that is why the new last pointer is first plus one element and
// not first plus a count.
//
// The two rep movsd runs are the two copies STLport's source spells out: the
// by-value local the function opens with, and _Construct on the new cursor.
// The second is guarded by a null test because _Construct is placement new and
// this compiler tests the pointer operator new(size_t, void*) returns.
//
// There is no unwind frame, so this translation unit is built without
// exceptions and the try around the construct is gone.

inline void *operator new(unsigned int, void *place) { return place; }

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/BuddyThread.h
class BuddyResponse
{
	char m_bfmeBody[0x864];
};

namespace _STL
{

void *__cdecl vectorLargeAllocate(unsigned int bytes);		// retail 0x00881F30
void *__cdecl vectorSmallAllocate(unsigned int bytes);		// retail 0x0082E540

template <class T1, class T2>
inline void _Construct(T1 *p, const T2 &value)
{
	new (p) T1(value);
}

template <class T>
class allocator
{
public:
	T *allocate(unsigned int n)
	{
		T *result;
		if (n != 0)
		{
			unsigned int bytes = n * sizeof(T);
			if (bytes > 128)
				result = (T *)vectorLargeAllocate(bytes);
			else
				result = (T *)vectorSmallAllocate(bytes);
		}
		else
		{
			result = 0;
		}
		return result;
	}
};

template <class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	unsigned int _M_data;
};

template <class T>
struct _Deque_iterator
{
	void _M_set_node(T **newNode)
	{
		_M_node = newNode;
		_M_first = *newNode;
		_M_last = _M_first + _S_buffer_size();
	}

	static unsigned int _S_buffer_size(void)
	{
		return sizeof(T) < 512 ? 512 / sizeof(T) : 1;
	}

	T *_M_cur;						// +0x00
	T *_M_first;						// +0x04
	T *_M_last;						// +0x08
	T **_M_node;						// +0x0C
};

template <class T, class Alloc>
class deque
{
protected:
	void _M_push_back_aux_v(const T &t);

	void _M_reallocate_map(unsigned int nodesToAdd, bool addAtFront);	// ILT 0x00001523

	unsigned int buffer_size(void) const
	{
		return _Deque_iterator<T>::_S_buffer_size();
	}

	void _M_reserve_map_at_back(unsigned int nodesToAdd)
	{
		if (nodesToAdd + 1 > _M_map_size._M_data - (unsigned int)(_M_finish._M_node - _M_map))
			_M_reallocate_map(nodesToAdd, false);
	}

	_Deque_iterator<T> _M_start;				// +0x00
	_Deque_iterator<T> _M_finish;				// +0x10
	T **_M_map;						// +0x20
	_STLP_alloc_proxy<T, allocator<T> > _M_map_size;	// +0x24
};

// ?_M_push_back_aux_v@?$deque@VBuddyResponse@@V?$allocator@VBuddyResponse@@@_STL@@@_STL@@IAEXABVBuddyResponse@@@Z
template <class T, class Alloc>
void deque<T, Alloc>::_M_push_back_aux_v(const T &t)
{
	T tCopy = t;
	_M_reserve_map_at_back(1);
	*(_M_finish._M_node + 1) = _M_map_size.allocate(buffer_size());
	_Construct(_M_finish._M_cur, tCopy);
	_M_finish._M_set_node(_M_finish._M_node + 1);
	_M_finish._M_cur = _M_finish._M_first;
}

template void deque<BuddyResponse, allocator<BuddyResponse> >::_M_push_back_aux_v(const BuddyResponse &);

}
