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

class Rva009A45A0CollisionData
{
public:
	~Rva009A45A0CollisionData();
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
