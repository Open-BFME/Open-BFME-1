// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Retail 0x003AAB40 copies a vector of 0x30-byte Gen_003A87D0 records. The
// loop calls the matched element copy constructor at 0x003A87D0 and the
// retail vector base constructor through ILT 0x00021DFA.

#include <new>

class Gen_003A87D0
{
public:
	Gen_003A87D0(const Gen_003A87D0 &other);
	virtual ~Gen_003A87D0(void);

	char m_body[0x2C];
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

	template <> class vector<Gen_003A87D0, allocator<Gen_003A87D0> >
		: public _Vector_base<Gen_003A87D0, allocator<Gen_003A87D0> >
	{
	public:
		typedef Gen_003A87D0 T;
		typedef _Vector_base<T, allocator<T> > Base;
		typedef allocator<T> allocator_type;

		allocator_type get_allocator() const;
		vector(const vector &other);
	};

	vector<Gen_003A87D0, allocator<Gen_003A87D0> >::vector(
		const vector<Gen_003A87D0, allocator<Gen_003A87D0> > &other)
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
