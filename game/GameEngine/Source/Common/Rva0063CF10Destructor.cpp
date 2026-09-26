// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the destructor at 0x0063CF10 (352 B), a ThreadClass-derived
// class (base dtor already pinned by the Watchdog destructor, ILT
// 0x009DB530, empty inline vtable-restore).  Reverse member unwind: a
// CriticalSectionClass::LockClass holder at +0xA8 (delete, no null store),
// a real CriticalSectionClass member at +0xA0 (already matched), five
// BigBlockReleases-style vector holders (elemsize 8, threshold 128) at
// +0x90/+0x84/+0x78/+0x6C/+0x60.  Member types are opaque address-derived
// shells sized from the offsets with out-of-line destructors except
// CriticalSectionClass/LockClass which resolve by their real matched
// names; the destructor body is empty and the compiler-generated reverse
// unwind reproduces retail exactly.

namespace _STL
{

template <bool __threads, int __inst>
class __node_alloc
{
	static void _M_deallocate( void *p, unsigned int n );

public:
	static void deallocate( void *p, unsigned int n )
	{
		if ( n > 128 )
			::operator delete( p );
		else
			_M_deallocate( p, n );
	}
};

}

class ThreadClass
{
public:
	~ThreadClass();
};

class CriticalSectionClass
{
public:
	~CriticalSectionClass();

	class LockClass
	{
	public:
		~LockClass();

	private:
		char m_body[ 4 ];
	};

private:
	void *m_handle;
	bool m_locked;
};

struct Rva0063CF10LockHolder
{
	~Rva0063CF10LockHolder()
	{
		if ( m_lock )
			delete m_lock;
	}

	CriticalSectionClass::LockClass *m_lock;
};

struct Rva0063CF10VectorHolder
{
	~Rva0063CF10VectorHolder()
	{
		char *start = m_start;
		unsigned int count = m_cap - start;

		if ( start )
		{
			_STL::__node_alloc< true, 0 >::deallocate( start, count );
		}
	}

	char *m_start;
	char *m_finish;
	char *m_cap;
};

class Rva0063CF10 : public ThreadClass
{
public:
	~Rva0063CF10();

private:
	unsigned char m_unreconstructed00[ 0x60 ];
	Rva0063CF10VectorHolder m_vector60;
	Rva0063CF10VectorHolder m_vector6C;
	Rva0063CF10VectorHolder m_vector78;
	Rva0063CF10VectorHolder m_vector84;
	Rva0063CF10VectorHolder m_vector90;
	unsigned char m_unreconstructed9C[ 0xA0 - 0x9C ];
	CriticalSectionClass m_criticalSection;
	Rva0063CF10LockHolder m_lockA8;
};

// ??1Rva0063CF10@@QAE@XZ
Rva0063CF10::~Rva0063CF10()
{
}
