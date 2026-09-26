// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// _STL::__destroy_aux over deque iterators of 4-byte refcounted handles.
// Block width is 0x80 bytes (32 elements), read from the retail lea.

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *lpAddend);

class RefCountedThing
{
public:
	virtual ~RefCountedThing();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
};

class ThingRef
{
public:
	~ThingRef()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

private:
	RefCountedThing *m_ptr;
};

namespace _STL
{

struct __false_type
{
};

struct _Deque_iterator
{
	ThingRef *_M_cur;
	ThingRef *_M_first;
	ThingRef *_M_last;
	ThingRef **_M_node;

	void operator++()
	{
		++_M_cur;
		if (_M_cur == _M_last)
		{
			++_M_node;
			_M_first = *_M_node;
			_M_last = _M_first + 32;
			_M_cur = _M_first;
		}
	}
};

inline bool operator==(_Deque_iterator a, _Deque_iterator b)
{
	return a._M_cur == b._M_cur;
}

inline bool operator!=(_Deque_iterator a, _Deque_iterator b)
{
	return a._M_cur != b._M_cur;
}

void __destroy_aux(_Deque_iterator first, _Deque_iterator last,
	const __false_type &)
{
	for (; first != last; ++first)
		first._M_cur->~ThingRef();
}

}
