// An entry removal from the Open-BFME5 list built by Bfme5EntryAppend.cpp.
//
// The list stores twenty-byte entries. Each entry points at the owner field
// used as its key, owns a three-pointer vector copy, and stores the second
// argument. The removal compares the vector contents, the owner field's first
// word, and that second argument before it unlinks and destroys the entry.

namespace _STL
{
	// The node allocator's pool entry points are private STLport members
	// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
	// 0x0082E5F0); these TU-local helpers reach them under their real names.
	template <bool __threads, int __inst> class __node_alloc;
	static void nodePoolDeallocate(void *block, unsigned int bytes);
	template <bool __threads, int __inst>
	class __node_alloc
	{
		friend void nodePoolDeallocate(void *, unsigned int);
		static void *__cdecl _M_allocate(unsigned int __n);
		static void __cdecl _M_deallocate(void *__p, unsigned int __n);
	};
	static inline void nodePoolDeallocate(void *block, unsigned int bytes) { __node_alloc<true, 0>::_M_deallocate(block, bytes); }
}

void __cdecl operator delete(void *block);

class Gen_dtor_000d4030
{
public:
	~Gen_dtor_000d4030(void);
};

struct BfmeEntry5
{
	void *m_bfmeOwner;
	float *m_bfmeStart;
	float *m_bfmeFinish;
	float *m_bfmeEnd;
	void *m_bfmeExtra;
};

struct BfmeEntry5Node
{
	BfmeEntry5Node *m_bfmeNext;
	BfmeEntry5Node *m_bfmePrev;
	BfmeEntry5 *m_bfmeValue;
};

struct BfmeEntry5Head
{
	BfmeEntry5Node *m_bfmeNext;
	BfmeEntry5Node *m_bfmePrev;
};

class ControlBar5
{
public:
	char m_bfmePad[0x24];
	bool m_bfmeDirty;
};

extern ControlBar5 *TheControlBar;

class Gen_000D5E90
{
public:
	void bfmeRemove(void *owner, void *extra);

private:
	char m_bfmePad[0x640];
	BfmeEntry5Head *m_bfmeList;
};

// ?bfmeRemove@Gen_000D5E90@@QAEXPAX0@Z
void Gen_000D5E90::bfmeRemove(void *owner, void *extra)
{
	BfmeEntry5Head *head = m_bfmeList;
	BfmeEntry5Node *node = head->m_bfmeNext;

	if (node == (BfmeEntry5Node *)head)
		return;

	float *ownerStart = *(float **)((char *)owner + 0x74);
	float *ownerFinish = *(float **)((char *)owner + 0x78);
	unsigned int ownerCount = (unsigned int)(ownerFinish - ownerStart);
	BfmeEntry5 *entry;
	float *entryStart;
	float *entryFinish;
	unsigned int entryCount;
	float *entryValue;

	while (node != (BfmeEntry5Node *)head)
	{
		entry = node->m_bfmeValue;
		entryStart = entry->m_bfmeStart;
		entryFinish = entry->m_bfmeFinish;
		entryCount = (unsigned int)(entryFinish - entryStart);

		if (entryCount == ownerCount)
		{
			entryValue = entryStart;

			if (entryValue != entryFinish)
			{
				do
				{
					if (*entryValue != *(float *)((char *)ownerStart +
						((char *)entryValue - (char *)entryStart)))
						goto next_entry;

					++entryValue;
				} while (entryValue != entryFinish);
			}

			if (*(void **)entry->m_bfmeOwner == *(void **)((char *)owner + 0x70) &&
				entry->m_bfmeExtra == extra)
			{
				BfmeEntry5Node *next = node->m_bfmeNext;
				BfmeEntry5Node *previous = node->m_bfmePrev;

				previous->m_bfmeNext = next;
				next->m_bfmePrev = previous;
				_STL::nodePoolDeallocate(node, 0x0c);

				((Gen_dtor_000d4030 *)entry)->~Gen_dtor_000d4030();
				::operator delete(entry);
				TheControlBar->m_bfmeDirty = true;
				return;
			}
		}

	next_entry:
		node = node->m_bfmeNext;
	}
}
