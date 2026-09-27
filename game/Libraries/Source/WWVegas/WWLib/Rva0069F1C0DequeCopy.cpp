// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// STLport-style __copy over deque iterators of 4-byte refcounted handles.
// Forward twin of Rva0069CC60DequeCopyBackward (0x0069CC60): same 0x80-byte
// (32-element) blocks, same retain-before-release handle assignment with a
// self-assign guard.

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *lpAddend);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *lpAddend);

class Rva0069F1C0Thing
{
public:
	virtual ~Rva0069F1C0Thing();

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

class Rva0069F1C0Ref
{
public:
	Rva0069F1C0Ref &operator=(const Rva0069F1C0Ref &other)
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
	Rva0069F1C0Thing *m_ptr;
};

struct Rva0069F1C0IteratorTag
{
};

struct Rva0069F1C0DequeIterator
{
	Rva0069F1C0Ref *_M_cur;
	Rva0069F1C0Ref *_M_first;
	Rva0069F1C0Ref *_M_last;
	Rva0069F1C0Ref **_M_node;

	void _M_set_node(Rva0069F1C0Ref **node)
	{
		_M_node = node;
		_M_first = *node;
		_M_last = _M_first + 32;
	}

	int operator-(const Rva0069F1C0DequeIterator &x) const
	{
		return 32 * (_M_node - x._M_node - 1) + (_M_cur - _M_first) +
			(x._M_last - x._M_cur);
	}

	Rva0069F1C0DequeIterator &operator++()
	{
		if (++_M_cur == _M_last)
		{
			_M_set_node(_M_node + 1);
			_M_cur = _M_first;
		}
		return *this;
	}
};

Rva0069F1C0DequeIterator rva0069F1C0DequeCopy(
	Rva0069F1C0DequeIterator first, Rva0069F1C0DequeIterator last,
	Rva0069F1C0DequeIterator result, const Rva0069F1C0IteratorTag &, int *)
{
	for (int n = last - first; n > 0; --n)
	{
		*result._M_cur = *first._M_cur;
		++first;
		++result;
	}
	return result;
}
