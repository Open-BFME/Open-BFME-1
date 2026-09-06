// ?d_00136840@@YAXXZ
// partial score=0.94 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Open-BFME5: near-twin of ??0?$vector@UGen_003A8BE0@@V?$allocator@UGen_003A8 @
// (retail 0x003AB280, BfmeVectorCopy003AB280.cpp) at retail 0x00136840, 192
// bytes. Same STLport vector<T> copy constructor shape (_Vector_base(count,
// alloc) then a manual uninitialized-copy loop calling each element's own
// copy constructor), but this element is 12 bytes: two direct ints followed
// by a 4-byte AsciiString/StringBase<char>-shaped string subobject at +8
// (copy ctor call to retail 0x00887B60, the shared StringBase<char> copy
// ctor -- ledger pins it under many aliases, dis_retail.py prints one of the
// generic ones, ??0GameSpyGroupRoom@@QAE@ABV0@@Z, which is not the real
// owning type here). Real element/vector name unproven; landed
// address-derived.

#include <new>

class BfmeStringBaseChar;

template <class T>
class StringBase
{
public:
	StringBase(const StringBase<T> &other);			// retail 0x00887B60
	~StringBase(void);

	private:
	T *m_bfmeData;
};

struct Rva00136840Element
{
	int m_bfmeA;
	int m_bfmeB;
	StringBase<char> m_bfmeName;
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

	template <> class vector<Rva00136840Element, allocator<Rva00136840Element> >
		: public _Vector_base<Rva00136840Element, allocator<Rva00136840Element> >
	{
	public:
		typedef Rva00136840Element T;
		typedef _Vector_base<Rva00136840Element, allocator<Rva00136840Element> > Base;
		typedef allocator<Rva00136840Element> allocator_type;

		allocator_type get_allocator() const;
		vector(const vector &other);
	};

	vector<Rva00136840Element, allocator<Rva00136840Element> >::vector(
		const vector<Rva00136840Element, allocator<Rva00136840Element> > &other)
		: Base((unsigned)(other.m_finish - other.m_start), other.get_allocator())
	{
		typedef Rva00136840Element T;
		T *end = other.m_finish;
		T *source = other.m_start;
		T *destination = m_start;
		while (source != end)
		{
			new (destination) T(*source);
			destination++;
			source++;
		}
		m_finish = destination;
	}
}
