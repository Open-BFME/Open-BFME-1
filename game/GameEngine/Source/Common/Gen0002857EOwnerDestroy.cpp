// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?destroy@Gen0002857EOwner@@QAEXPAVGen0002857E@@H@Z
// Gen0002857E::release reaches Gen0002857EOwner::notify when the guarded
// reference count reaches zero. The notify body calls this two-argument
// cleanup routine with the object and a deferred-removal flag.
//
// The retail body subtracts the object's +0x30 accounting value from the
// owner's +0x38 total, unlinks an inactive object from one of nine sentinel
// lists, calls the owner's cleanup helpers, destroys the object, and frees it.

class Gen0002857E;

struct Gen0002857EListNode
{
	Gen0002857EListNode *next;
	Gen0002857EListNode *prev;
	Gen0002857E *value;
};

class Gen0002857EBuckets
{
public:
	__forceinline Gen0002857EListNode *&operator[](int index) { return m_heads[index]; }
	Gen0002857EListNode *m_heads[9];
};

void __cdecl operator delete(void *memory);

// _STL::__node_alloc<true, 0>::_M_deallocate is private in the STLport
// header (inputs/vendor/stlport/stl/_alloc.h), so the deallocate call goes
// through a TU-local force-inlined helper that the template befriends.  The
// helper never reaches the object file: cl folds it into the caller and the
// only reference left is to the private static's own decorated name.
static void __forceinline Gen0002857EFreeListNode(void *node, unsigned int bytes);

namespace _STL
{
template <bool __threads, int __inst>
class __node_alloc
{
private:
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
	friend void ::Gen0002857EFreeListNode(void *, unsigned int);
};
}

static void __forceinline Gen0002857EFreeListNode(void *node, unsigned int bytes)
{
	_STL::__node_alloc<true, 0>::_M_deallocate(node, bytes);
}

class Gen0002857E
{
public:
	__forceinline int getBucket() const { return m_bucket; }

	char m_pad30[0x30];
	int m_accountingValue;
	char m_pad3c[8];
	unsigned int m_bucket;
	char m_pad41;
	bool m_active;
};

// Retail reaches the owner helpers and the object's destructor through the
// ILT thunks ?j_0001902e, ?j_00046d8a and ?j_0003dad2; the calls are routed
// through compile-time constant member pointers so they stay direct calls.
extern void j_0001902e();
extern void j_00046d8a();
extern void j_0003dad2();

class Gen0002857EOwner
{
public:
	void destroy(Gen0002857E *value, int deferred);

private:
	char m_pad14[0x14];
	Gen0002857EBuckets m_buckets;
	int m_accountingTotal;
};

void Gen0002857EOwner::destroy(Gen0002857E *value, int deferred)
{
	typedef void (Gen0002857EOwner::*OwnerCall)(Gen0002857E *);
	typedef void (Gen0002857E::*ValueCall)();

	if (value->m_active)
		m_accountingTotal -= value->m_accountingValue;

	if (!deferred)
	{
		union { void (*fn)(); OwnerCall call; } u = { j_0001902e };
		(this->*u.call)(value);
	}

	if (!value->m_active)
	{
		int bucket = value->m_bucket;
		__assume(bucket >= 0 && bucket < 9);
		Gen0002857EListNode *head = m_buckets.m_heads[bucket];
		for (Gen0002857EListNode *node = head->next; node != head; node = node->next)
		{
			if (node->value == value)
			{
				Gen0002857EListNode *next = node->next;
				Gen0002857EListNode *previous = node->prev;
				previous->next = next;
				next->prev = previous;
				Gen0002857EFreeListNode(node, sizeof(*node));
				break;
			}
		}
	}

	{
		union { void (*fn)(); OwnerCall call; } u = { j_00046d8a };
		(this->*u.call)(value);
	}
	{
		union { void (*fn)(); ValueCall call; } u = { j_0003dad2 };
		(value->*u.call)();
	}
	::operator delete(value);
}
