// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <new>

// Retail 0x003AB860 is the STLport vector copy constructor for a second 12-byte record type whose copy constructor is the thunk at 0x000112BB; byte-twin of BfmeVectorCopy003AB280.cpp (tools/twin_scan.py). The original
// three-string record copy at 0x003A8BE0 is the twin.

struct Gen_003AB860Elem
{
	void *m_first;
	void *m_second;
	void *m_third;
	Gen_003AB860Elem(const Gen_003AB860Elem &other);
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

	template <> class vector<Gen_003AB860Elem, allocator<Gen_003AB860Elem> >
		: public _Vector_base<Gen_003AB860Elem, allocator<Gen_003AB860Elem> >
	{
	public:
		typedef Gen_003AB860Elem T;
		typedef _Vector_base<Gen_003AB860Elem, allocator<Gen_003AB860Elem> > Base;
		typedef allocator<Gen_003AB860Elem> allocator_type;

		allocator_type get_allocator() const;
		vector(const vector &other);
	};

	vector<Gen_003AB860Elem, allocator<Gen_003AB860Elem> >::vector(
		const vector<Gen_003AB860Elem, allocator<Gen_003AB860Elem> > &other)
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
