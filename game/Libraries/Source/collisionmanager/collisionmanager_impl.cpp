// cl: /O2 /Ob1
// Retail 0x009A36F0 (?d_009a36f0@@YAXXZ, dump d_0099d0c0.asm).
// Full control-flow decode (verified against tools/dis_retail.py):
//   this = ebx (a large object; the only fields it touches are a list-head
//   pointer at +8 and a flag byte at +0xC06D -- both address-derived, no
//   semantic class identity proven).
//   param (edi, the one stack arg, ret 4) exposes two virtual slots: +0x18
//   (void f(int), called with 0) and +0x1c (returns a "thing" pointer).
//   If param is null, or the +0x1c call returns null, the function is a
//   no-op.  Otherwise it calls param->slot18(0), then:
//     - if this->m_flag is set: link `thing` into the doubly-linked list
//       rooted at this+8 (same back-slot/next idiom as the landed
//       Rva009A3770HashChainInsert.cpp), unless it is already linked
//       (thing->m_10 != 0), then zero thing->m_4;
//     - else: call the still-dump unlinker at 0x009A3630 (ecx=this), the
//       matched dtor ??1Rva009A45A0CollisionData@@QAE@XZ on `thing`, then
//       operator delete(thing).
// callees: 0x009A3630 (dump, pinned below as unlinkChain), 0x009A2390
// (matched CollisionData dtor), 0x00881EB0 (operator delete).
// landed neighbour Rva009A3770HashChainInsert.cpp supplies the link idiom.

class Rva009A36F0Thing
{
public:
	unsigned char m_pad0[4];
	int m_4;
	unsigned char m_pad8[8];
	void *m_10;
	Rva009A36F0Thing *m_14;
	unsigned char m_pad18[8];
	void *m_queueHead;
};

class Rva009A36F0Param
{
public:
	virtual void slot0();
	virtual void slot4();
	virtual void slot8();
	virtual void slotc();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18(int);
	virtual Rva009A36F0Thing *slot1c();
};

#include "../../../GameEngine/Include/Common/ScalarTypes.h"

struct Rva009A3540OpaqueOwner;

// One end of a collision data's interval on one axis; each axis keeps its
// end points in a sorted doubly linked list (heads at CollisionManagerImpl
// +0x0c).
struct Rva009A3AD0Endpoint
{
	Rva009A3AD0Endpoint *m_prev;	// +0x00
	Rva009A3AD0Endpoint *m_next;	// +0x04
	class Rva009A45A0CollisionData *m_node;	// +0x08
	unsigned int m_isMax : 1;	// +0x0c
	Real value;	// +0x10

	bool isMin() const { return !m_isMax; }
};

struct Rva009A3AD0Interval
{
	Rva009A3AD0Endpoint m_min;
	Rva009A3AD0Endpoint m_max;
};

class Rva009A45A0CollisionData
{
public:
	~Rva009A45A0CollisionData();

	void *m_owner;	// +0x00
	void *m_source;	// +0x04
	void *m_rootPrev;	// +0x08
	Rva009A45A0CollisionData *m_rootNext;	// +0x0c
	void *m_dirtyPrev;	// +0x10
	Rva009A45A0CollisionData *m_dirtyNext;	// +0x14
	Rva009A45A0CollisionData **m_openPrev;	// +0x18
	Rva009A45A0CollisionData *m_openNext;	// +0x1c
	int m_rva009A3AD0_020;	// +0x20
	union
	{
		Rva009A3AD0Endpoint m_endpoints[6];	// +0x24
		Rva009A3AD0Interval m_intervals[3];
	};
};

void __cdecl operator delete(void *block);

class Rva009A36F0Owner
{
public:
	void apply(Rva009A36F0Param *param);
	void unlinkChain(Rva009A36F0Thing *thing);

private:
	unsigned char m_pad0[8];
	Rva009A36F0Thing *m_listHead;
	unsigned char m_padToFlag[0xae04 - 0xc];
	void *m_freeHead;
	unsigned char m_unreconstructed_ae08[4];
	void *m_cursor;
	unsigned char m_padToFlagAE10[0xc06d - 0xae10];
	unsigned char m_flag;
};

