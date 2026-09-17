// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// STLport deque<ThingRef>::_M_push_back_aux_v at retail RVA 0x006A7DF0.
// Gen_006AB0B0 and Gen_006AC5D0 both call the shared ILT at 0x0000B61D.

#include <new>

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *lpAddend);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *lpAddend);

void *__cdecl operator new(unsigned int size);

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
	ThingRef(const ThingRef &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			InterlockedIncrement(&m_ptr->m_refCount);
	}

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
	template <bool threads, int instance>
	class __node_alloc
	{
	private:
		enum { _MAX_BYTES = 128 };
		static void *__cdecl _M_allocate(unsigned int bytes);

	public:
		static void *__cdecl allocate(unsigned int bytes)
		{
			return bytes > (unsigned int)_MAX_BYTES ?
				::operator new(bytes) : _M_allocate(bytes);
		}
	};

	template <class T>
	class allocator
	{
	public:
		T *allocate(unsigned int count)
		{
			return (T *)__node_alloc<true, 0>::allocate(count * sizeof(T));
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
			return sizeof(T) < 128 ? 128 / sizeof(T) : 1;
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
			if (nodesToAdd + 1 > _M_map_size._M_data -
				(unsigned int)(_M_finish._M_node - _M_map))
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
		*(_M_finish._M_node + 1) =
			_M_map_size.allocate(_DequeIterator<T>::buffer_size());
		_Construct(_M_finish._M_cur, valueCopy);
		_M_finish._M_set_node(_M_finish._M_node + 1);
		_M_finish._M_cur = _M_finish._M_first;
	}

	template void deque<ThingRef, allocator<ThingRef> >::_M_push_back_aux_v(
		const ThingRef &);
}
