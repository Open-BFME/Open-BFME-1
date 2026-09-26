// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME: byte-identical twin of Rva003AED40CopyBackward.cpp at retail
// 0x003B3EF0. Same 16-byte refcounted-cell shape, separate instantiation.

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long *addend);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *addend);

class Rva003B3EF0Thing
{
public:
	virtual ~Rva003B3EF0Thing();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
};

class Rva003B3EF0Ptr
{
public:
	Rva003B3EF0Ptr &operator=(const Rva003B3EF0Ptr &other)
	{
		if (this != &other)
		{
			if (other.m_ptr)
				InterlockedIncrement(&other.m_ptr->m_refCount);
			if (m_ptr)
				m_ptr->Release_Ref();
			m_ptr = other.m_ptr;
		}
		return *this;
	}

private:
	Rva003B3EF0Thing *m_ptr;
};

struct Gen_t_003b4070_p128pod
{
	int m_pad0;
	int m_tag;
	Rva003B3EF0Ptr m_ptr;
	unsigned char m_flag;
	unsigned char m_pad1[3];

	Gen_t_003b4070_p128pod &operator=(const Gen_t_003b4070_p128pod &other)
	{
		m_tag = other.m_tag;
		m_ptr = other.m_ptr;
		m_flag = other.m_flag;
		return *this;
	}
};

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy_backward(InputIterator first, InputIterator last,
	OutputIterator result, const random_access_iterator_tag &, Distance *)
{
	for (Distance count = last - first; count > 0; --count, ++first, ++result)
		*result = *first;
	return result;
}

template Gen_t_003b4070_p128pod *__copy_backward<Gen_t_003b4070_p128pod *, Gen_t_003b4070_p128pod *, int>(
	Gen_t_003b4070_p128pod *, Gen_t_003b4070_p128pod *, Gen_t_003b4070_p128pod *,
	const random_access_iterator_tag &, int *);
}