void Rva009A36F0Owner::apply(Rva009A36F0Param *param)
{
	if (param == 0)
		return;

	Rva009A36F0Thing *thing = param->slot1c();
	if (thing == 0)
		return;

	param->slot18(0);

	if (m_flag)
	{
		if (thing->m_10 == 0)
		{
			Rva009A36F0Thing **slot = (Rva009A36F0Thing **)&m_listHead;

			thing->m_10 = slot;

			Rva009A36F0Thing *head = *slot;
			thing->m_14 = head;
			if (head != 0)
				head->m_10 = &thing->m_14;

			*slot = thing;
		}

		thing->m_4 = 0;
		return;
	}

	unlinkChain(thing);
	// The qualified destructor call (p->T::~T(), not p->~T()) is what keeps the
// call direct: the unqualified spelling makes MSVC 7.1 route through the
// scalar-deleting destructor ??_GT@@QAEPAXI@Z, which retail does not call here.
	((Rva009A45A0CollisionData *)thing)->Rva009A45A0CollisionData::~Rva009A45A0CollisionData();
	operator delete(thing);
}

struct Rva009A3300Node
{
    char m_pad0[8];
    unsigned int m_key0;
    unsigned int m_key1;
    char m_pad10[0x1c];
};
class Rva009A3300HashTable
{
public:
    void remove(Rva009A3300Node *entry);
    // ?removeKey@Rva009A3300HashTable@@QAEXII@Z absent-from-retail
    __forceinline void removeKey(unsigned a, unsigned b)
    {
        Rva009A3300Node key;
        key.m_key0 = a;
        key.m_key1 = b;
        remove(&key);
    }
};
struct PairNode3630
{
    struct Link { Link **backlink; Link *next; };
    char pad00[8];
    unsigned key0, key1, counter;
    Link first;
    unsigned pad1c;
    Link second;
    unsigned pad28;
    PairNode3630 **backlink;
    PairNode3630 *next;
};

// ?unlinkChain@Rva009A36F0Owner@@QAEXPAVRva009A36F0Thing@@@Z
// Open BFME 2: Code/GameEngine/Source/Common/Rva009A36F0Owner.cpp.
void Rva009A36F0Owner::unlinkChain(Rva009A36F0Thing *thing)
{
    while (thing->m_queueHead)
    {
        PairNode3630 *node = *(PairNode3630 **)((char *)thing->m_queueHead + 8);
        if (node->first.next)
            node->first.next->backlink = node->first.backlink;
        *node->first.backlink = node->first.next;
        PairNode3630::Link *next = node->second.next;
        node->first.backlink = 0;
        if (next)
            next->backlink = node->second.backlink;
        *node->second.backlink = node->second.next;
        node->second.backlink = 0;
        ((Rva009A3300HashTable *)((char *)this + 0xae10))->removeKey(node->key0, node->key1);
        PairNode3630 *cursor = (PairNode3630 *)m_cursor;
        if (cursor == node)
            m_cursor = cursor->next;
        if (node->next)
            node->next->backlink = node->backlink;
        *node->backlink = node->next;
        node->backlink = 0;
        node->next = (PairNode3630 *)m_freeHead;
        m_freeHead = node;
    }
}

// Callees of UpdateSort, by their ledger names.
class Rva009A2420CollisionNode
{
public:
	unsigned int getMovementScore(bool removeAndReInsert);
};

class BfmeLinkXX
{
public:
	void bfmeDropXX();
};

class Rva009A2A50Table
{
public:
	void recycleBuckets009A2A50();
};

class Rva009A2B80Owner
{
public:
	void clear();
};

class Rva009A3540PairOwner
{
public:
	void rva009A3960(Rva009A3540OpaqueOwner *first, Rva009A3540OpaqueOwner *second);
	void removePair(Rva009A3540OpaqueOwner *a, Rva009A3540OpaqueOwner *b);
};

