// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Retail 0x0013BB90 copies a 0x128-byte STLport vector element. The retail
// call through ILT 0x0001A668 reaches the pinned pair copy constructor at
// 0x00772390, while ILT 0x00024FB9 reaches the matched vector base constructor
// at 0x0013B110.

#include <new>

struct Gen_t_0013a700_k4
{
	int a[1];
};

struct Gen_t_0013a700_p12cd
{
	char body[292];
};

namespace _STL
{
	template <typename T> class allocator
	{
		int m_value;
	};

	template <typename T1, typename T2> struct pair
	{
		T1 first;
		T2 second;
		pair(const pair &other);
	};

	template <typename T, typename Alloc> struct _Vector_base
	{
		_Vector_base(unsigned count, const Alloc &alloc);
		~_Vector_base();
		T *m_start;
		T *m_finish;
		T *m_storage;
	};

	template <typename T, typename Alloc = allocator<T> > class vector;

	typedef pair<const Gen_t_0013a700_k4, Gen_t_0013a700_p12cd>
		Rva0013BB90Element;

	template <> class vector<Rva0013BB90Element,
		allocator<Rva0013BB90Element> >
		: public _Vector_base<Rva0013BB90Element,
			allocator<Rva0013BB90Element> >
	{
	public:
		typedef Rva0013BB90Element T;
		typedef _Vector_base<T, allocator<T> > Base;
		typedef allocator<T> allocator_type;

		allocator_type get_allocator() const;
		vector(const vector &other);
	};

	vector<Rva0013BB90Element, allocator<Rva0013BB90Element> >::vector(
		const vector<Rva0013BB90Element,
			allocator<Rva0013BB90Element> > &other)
		: Base((unsigned)(other.m_finish - other.m_start),
			other.get_allocator())
	{
		T *end = other.m_finish;
		T *source = other.m_start;
		T *destination = m_start;
		while (source != end)
		{
			new (destination) T(*source);
			source++;
			destination++;
		}
		m_finish = destination;
	}
}
