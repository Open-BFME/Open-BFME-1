// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME7: out-of-line STLport copy-backward helper at retail 0x003B5EA0.
// 36-byte element: offset0 untouched, UnicodeString at +4 (StringBase set,
// 0x00887C90), an opaque 4-byte handle at +8 assigned via an unnamed thunk
// (0x00407A63), two untouched dwords at +0xc/+0x10, three ints at
// +0x14/+0x18/+0x1c, three bytes at +0x20/+0x21/+0x22, then padding to 0x24.

class UnicodeString
{
	void *m_data;
public:
	void set(const UnicodeString &);
};

extern "C" void j_00007a63();

class Rva003B5EA0Handle
{
	void *m_data;
public:
	void assign(const Rva003B5EA0Handle &other)
	{
		typedef void (Rva003B5EA0Handle::*Fn)(const Rva003B5EA0Handle &);
		union { void (*raw)(); Fn member; } fn;
		fn.raw = j_00007a63;
		(this->*fn.member)(other);
	}
};

struct Gen_t_003b60a0_p128pod
{
	int m_pad0;
	UnicodeString m_str;
	Rva003B5EA0Handle m_handle;
	int m_padc;
	int m_pad10;
	int m_a;
	int m_b;
	int m_c;
	unsigned char m_f0;
	unsigned char m_f1;
	unsigned char m_f2;
	unsigned char m_pad23;

	Gen_t_003b60a0_p128pod &operator=(const Gen_t_003b60a0_p128pod &other)
	{
		m_str.set(other.m_str);
		m_handle.assign(other.m_handle);
		m_a = other.m_a;
		m_b = other.m_b;
		m_c = other.m_c;
		m_f0 = other.m_f0;
		m_f1 = other.m_f1;
		m_f2 = other.m_f2;
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

template Gen_t_003b60a0_p128pod *__copy_backward<Gen_t_003b60a0_p128pod *, Gen_t_003b60a0_p128pod *, int>(
	Gen_t_003b60a0_p128pod *, Gen_t_003b60a0_p128pod *, Gen_t_003b60a0_p128pod *,
	const random_access_iterator_tag &, int *);
}
