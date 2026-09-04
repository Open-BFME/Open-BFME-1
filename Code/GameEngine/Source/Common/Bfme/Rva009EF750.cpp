// ?copy@Rva009EF750@@QAEPAV1@PAV1@@Z
// cl: /DNDEBUG /MD /EHsc

#pragma intrinsic(_ReadWriteBarrier)
extern "C" void __cdecl _ReadWriteBarrier(void);

struct Gen_t_009ee8e0_k4
{
	int a[1];
	Gen_t_009ee8e0_k4();
	Gen_t_009ee8e0_k4(const Gen_t_009ee8e0_k4 &other);
	~Gen_t_009ee8e0_k4();
	Gen_t_009ee8e0_k4 &operator=(const Gen_t_009ee8e0_k4 &other);
};

namespace _STL
{
	template <class T> struct _Identity;
	template <class T> struct less;
	template <class T> class allocator;

	template <class Key, class Value, class KeyOfValue, class Compare,
		class Allocator> class _Rb_tree
	{
	public:
		_Rb_tree(const _Rb_tree &other);

	private:
		void *m_header;
		unsigned int m_node_count;
		unsigned int m_compare;
	};
}

typedef _STL::_Rb_tree<
	Gen_t_009ee8e0_k4,
	Gen_t_009ee8e0_k4,
	_STL::_Identity<Gen_t_009ee8e0_k4>,
	_STL::less<Gen_t_009ee8e0_k4>,
	_STL::allocator<Gen_t_009ee8e0_k4> > Rva009EF750Tree;

struct CRITICAL_SECTION;
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
	CRITICAL_SECTION *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
	CRITICAL_SECTION *lock);

__forceinline void *operator new(unsigned int, void *where)
{
	return where;
}

class CriticalSectionLock
{
public:
	explicit CriticalSectionLock(int lock) : m_lock(lock)
	{
		EnterCriticalSection((CRITICAL_SECTION *)m_lock);
	}
	~CriticalSectionLock()
	{
		LeaveCriticalSection((CRITICAL_SECTION *)m_lock);
	}

	int m_lock;
};

struct Rva009EF750Output
{
	Rva009EF750Output(const Rva009EF750Tree &source) : m_tree(source)
	{
		m_value = 0;
		_ReadWriteBarrier();
		m_active = true;
	}
	Rva009EF750Tree m_tree;
	int m_value;
	bool m_active;
};

__forceinline void constructRva009EF750Output(
	Rva009EF750Output *out, const Rva009EF750Tree &source)
{
	__assume(out != 0);
	new (out) Rva009EF750Output(source);
}

class Rva009EF750
{
public:
	Rva009EF750 *copy(Rva009EF750 *out);

private:
	unsigned char m_unmodelled_000[0x2C];
	unsigned char m_critical_section[0x18];
	unsigned char m_unmodelled_044[0x14C];
	Rva009EF750Tree m_tree;
};

Rva009EF750 *Rva009EF750::copy(Rva009EF750 *out)
{
	volatile int dummy = 0;
	CriticalSectionLock lock((int)&m_critical_section);
	constructRva009EF750Output((Rva009EF750Output *)out,
		*(Rva009EF750Tree *)((unsigned char *)this + 0x190));
	return out;
}
