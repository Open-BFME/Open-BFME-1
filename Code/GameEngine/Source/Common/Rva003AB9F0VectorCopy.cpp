// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <new>

class Rva003BABE0Record
{
public:
	Rva003BABE0Record(const Rva003BABE0Record &other);
	virtual ~Rva003BABE0Record();
	char m_body[0x20];
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

	template <> class vector<Rva003BABE0Record,
		allocator<Rva003BABE0Record> >
		: public _Vector_base<Rva003BABE0Record,
			allocator<Rva003BABE0Record> >
	{
	public:
		typedef Rva003BABE0Record T;
		typedef _Vector_base<T, allocator<T> > Base;
		typedef allocator<T> allocator_type;

		allocator_type get_allocator() const;
		vector(const vector &other);
	};

	vector<Rva003BABE0Record, allocator<Rva003BABE0Record> >::vector(
		const vector<Rva003BABE0Record,
			allocator<Rva003BABE0Record> > &other)
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
