// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <new>

// Retail 0x003AB280 is the STLport vector copy constructor for the
// three-string record whose copy constructor is the matched body at 0x003A8BE0.

struct Gen_003A8BE0
{
	void *m_first;
	void *m_second;
	void *m_third;
	Gen_003A8BE0(const Gen_003A8BE0 &other);
};

namespace _STL
{
	template <typename T> class allocator
	{
		int m_value;
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

	template <> class vector<Gen_003A8BE0, allocator<Gen_003A8BE0> >
		: public _Vector_base<Gen_003A8BE0, allocator<Gen_003A8BE0> >
	{
	public:
		typedef Gen_003A8BE0 T;
		typedef _Vector_base<Gen_003A8BE0, allocator<Gen_003A8BE0> > Base;
		typedef allocator<Gen_003A8BE0> allocator_type;

		allocator_type get_allocator() const;
		vector(const vector &other);
	};

	vector<Gen_003A8BE0, allocator<Gen_003A8BE0> >::vector(
		const vector<Gen_003A8BE0, allocator<Gen_003A8BE0> > &other)
		: Base((unsigned)(other.m_finish - other.m_start), other.get_allocator())
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
