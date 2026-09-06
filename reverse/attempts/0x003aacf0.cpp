// ??0?$vector@VBfmeEntVTA@@V?$allocator@VBfmeEntVTA@@@_STL@@@_STL@@QAE@ABV01@@Z
// partial score=0.95 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <new>

// Retail 0x003AACF0 is the STLport vector copy constructor for BfmeEntVTA
// (Code/GameEngine/Source/Common/BfmeConv1605.cpp: vtable
// ??_7BfmeEntVTA@@6B@,0x010EC77C, element copy ctor calling the AsciiString
// copy ctor at 0x00887B60 and copying the trailing byte), byte-twin shape of
// Code/GameEngine/Source/Common/BfmeVectorCopy003AB280.cpp.

class BfmeStrVTA
{
public:
	BfmeStrVTA(const BfmeStrVTA &other);
	~BfmeStrVTA();
	char *m_bfme00;
};

class BfmeEntVTA
{
public:
	__forceinline BfmeEntVTA(const BfmeEntVTA &other)
		: m_bfme04(other.m_bfme04), m_bfme08(other.m_bfme08)
	{
	}

	virtual void bfmeSlot0VTA();
	BfmeStrVTA m_bfme04;
	char m_bfme08;
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

	template <> class vector<BfmeEntVTA, allocator<BfmeEntVTA> >
		: public _Vector_base<BfmeEntVTA, allocator<BfmeEntVTA> >
	{
	public:
		typedef BfmeEntVTA T;
		typedef _Vector_base<BfmeEntVTA, allocator<BfmeEntVTA> > Base;
		typedef allocator<BfmeEntVTA> allocator_type;

		allocator_type get_allocator() const;
		vector(const vector &other);
	};

	vector<BfmeEntVTA, allocator<BfmeEntVTA> >::vector(
		const vector<BfmeEntVTA, allocator<BfmeEntVTA> > &other)
		: Base((unsigned)(other.m_finish - other.m_start), other.get_allocator())
	{
		T *destination = m_start;
		T *end = other.m_finish;
		T *source = other.m_start;
		while (source != end)
		{
			new (destination) T(*source);
			source++;
			destination++;
		}
		m_finish = destination;
	}
}
