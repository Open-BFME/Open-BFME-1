// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Retail 0x0013BC80 is the STLport copy constructor for the proven
// Rva0077CC10Element type. Its 0xbc stride calls the pinned element copy
// constructor at 0x00013FB1 and its base setup calls the adjacent vector
// constructor at 0x0013B200.

#include <new>

struct Rva0077CC10Element
{
	Rva0077CC10Element(const Rva0077CC10Element &other);
	char m_body[188];
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

	template <> class vector<Rva0077CC10Element,
		allocator<Rva0077CC10Element> >
		: public _Vector_base<Rva0077CC10Element,
			allocator<Rva0077CC10Element> >
	{
	public:
		typedef Rva0077CC10Element T;
		typedef _Vector_base<T, allocator<T> > Base;
		typedef allocator<T> allocator_type;

		allocator_type get_allocator() const;
		vector(const vector &other);
	};

	vector<Rva0077CC10Element, allocator<Rva0077CC10Element> >::vector(
		const vector<Rva0077CC10Element,
			allocator<Rva0077CC10Element> > &other)
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
