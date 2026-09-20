// ?d_006adee0@@YAXXZ
// partial score=0.19 date=2026-09-20
// cl: /DNDEBUG /MD /EHsc

// Open-BFME: carved SEH body at retail 0x006ADEE0 (305 B). No named caller;
// identity is address-derived. The STL::list<AudioRequest*> node layout
// matches Rva00696B80AudioRequestIteratorArrow.cpp (node+8 = payload). The
// two indirect calls resolve via reverse/imports.csv: 0x013595C4 is
// mss32.dll!_AIL_lock_mutex@0 and 0x013596D8 is mss32.dll!_AIL_unlock_mutex@0
// (the symbols.csv pin naming one of them "Rva01358E54" is stale/wrong --
// 0x01358E54 is really KERNEL32!InterlockedDecrement per imports.csv). This
// walks a list at this+0xB04, releasing each element's ref-counted payload,
// then does the same for one more object (ebx) outside the loop.

extern "C" int __stdcall AIL_lock_mutex();
extern "C" int __stdcall AIL_unlock_mutex();
extern "C" long __stdcall InterlockedIncrement(long *addend);
extern "C" long __stdcall InterlockedDecrement(long *addend);

struct ListNodeBase
{
	ListNodeBase *m_next;
	ListNodeBase *m_prev;
};

void _M_deallocate_node12(void *p, unsigned int size);

class RefCounted
{
public:
#define RVA006ADEE0_SLOT(N) virtual void slot##N() = 0
	RVA006ADEE0_SLOT(00);
#undef RVA006ADEE0_SLOT
	long m_refCount;
};

class Rva006ADEE0Owner
{
public:
	void bfmeClearList006ADEE0();

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
	AIL_lock_mutex();

	ListNodeBase *sentinel = m_listHead;
	if (sentinel->m_next != sentinel)
	{
		ListNodeBase *node = sentinel->m_next;
		do
		{
			RefCounted *payload = *(RefCounted **)((char *)node + 8);
			bfmeReleaseIfLast(payload);

			ListNodeBase *next = node->m_next;
			_M_deallocate_node12(node, 0xc);
			node = next;
		} while (node != sentinel);
	}

	AIL_unlock_mutex();
}
