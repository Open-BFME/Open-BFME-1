// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Retail 0x003AADF0 copies a vector whose elements are the witnessed
// 0x14-byte Gen_003A8A70 records.  The vector base and allocator accessor are
// the existing 0x14-byte STLport thunks; the loop calls the independently
// matched Gen_003A8A70 copy constructor through its ILT.

#include <new>

class AsciiStringWM
{
public:
	AsciiStringWM(const AsciiStringWM &other);
	~AsciiStringWM(void);

private:
	char *m_bfmeData;
};

class BfmeStrWM : private AsciiStringWM
{
public:
	BfmeStrWM(const AsciiStringWM &other) : AsciiStringWM(other) {}
	~BfmeStrWM(void) {}
};

class Gen_003A8A70
{
public:
	Gen_003A8A70(const Gen_003A8A70 &other);
	virtual ~Gen_003A8A70(void);

	BfmeStrWM m_bfmeFirst;
	BfmeStrWM m_bfmeSecond;
	BfmeStrWM m_bfmeThird;
	bool m_bfmeFlag;
};

extern void j_000404fd();
extern void j_0003d16d();

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

	template <> class vector<Gen_003A8A70,
		allocator<Gen_003A8A70> >
		: public _Vector_base<Gen_003A8A70, allocator<Gen_003A8A70> >
	{
	public:
		typedef Gen_003A8A70 T;
		typedef _Vector_base<T, allocator<T> > Base;
		typedef allocator<T> allocator_type;

		allocator_type get_allocator() const;
		vector(const vector &other);
	};

	vector<Gen_003A8A70, allocator<Gen_003A8A70> >::vector(
		const vector<Gen_003A8A70,
			allocator<Gen_003A8A70> > &other)
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

#pragma comment(linker, "/alternatename:??0?$_Vector_base@VGen_003A8A70@@V?$allocator@VGen_003A8A70@@@_STL@@@_STL@@QAE@IABV?$allocator@VGen_003A8A70@@@1@@Z=?j_0003d16d@@YAXXZ")
#pragma comment(linker, "/alternatename:?get_allocator@?$vector@VGen_003A8A70@@V?$allocator@VGen_003A8A70@@@_STL@@@_STL@@QBE?AV?$allocator@VGen_003A8A70@@@2@XZ=?j_000404fd@@YAXXZ")