// CollisionManagerImpl::UpdateSort, retail 0x009A3AD0 (1244 bytes); EA
// evidence names it (chain+direct) and WorldBuilder places it in this file.
// Each dirty data refreshes its coordinates; a moved one leaves its three
// sorted axis lists and is re-inserted by value, opening overlap pairs with
// every data whose interval it crosses, or pushed to the list fronts while a
// rebuild is pending. A small total move re-sorts the lists by insertion,
// adding and removing overlap pairs as end points cross; otherwise every pair
// is dropped, the lists are merge-sorted (0x009A2750) and swept again.
// Ported from Open-BFME-2's matched copy (0x00759600), which is byte-identical
// and was itself finished from this repo's banked draft.
//
// 0x009A2750 is the bottom-up merge sort of the three axis endpoint lists;
// UpdateSort calls it after the reinsertion pass. The body is ported from
// Open-BFME-2's matched twin at 0x007586F0 (collisionmanager_impl.cpp) and
// compiles to the full 460-byte BFME1 body with no relocations. The two
// left-run count reads go through the volatile accessor because that is what
// reproduces VC7.1's register cost; it is a codegen choice, not evidence that
// the original field was declared volatile.

class CollisionManagerImpl
{
public:
	void UpdateSort();
	void rva009A2750();

	Rva009A45A0CollisionData *m_root;	// +0x00
	unsigned int m_nodeCount;	// +0x04
	Rva009A45A0CollisionData *m_dirty;	// +0x08
	Rva009A3AD0Endpoint *m_axisHeads[3];	// +0x0c
	unsigned char m_table[0xAE10 - 0x18];
	unsigned char m_table2[0xC068 - 0xAE10];
	unsigned int m_axisCount;	// +0xc068
	bool m_rebuild;	// +0xc06c

	__forceinline void addOverlap(Rva009A45A0CollisionData *a, Rva009A45A0CollisionData *b)
	{
		((Rva009A3540PairOwner *)this)->rva009A3960(
			(Rva009A3540OpaqueOwner *)a, (Rva009A3540OpaqueOwner *)b);
	}

	__forceinline void insertSorted(Rva009A45A0CollisionData *node, Rva009A3AD0Interval *axis, Rva009A3AD0Endpoint **head)
	{
		Rva009A3AD0Endpoint *cur = *head;
		Rva009A3AD0Endpoint *prev = 0;
		Rva009A45A0CollisionData *open = 0;
		Real value = axis->m_max.value;
		while (cur != 0 && !(cur->value > value))
		{
			if (cur->isMin())
			{
				cur->m_node->m_openPrev = &open;
				cur->m_node->m_openNext = open;
				if (cur->m_node->m_openNext != 0)
					cur->m_node->m_openNext->m_openPrev = &cur->m_node->m_openNext;
				open = cur->m_node;
			}
			else
			{
				if (cur->m_node->m_openNext != 0)
					cur->m_node->m_openNext->m_openPrev = cur->m_node->m_openPrev;
				*cur->m_node->m_openPrev = cur->m_node->m_openNext;
				cur->m_node->m_openPrev = 0;
			}
			prev = cur;
			cur = cur->m_next;
		}

		axis->m_max.m_prev = prev;
		axis->m_max.m_next = cur;
		if (prev != 0)
			prev->m_next = &axis->m_max;
		else
			*head = &axis->m_max;
		if (cur != 0)
			axis->m_max.m_next->m_prev = &axis->m_max;
		prev = &axis->m_max;

		if (cur != 0)
		{
			while (open != 0)
			{
				addOverlap(open, node);
				Rva009A45A0CollisionData *closed = open;
				if (closed->m_openNext != 0)
					closed->m_openNext->m_openPrev = closed->m_openPrev;
				*closed->m_openPrev = closed->m_openNext;
				closed->m_openPrev = 0;
			}
			value = axis->m_min.value;
			do
			{
				if (!(cur->value < value))
					break;
				if (cur->isMin())
					addOverlap(cur->m_node, node);
				prev = cur;
				cur = cur->m_next;
			}
			while (cur != 0);
		}

		axis->m_min.m_prev = prev;
		axis->m_min.m_next = cur;
		prev->m_next = &axis->m_min;
		if (cur != 0)
			axis->m_min.m_next->m_prev = &axis->m_min;
	}

