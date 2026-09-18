// ?d_008833c0@@YAXXZ
// partial score=0.55 date=2026-09-17
// cl: /O2 /DNDEBUG /MD /EHsc

// Address-derived identity: this is the debug-allocation tracker helper called
// by MemoryPool::_Allocate.  The owner and bucket layout are shared with the
// landed Rva008838F0 constructor, lookup, and destructor; the helper's own
// name remains tied to its retail address because no semantic symbol survives.

#include <stdarg.h>
#include <string.h>

extern "C" __declspec(dllimport) void __stdcall Rva01358D18Enter(void *lock);
extern "C" __declspec(dllimport) void __stdcall Rva01358E74Leave(void *lock);
extern "C" __declspec(dllimport) void *__stdcall GetProcessHeap(void);
extern "C" __declspec(dllimport) void *__stdcall HeapAlloc(
	void *heap, unsigned long flags, unsigned long bytes);
extern "C" __declspec(dllimport) int __stdcall HeapFree(
	void *heap, unsigned long flags, void *block);
extern "C" __declspec(dllimport) int __cdecl _vsnprintf(
	char *buffer, unsigned int count, const char *format, va_list args);

#pragma intrinsic(memcpy)

extern unsigned int Rva01336CDC;
extern void d_0088ce00(void);

class DebugStackwalk
{
public:
	class Signature
	{
	public:
		Signature(void) : m_numAddr(0) {}
		unsigned GetAddress(int index) const;

	private:
		unsigned m_numAddr;
		unsigned m_addr[256];
	};

	static int StackWalk(Signature &signature, void *context);
};

#pragma comment(linker, "/alternatename:?StackWalk@DebugStackwalk@@SAHAAVSignature@1@PAU_CONTEXT@@@Z=?d_0088ce00@@YAXXZ")

struct Rva008833C0Node
{
	Rva008833C0Node *m_next;
	unsigned int m_type;
	unsigned int m_block;
	unsigned int m_size;
	unsigned int m_serial;
	char *m_description;
	unsigned int m_signatureCount;
	unsigned int m_signature[32];
	int m_freeCheckpoint;
};

class Rva008838F0Owner
{
	public:
	char m_pad00[0x0c];
	Rva008833C0Node *m_buckets[0x2b7b];
	Rva008833C0Node *m_slots[0x7530];
	unsigned int m_slotIndex;
	Rva008833C0Node *m_current;
	unsigned char m_disabled;
	char m_pad282c1[3];
	void *m_previousOwner;
	void *m_lock;
};

extern "C" void Rva008833C0Insert(Rva008838F0Owner *owner,
	unsigned int type, void *block, unsigned int size,
	const char *format, ...)
{
	if (owner->m_disabled != 0)
		return;

	{
		void *lock = owner->m_lock;
		if (lock)
			Rva01358D18Enter(lock);
	}

	Rva008833C0Node **link = &owner->m_buckets[(unsigned int)block % 0x2b7b];
	while (*link && (*link)->m_block != (unsigned int)block)
		link = (Rva008833C0Node **)*link;

	Rva008833C0Node *node = *link;
	if (node)
	{
		int checkpoint = node->m_freeCheckpoint;
		if (checkpoint < 0)
			goto leave;

		*link = node->m_next;
		node->m_next = owner->m_current;
		owner->m_current = node;
		owner->m_slots[checkpoint] = 0;

		if (node->m_description)
		{
			HeapFree(GetProcessHeap(), 0, node->m_description);
			node->m_description = 0;
		}
	}

	{
		Rva008833C0Node *freeNode = owner->m_current;
		if (freeNode)
		{
			owner->m_current = freeNode->m_next;
			node = freeNode;
		}
		else
		{
			node = (Rva008833C0Node *)HeapAlloc(GetProcessHeap(), 4, 0xa4);
		}
	}

	node->m_next = *link;
	*link = node;
	node->m_block = (unsigned int)block;
	node->m_type = type;
	node->m_size = size;
	node->m_serial = ++Rva01336CDC;
	node->m_freeCheckpoint = -1;

	if (format != 0)
	{
		char diagnostic[0x200];
		va_list args;
		va_start(args, format);
		if (_vsnprintf(diagnostic, 0x200, format, args) < 0)
			diagnostic[0x1ff] = 0;
		va_end(args);

		unsigned int length = strlen(diagnostic) + 1;
		node->m_description = (char *)HeapAlloc(GetProcessHeap(), 4, length);
		memcpy(node->m_description, diagnostic, length);
	}
	else
	{
		node->m_description = 0;
	}

	{
		DebugStackwalk::Signature signature;
		unsigned int count = (unsigned int)DebugStackwalk::StackWalk(
			signature, 0);
		if (count > 0x20)
			count = 0x20;
		node->m_signatureCount = count;
		for (unsigned int index = 0; index < count; ++index)
			node->m_signature[index] = signature.GetAddress(index);
	}

leave:
	if (owner->m_lock)
		Rva01358E74Leave(owner->m_lock);
}
