// ?d_003aa980@@YAXXZ
// partial score=0.84 date=2026-09-20
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// The carved body at retail 0x003AA980 copies an STLport vector of eight-byte
// polymorphic records. The 8-byte element layout (vptr at +0, an AsciiString
// member at +4 whose copy ctor is the retail StringBase<char> copy
// constructor at 0x00887B60, shared/ICF'd with GameSpyGroupRoom's copy ctor)
// matches the landed Gen_t_003a9110_p8vs pattern at 0x003a8670/0x003a9110
// (Construct_003a9110.cpp). The vtable installed is 0x010EC76C.

#include <new>
#include "ascii_string.h"

// 8-byte polymorphic payload: vptr at +0, an AsciiString at +4.
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
		T *destination = m_start;
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
