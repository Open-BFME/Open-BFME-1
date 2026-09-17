// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <new>

// Retail 0x00195C40 copies a vector of the 0x8C-byte records whose copy
// constructor is the matched Gen_00193D50 body at 0x00193D50. The generated
// callers at 0x001973D0, 0x001975F0, 0x00197670 and 0x001984D0 all pass their
// vector member to this body. The element type keeps the proven copy-callee
// name while its byte array preserves the record size used by this vector.

class Gen_00193D50
{
	public:
	char bytes[0x8c];
	Gen_00193D50(const Gen_00193D50 &other);
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

	template <> class vector<Gen_00193D50, allocator<Gen_00193D50> >
		: public _Vector_base<Gen_00193D50, allocator<Gen_00193D50> >
	{
	public:
		typedef Gen_00193D50 T;
		typedef _Vector_base<Gen_00193D50, allocator<Gen_00193D50> > Base;
		typedef allocator<Gen_00193D50> allocator_type;

		allocator_type get_allocator() const;
		vector(const vector &other);
	};

	vector<Gen_00193D50, allocator<Gen_00193D50> >::vector(
		const vector<Gen_00193D50, allocator<Gen_00193D50> > &other)
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