	__forceinline void pushFront(Rva009A3AD0Endpoint *endpoint, Rva009A3AD0Endpoint **head)
	{
		endpoint->m_prev = 0;
		endpoint->m_next = *head;
		if (endpoint->m_next != 0)
			endpoint->m_next->m_prev = endpoint;
		*head = endpoint;
	}
};

void CollisionManagerImpl::UpdateSort()
{
	unsigned int totalScore = 0;
	Rva009A45A0CollisionData *node = m_dirty;
	while (node != 0)
	{
		unsigned int score = ((Rva009A2420CollisionNode *)node)->getMovementScore(true);
		if (score == 0)
		{
			node = node->m_dirtyNext;
			continue;
		}
		totalScore += score;
		((Rva009A36F0Owner *)this)->unlinkChain((Rva009A36F0Thing *)node);
		Rva009A45A0CollisionData *next = node->m_dirtyNext;
		if (node->m_source != 0)
		{
			if (node->m_endpoints[0].m_prev != 0)
			{
				unsigned int index = 0;
				do
				{
					Rva009A3AD0Endpoint *endpoint = &node->m_endpoints[index];
					if (endpoint->m_prev != 0)
						endpoint->m_prev->m_next = endpoint->m_next;
					else
						m_axisHeads[index >> 1] = endpoint->m_next;
					if (endpoint->m_next != 0)
						endpoint->m_next->m_prev = endpoint->m_prev;
					endpoint->m_prev = 0;
					endpoint->m_next = 0;
					++index;
				}
				while (index < 6);
			}

			unsigned int k = 0;
			do
			{
				if (k < m_axisCount && !m_rebuild)
					insertSorted(node, &node->m_intervals[k], &m_axisHeads[k]);
				else
				{
					pushFront(&node->m_intervals[k].m_min, &m_axisHeads[k]);
					pushFront(&node->m_intervals[k].m_max, &m_axisHeads[k]);
				}
				++k;
			}
			while (k < 3);

			((BfmeLinkXX *)node)->bfmeDropXX();
		}
		else
		{
			delete node;
		}
		node = next;
	}

	while (m_dirty != 0)
	{
		totalScore += ((Rva009A2420CollisionNode *)m_dirty)->getMovementScore(false);
		((BfmeLinkXX *)m_dirty)->bfmeDropXX();
	}

	if (m_root == 0)
		return;

	if (totalScore * 100 <= m_nodeCount * 100 && !m_rebuild)
	{
		for (unsigned int k = 0; k < m_axisCount; ++k)
		{
			Rva009A3AD0Endpoint **head = &m_axisHeads[k];
			Rva009A3AD0Endpoint *cur = (*head)->m_next;
			while (cur != 0)
			{
				if (cur->m_prev->value <= cur->value)
				{
					cur = cur->m_next;
					continue;
				}
				Rva009A3AD0Endpoint *pos = cur;
				while (pos->m_prev != 0 && pos->m_prev->value > cur->value)
				{
					Rva009A3AD0Endpoint *before = pos->m_prev;
					if (before->m_isMax && cur->isMin())
						addOverlap(before->m_node, cur->m_node);
					else if (before->isMin() && cur->m_isMax)
						((Rva009A3540PairOwner *)this)->removePair(
							(Rva009A3540OpaqueOwner *)before->m_node,
							(Rva009A3540OpaqueOwner *)cur->m_node);
					pos = pos->m_prev;
				}

				Rva009A3AD0Endpoint *next = cur->m_next;
				if (cur->m_prev != 0)
					cur->m_prev->m_next = cur->m_next;
				else
					*head = cur->m_next;
				if (cur->m_next != 0)
					cur->m_next->m_prev = cur->m_prev;
				cur->m_prev = 0;
				cur->m_next = 0;

				cur->m_prev = pos->m_prev;
				cur->m_next = pos;
				pos->m_prev = cur;
				if (cur->m_prev != 0)
					cur->m_prev->m_next = cur;
				else
					*head = cur;
				cur = next;
			}
		}
		return;
	}

	m_rebuild = false;
	((Rva009A2A50Table *)((char *)this + 0x18))->recycleBuckets009A2A50();
	((Rva009A2B80Owner *)((char *)this + 0xAE10))->clear();
	for (Rva009A45A0CollisionData *root = m_root; root != 0; root = root->m_rootNext)
		root->m_rva009A3AD0_020 = 0;
	rva009A2750();

	for (unsigned int k = 0; k < m_axisCount; ++k)
	{
		Rva009A45A0CollisionData *open = 0;
		for (Rva009A3AD0Endpoint *cur = m_axisHeads[k]; cur != 0; cur = cur->m_next)
		{
			if (cur->isMin())
			{
				for (Rva009A45A0CollisionData *other = open; other != 0; other = other->m_openNext)
					addOverlap(other, cur->m_node);
				cur->m_node->m_openPrev = &open;
				cur->m_node->m_openNext = open;
				if (cur->m_node->m_openNext != 0)
					cur->m_node->m_openNext->m_openPrev = &cur->m_node->m_openNext;
				open = cur->m_node;
			}
			else
			{
				if (cur->m_node->m_openNext != 0)
					cur->m_node->m_openNext->m_openPrev = cur->m_node->m_openPrev;
				*cur->m_node->m_openPrev = cur->m_node->m_openNext;
				cur->m_node->m_openPrev = 0;
			}
		}
	}
}

