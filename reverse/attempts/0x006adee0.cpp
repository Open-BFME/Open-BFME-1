// ?d_006adee0@@YAXXZ
// partial score=0.28 date=2026-09-24
// cl: /DNDEBUG /MD /EHsc

// This source reconstructs the carved 305-byte body at 0x006ADEE0.
// Its only caller at 0x006B9C90 remains anonymous, so this source keeps the address.

// The list at this+0xB04 stores pointers at node+8, as the matched iterator at
// 0x00696B80 shows for AudioRequest* entries. The unwind map names ThingRef and
// BfmeStr4BE cleanup calls at 0x00696870 and 0x00694BE0.

// The helper at 0x006ADD50 receives this in ECX and ThingRef* on the stack.
// It returns with ret 4 and reads the pointer without changing it.
// The import table names the AIL lock and unlock calls and both Interlocked calls.

// This draft compiles to 304 bytes. Its first byte mismatch is at +0x1B, where
// MSVC saves EDI instead of EBP.

extern "C" __declspec(dllimport) int __stdcall AIL_lock_mutex();
extern "C" __declspec(dllimport) int __stdcall AIL_unlock_mutex();
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long *addend);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long *addend);

struct ListNodeBase
{
	ListNodeBase *m_next;
	ListNodeBase *m_prev;
};

namespace _STL
{
template <bool threads, int instance>
class __node_alloc
{
public:
	static void _M_deallocate(void *p, unsigned int size);
};
}

class RefCounted
{
public:
#define RVA006ADEE0_SLOT(N) virtual void slot##N() = 0
	RVA006ADEE0_SLOT(00);
#undef RVA006ADEE0_SLOT
	long m_refCount;
};

class ThingRef
{
public:
	ThingRef() : m_ptr(0) {}
	~ThingRef()
	{
		if (m_ptr && InterlockedDecrement(&m_ptr->m_refCount) <= 0)
			m_ptr->slot00();
	}
	RefCounted *m_ptr;
};

struct BfmeStr4BE
{
	char m_buf[1];
	BfmeStr4BE() : m_buf() {}
	~BfmeStr4BE() { freeStr(); }
	void freeStr()
	{
		if (m_buf[0])
			AIL_unlock_mutex();
	}
	void lock()
	{
		AIL_lock_mutex();
		m_buf[0] = 1;
	}
	void unlock()
	{
		AIL_unlock_mutex();
		m_buf[0] = 0;
	}
};

class Rva006ADEE0Owner
{
public:
	void bfmeClearList006ADEE0();
	void rva006ADD50(ThingRef *held);

	unsigned char m_pad[0xb04];
	ListNodeBase *m_listHead;   // +0xb04, sentinel node of an STL::list
};

static void bfmeReleaseIfLast(RefCounted *obj)
{
	if (obj)
	{
		if (InterlockedDecrement(&obj->m_refCount) <= 0)
			obj->slot00();
	}
}

void Rva006ADEE0Owner::bfmeClearList006ADEE0()
{
	ThingRef held;
	BfmeStr4BE mutex;
	mutex.lock();

	if (m_listHead->m_next != m_listHead)
	{
		do
		{
			ListNodeBase *node = m_listHead->m_next;
			RefCounted **slot = (RefCounted **)((char *)node + 8);
			if (slot != &held.m_ptr)
			{
				RefCounted *payload = *slot;
				if (payload)
					InterlockedIncrement(&payload->m_refCount);
				held.m_ptr = payload;
			}

			node = m_listHead->m_next;
			RefCounted *payload = *(RefCounted **)((char *)node + 8);
			ListNodeBase *next = node->m_next;
			ListNodeBase *prev = node->m_prev;
			prev->m_next = next;
			next->m_prev = prev;
			bfmeReleaseIfLast(payload);
			_STL::__node_alloc<true, 0>::_M_deallocate(node, 0xc);
			mutex.unlock();
			rva006ADD50(&held);
			bfmeReleaseIfLast(held.m_ptr);
			held.m_ptr = 0;
			mutex.lock();
		} while (m_listHead->m_next != m_listHead);
	}

	mutex.unlock();
}
