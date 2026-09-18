// ?d_003aa980@@YAXXZ
// partial score=0.9 date=2026-09-18
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// The carved body at retail 0x003AA980 copies an STLport vector of eight-byte
// records. The record vtable is 0x010EC76C, which the landed
// Rva003B7BA0Record parser identifies, and its AsciiString copy uses the
// established GameSpyGroupRoom copy address at 0x00887B60.

#include <new>
#include "ascii_string.h"

struct Gen_t_003a75c0_p8cd
{
	virtual ~Gen_t_003a75c0_p8cd() {}
	AsciiString m_name;
};

namespace _STL
{
	template <typename T> class allocator
	{
		int m_value;
	};

	template <typename T, typename Alloc> struct _Vector_base
	{
		_Vector_base( unsigned count, const Alloc &alloc );
		~_Vector_base();
		T *m_start;
		T *m_finish;
		T *m_storage;
		unsigned size() const { return (unsigned)(m_finish - m_start); }
		T *begin() { return m_start; }
		const T *begin() const { return m_start; }
		T *end() { return m_finish; }
		const T *end() const { return m_finish; }
	};

	template <typename T, typename Alloc = allocator<T> > class vector;

	template <> class vector<Gen_t_003a75c0_p8cd,
		allocator<Gen_t_003a75c0_p8cd> >
		: public _Vector_base<Gen_t_003a75c0_p8cd,
			allocator<Gen_t_003a75c0_p8cd> >
	{
	public:
		typedef Gen_t_003a75c0_p8cd T;
		typedef _Vector_base<T, allocator<T> > Base;
		typedef allocator<T> allocator_type;

		allocator_type get_allocator() const;
		vector( const vector &other );

	};

	vector<Gen_t_003a75c0_p8cd,
		allocator<Gen_t_003a75c0_p8cd> >::vector(
		const vector<Gen_t_003a75c0_p8cd,
			allocator<Gen_t_003a75c0_p8cd> > &other)
		: Base( (unsigned)(other.m_finish - other.m_start),
			other.get_allocator() )
	{
		T *destination = begin();
		const T *end = other.m_finish;
		const T *source = other.m_start;
		while ( source != end )
		{
			new ( destination ) T( *source );
			source++;
			destination++;
		}
		m_finish = destination;
	}
}
