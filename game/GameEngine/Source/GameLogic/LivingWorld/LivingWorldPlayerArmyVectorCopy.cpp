// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <new>

// The LivingWorldPlayerArmy copy constructor and xfer body establish this
// vector's BfmeOwnVUM element type and its 0xB4-byte record size. The retail
// element copy constructor is pinned at 0x00362F30.
class BfmeOwnVUM
{
public:
	BfmeOwnVUM(const BfmeOwnVUM &other);
	virtual ~BfmeOwnVUM();
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();

	char m_fields[0xB0];
};

extern void j_0000f015();
extern void j_00038140();

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

	template <> class vector<BfmeOwnVUM, allocator<BfmeOwnVUM> >
		: public _Vector_base<BfmeOwnVUM, allocator<BfmeOwnVUM> >
	{
	public:
		typedef BfmeOwnVUM T;
		typedef _Vector_base<BfmeOwnVUM, allocator<BfmeOwnVUM> > Base;
		typedef allocator<BfmeOwnVUM> allocator_type;

		allocator_type get_allocator() const;
		vector(const vector &other);
	};

	// Retail routes vector::get_allocator through the ILT thunk at 0x0000f015.
	// The thunk is the thiscall member get_allocator, so a member pointer
	// taken from it makes the call with the same shape.
	typedef allocator<BfmeOwnVUM> (vector<BfmeOwnVUM, allocator<BfmeOwnVUM> >::*GetAllocatorFn)() const;
	union GetAllocatorThunk { void (*fn)(); GetAllocatorFn call; };
	static __forceinline GetAllocatorThunk get_allocator_thunk()
	{
		GetAllocatorThunk u;
		u.fn = j_0000f015;
		return u;
	}

	vector<BfmeOwnVUM, allocator<BfmeOwnVUM> >::vector(
		const vector<BfmeOwnVUM, allocator<BfmeOwnVUM> > &other)
		: Base((unsigned)(other.m_finish - other.m_start),
			(other.*get_allocator_thunk().call)())
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
