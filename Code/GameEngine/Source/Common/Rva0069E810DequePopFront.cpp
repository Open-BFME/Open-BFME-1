// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// deque pop_front of a 4-byte refcounted handle with 0x80-byte blocks.

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *lpAddend);

namespace _STL
{
	template <bool THREADS, int INSTANCE>
	class __node_alloc
	{
	public:
		static void _M_deallocate(void *node, unsigned int bytes);
	};
}

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

// Finish iterator sits at +0x10 of the deque, so the this pointer is the
// deque object and fields are at +0x10/+0x14/+0x18/+0x1c.

class Open269E810DequeFull
{
public:
	void _M_pop_back_aux();

	char m_pad[0x10];
	ThingRef *_M_cur;
	ThingRef *_M_first;
	ThingRef *_M_last;
	ThingRef **_M_node;
};

// ?_M_pop_back_aux@Open269E810DequeFull@@QAEXXZ
void Open269E810DequeFull::_M_pop_back_aux()
{
	if (_M_first)
		_STL::__node_alloc<true, 0>::_M_deallocate(_M_first, 0x80);

	ThingRef **node = _M_node - 1;
	_M_node = node;
	ThingRef *first = *node;
	_M_first = first;
	ThingRef *last = first + 32;
	_M_last = last;
	_M_cur = last - 1;
	_M_cur->~ThingRef();
}
