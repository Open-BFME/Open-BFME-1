// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME: out-of-line STLport copy-backward helper at retail 0x003AED40.
// 16-byte element: an untouched leading dword, a plain int tag at +4, a
// refcounted pointer at +8 (AddRef/Release_Ref via KERNEL32 Interlocked*),
// and a trailing flag byte at +0xc.

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long *addend);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *addend);

class Rva003AED40Thing
{
public:
	virtual ~Rva003AED40Thing();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
};

class Rva003AED40Ptr
{
public:
	Rva003AED40Ptr &operator=(const Rva003AED40Ptr &other)
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
	Rva003AED40Thing *m_ptr;
};

struct Gen_t_003af640_p128pod
{
	int m_pad0;
	int m_tag;
	Rva003AED40Ptr m_ptr;
	unsigned char m_flag;
	unsigned char m_pad1[3];

	Gen_t_003af640_p128pod &operator=(const Gen_t_003af640_p128pod &other)
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

template Gen_t_003af640_p128pod *__copy_backward<Gen_t_003af640_p128pod *, Gen_t_003af640_p128pod *, int>(
	Gen_t_003af640_p128pod *, Gen_t_003af640_p128pod *, Gen_t_003af640_p128pod *,
	const random_access_iterator_tag &, int *);
}
