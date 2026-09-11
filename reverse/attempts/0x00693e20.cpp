// ?d_00693e20@@YAXXZ
// partial score=0.98 date=2026-09-11
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Open-BFME5: Gen0002857EOwner's final removal path at 0x00693E20.
//
// Gen0002857E::release calls the owner's notify method at 0x00693EC0 when the
// guarded reference count reaches zero.  That method calls this routine with
// the object and a defer-removal flag.  The object supplies its accounting
// value at +0x30, bucket number at +0x3c, and active flag at +0x41.  Each
// owner bucket is a sentinel-headed list of object pointers.

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

private:
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
	int m_bucket;
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
		Gen0002857EListNode *head = m_buckets[value->getBucket()];
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
