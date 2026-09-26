// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// STLport-style __copy_backward over deque iterators of 4-byte refcounted
// handles. Block width is 0x80 bytes (32 elements), read from the retail lea;
// the handle assignment adds a reference to the source before releasing the
// destination's old pointee. Element and owner identity are not recovered, so
// the function keeps its address.

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *lpAddend);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *lpAddend);

class Rva0069CC60Thing
{
public:
	virtual ~Rva0069CC60Thing();

	void Add_Ref(void)
	{
		InterlockedIncrement(&m_refCount);
	}

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
};

class Rva0069CC60Ref
{
public:
	Rva0069CC60Ref &operator=(const Rva0069CC60Ref &other)
	{
		if (this != &other)
		{
			if (other.m_ptr)
				other.m_ptr->Add_Ref();
			if (m_ptr)
				m_ptr->Release_Ref();
			m_ptr = other.m_ptr;
		}
		return *this;
	}

private:
	Rva0069CC60Thing *m_ptr;
};

struct Rva0069CC60IteratorTag
{
};

struct Rva0069CC60DequeIterator
{
	Rva0069CC60Ref *_M_cur;
	Rva0069CC60Ref *_M_first;
	Rva0069CC60Ref *_M_last;
	Rva0069CC60Ref **_M_node;

	void _M_set_node(Rva0069CC60Ref **node)
	{
		_M_node = node;
		_M_first = *node;
		_M_last = _M_first + 32;
	}

	int operator-(const Rva0069CC60DequeIterator &x) const
	{
		return 32 * (_M_node - x._M_node - 1) + (_M_cur - _M_first) +
			(x._M_last - x._M_cur);
	}

	Rva0069CC60DequeIterator &operator--()
	{
		if (_M_cur == _M_first)
		{
			_M_set_node(_M_node - 1);
			_M_cur = _M_last;
		}
		--_M_cur;
		return *this;
	}
};

Rva0069CC60DequeIterator rva0069CC60DequeCopyBackward(
	Rva0069CC60DequeIterator first, Rva0069CC60DequeIterator last,
	Rva0069CC60DequeIterator result, const Rva0069CC60IteratorTag &, int *)
{
	for (int n = last - first; n > 0; --n)
		*(--result)._M_cur = *(--last)._M_cur;
	return result;
}