// Bottom-up merge sort of one axis's endpoint list. The BFME 1 body at
// 0x009A2750 (460 bytes) and the BFME 2 twin at 0x007586F0 are identical; the
// donor's UpdateSort caller and WorldBuilder's 0x01802EC0 copy establish the
// purpose and layout, while the original method name stays unknown. The two
// left-run count reads use the volatile-qualified accessor to reproduce VC7.1
// register costs; this is a codegen choice, not evidence that the field was
// declared volatile.
struct SortList
{
	Rva009A3AD0Endpoint *head;
	Rva009A3AD0Endpoint *tail;
	unsigned int count;
	unsigned int getCount() const volatile { return count; }
};
typedef Rva009A3AD0Endpoint Endpoint;


void CollisionManagerImpl::rva009A2750()
{
	for (unsigned int k = 0; k < m_axisCount; k++)
	{
		SortList lists[4];
		lists[1].count = 0;
		lists[0].count = 0;
		lists[0].head = 0;
		int i = 0;
		Endpoint *cur = m_axisHeads[k];
		while (cur)
		{
			Endpoint *next = cur->m_next;
			cur->m_next = lists[i].head;
			lists[i].head = cur;
			lists[i].count++;
			i ^= 1;
			cur = next;
		}
		int src = 0;
		unsigned int runLen = 1;
		while (lists[src + 1].count != 0)
		{
			SortList *A = &lists[src];
			SortList *B = &lists[src + 1];

			int out = src ^ 2;
			lists[out + 1].count = 0;
			lists[out].count = 0;
			while (A->getCount() != 0)
			{
				unsigned int b = runLen;
				unsigned int a = runLen;
				SortList *o = &lists[out];
				for (;;)
				{
					SortList *from;
					if (a != 0 && A->getCount() != 0)
					{
						if (b != 0 && B->count != 0 && A->head->value > B->head->value)
						{
							from = B;
							b--;
						}
						else
						{
							from = A;
							a--;
						}
					}
					else if (b != 0 && B->count != 0)
					{
						from = B;
						b--;
					}
					else
						break;
					from->count--;
					Endpoint *e = from->head;
					from->head = e->m_next;
					if (o->count == 0)
					{
						o->head = e;
						o->tail = e;
					}
					else
					{
						o->tail->m_next = e;
						o->tail = e;
					}
					o->count++;
				}
				out ^= 1;
			}
			runLen <<= 1;
			src ^= 2;
		}
		if (lists[src].count > 1)
			lists[src].tail->m_next = 0;
		m_axisHeads[k] = lists[src].head;
		m_axisHeads[k]->m_prev = 0;
		for (Endpoint *p = m_axisHeads[k]; p->m_next != 0; p = p->m_next)
			p->m_next->m_prev = p;
	}
}
