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

extern "C" void __cdecl Gen0002857EFreeListNode(void *node, unsigned int bytes);
void __cdecl operator delete(void *memory);
#pragma comment(linker, "/alternatename:_Gen0002857EFreeListNode=?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z")

class Gen0002857E
{
public:
	void destruct();
	__forceinline int getBucket() const { return m_bucket; }

	char m_pad30[0x30];
	int m_accountingValue;
	char m_pad3c[8];
	unsigned int m_bucket;
	char m_pad41;
	bool m_active;
};

class Gen0002857EOwner
{
public:
	void prepareRemoval(Gen0002857E *value);
	void finishRemoval(Gen0002857E *value);
	void destroy(Gen0002857E *value, int deferred);

private:
	char m_pad14[0x14];
	Gen0002857EBuckets m_buckets;
	int m_accountingTotal;
};

#pragma comment(linker, "/alternatename:?prepareRemoval@Gen0002857EOwner@@QAEXPAVGen0002857E@@@Z=?j_0001902e@@YAXXZ")
#pragma comment(linker, "/alternatename:?finishRemoval@Gen0002857EOwner@@QAEXPAVGen0002857E@@@Z=?j_00046d8a@@YAXXZ")
#pragma comment(linker, "/alternatename:?destruct@Gen0002857E@@QAEXXZ=?j_0003dad2@@YAXXZ")

void Gen0002857EOwner::destroy(Gen0002857E *value, int deferred)
{
	if (value->m_active)
		m_accountingTotal -= value->m_accountingValue;

	if (!deferred)
		prepareRemoval(value);

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

	finishRemoval(value);
	value->destruct();
	::operator delete(value);
}
