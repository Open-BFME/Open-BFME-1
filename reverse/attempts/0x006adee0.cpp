// ?processRequestList@MilesAudioManager@@QAEXXZ
// partial score=0.4 date=2026-09-25
// cl: /DNDEBUG /MD /EHsc

// Vtable 0x0111C0C0 puts retail 0x006B9C90 in slot 5. The Zero Hour update
// calls processRequestList after setDeviceListenerPosition, and retail update
// calls 0x006ADEE0 at the same point.
//
// The matched iterator at 0x00696B80 shows that list payloads start at node+8.
// The unwind map sends ThingRef at EBP-0x14 to its matched destructor at
// 0x00696870 and sends BfmeStr4BE at EBP-0x10 to freeStr at 0x00694BE0.
//
// The helper at 0x006ADD50 receives this in ECX and ThingRef* on the stack.
// This draft compiles to 282 of 305 bytes. It differs at 171 bytes outside
// relocations, with its first mismatch at +0x40. The external ThingRef
// destructor keeps this in EBP.

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
	~ThingRef();
	RefCounted *m_ptr;
};

struct BfmeStr4BE
{
	char m_buf[1];
	BfmeStr4BE() : m_buf() { lock(); }
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

class MilesAudioManager
{
public:
	void processRequestList();
	void rva006ADD50(ThingRef *held);

	unsigned char m_pad[0xb04];
	ListNodeBase *m_rva006ADEE0ListHead;   // +0xb04, sentinel node of an STL::list
};

static void bfmeReleaseIfLast(RefCounted *obj)
{
	if (obj)
	{
		if (InterlockedDecrement(&obj->m_refCount) <= 0)
			obj->slot00();
	}
}

void MilesAudioManager::processRequestList()
{
	ThingRef held;
	BfmeStr4BE mutex;

	if (*reinterpret_cast<ListNodeBase *volatile *>(m_rva006ADEE0ListHead) != m_rva006ADEE0ListHead)
	{
		do
		{
			ListNodeBase *node = m_rva006ADEE0ListHead->m_next;
			RefCounted **slot = (RefCounted **)((char *)node + 8);
			if (slot != &held.m_ptr)
			{
				RefCounted *payload = *slot;
				if (payload)
					InterlockedIncrement(&payload->m_refCount);
				held.m_ptr = payload;
			}

			node = m_rva006ADEE0ListHead->m_next;
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
		} while (*reinterpret_cast<ListNodeBase *volatile *>(m_rva006ADEE0ListHead) != m_rva006ADEE0ListHead);
	}

	mutex.unlock();
}
