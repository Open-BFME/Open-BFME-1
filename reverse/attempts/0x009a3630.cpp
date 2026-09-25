// ?unlinkChain@Rva009A36F0Owner@@QAEXPAVRva009A36F0Thing@@@Z
// partial score=0.878947 date=2026-09-25
// cl: /DNDEBUG /MD /EHsc
//
// Retail RVA 0x009A3630 (190 bytes). Pinned identity (reverse/symbols.csv):
// ?unlinkChain@Rva009A36F0Owner@@QAEXPAVRva009A36F0Thing@@@Z -- address-derived
// direct pin for the still-dump chain-unlinker Rva009A36F0Owner::apply calls
// in its else branch (Code/GameEngine/Source/Common/Rva009A36F0Owner.cpp).
//
// thing->+0x20 is the head of a work queue of anchor records; each anchor's
// +8 gives the payload node to detach.  Per node, retail unlinks it from two
// intrusive backlink/next lists (+0x14/+0x18 and +0x20/+0x24, same
// pointer-to-pointer backlink idiom as the landed
// Rva009A3300HashTableRemove.cpp), removes it from the 0x493-bucket hash
// table keyed by its own +8/+0xc fields, then unlinks it from a THIRD
// backlink/next list at +0x2c/+0x30 -- this one belongs to Owner itself
// (freeHead at +0xae04, cursor at +0xae0c, both ahead of the embedded hash
// table at +0xae10) -- and finally pushes the node onto Owner's free list.

// pinned callee: ?remove@Rva009A3300HashTable@@QAEXPAURva009A3300Node@@@Z
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
	void remove( Rva009A3300Node *entry );
};

class Rva009A36F0Thing
{
public:
	char m_unreconstructed_00[0x20];
	void *m_queueHead;          // +0x20
};

class Rva009A36F0Owner
{
public:
	void unlinkChain( Rva009A36F0Thing *thing );

	char m_unreconstructed_00[0xae04];
	void *m_freeHead;                    // +0xae04
	char m_unreconstructed_ae08[4];
	void *m_cursor;                       // +0xae0c
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
        Rva009A3300Node key;
        key.m_key0 = node->key0;
        key.m_key1 = node->key1;
        node->second.backlink = 0;
        ((Rva009A3300HashTable *)((char *)this + 0xae10))->remove(&key);
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
