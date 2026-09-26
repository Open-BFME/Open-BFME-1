// STLport deque<ThingRef>::pop_front at retail RVA 0x006A0530.

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

extern "C" ThingRef *__fastcall Rva0069E880DequeAdvance(void *self);

namespace _STL
{
	template <class T>
	class allocator
	{
	};

	template <class T>
	struct _Deque_iterator
	{
		T *_M_cur;
		T *_M_first;
		T *_M_last;
		T **_M_node;
	};

	template <class T, class Allocator>
	class deque
	{
	public:
		void pop_front();

		_Deque_iterator<T> _M_start;
		_Deque_iterator<T> _M_finish;
		T **_M_map;
		unsigned int _M_map_size;
	};

	template <class T, class Allocator>
	void deque<T, Allocator>::pop_front()
	{
		if (_M_start._M_cur != _M_start._M_last - 1)
		{
			_M_start._M_cur->~T();
			++_M_start._M_cur;
		}
		else
		{
			Rva0069E880DequeAdvance(this);
		}
	}

	template void deque<ThingRef, allocator<ThingRef> >::pop_front();
}
