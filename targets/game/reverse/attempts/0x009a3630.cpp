// ?unlinkChain@Rva009A36F0Owner@@QAEXPAVRva009A36F0Thing@@@Z
// partial score=0.894737 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc
// Address-derived chain unlinker called from Rva009A36F0Owner::apply.
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
};
class Rva009A36F0Thing
{
public:
    char m_unreconstructed_00[0x20];
    void *m_queueHead;
};
class Rva009A36F0Owner
{
public:
    void unlinkChain(Rva009A36F0Thing *thing);
    char m_unreconstructed_00[0xae04];
    void *m_freeHead;
    char m_unreconstructed_ae08[4];
    void *m_cursor;
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
        node->second.backlink = 0;
        key.m_key1 = node->key1;
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
