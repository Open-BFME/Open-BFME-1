// Address-derived identity: a two-key decrement/removal operation. The owning
// class is unknown; the verified layout is represented by explicit offsets.
struct Rva009A3540PairNode
{
    struct Link
    {
        Link **backlink;
        Link *next;

    };

    unsigned char pad00[8];
    unsigned int key0;
    unsigned int key1;
    unsigned int counter;
    Link link14;
    unsigned int pad1c;
    Link link20;
    unsigned char pad28[8];
    Rva009A3540PairNode *next;
};
struct Rva009A3300Node;
class Rva009A3300HashTable
{
public:
    void remove(Rva009A3300Node *entry);
};
struct BfmeHolderZT;
struct BfmeNodeZT
{
    unsigned char head[0x2c];
    BfmeHolderZT *before;
    BfmeNodeZT *after;
};
class BfmeListZT
{
public:
    void bfmeFreeZT(BfmeNodeZT *node);
};
struct Rva009A3540OpaqueOwner
{
    unsigned char pad00[0x18];
    Rva009A3540PairNode *buckets[0x2b7b];
};

class Rva009A3540PairOwner
{
public:
    void removePair(Rva009A3540OpaqueOwner *a, Rva009A3540OpaqueOwner *b);
};

void Rva009A3540PairOwner::removePair(Rva009A3540OpaqueOwner *a,
                                      Rva009A3540OpaqueOwner *b)
{
    unsigned int aGroup = *(unsigned int *)((char *)a + 0xa0);
    if (aGroup != 0 &&
        aGroup == *(unsigned int *)((char *)b + 0xa0))
        return;

    if (*(unsigned int *)((char *)a + 0x9c) >
        *(unsigned int *)((char *)b + 0x9c))
    {
        Rva009A3540OpaqueOwner *swap = a;
        a = b;
        b = swap;
    }
    unsigned int aId = *(unsigned int *)((char *)a + 0x9c);
    unsigned int bId = *(unsigned int *)((char *)b + 0x9c);

    unsigned int hash = (aId << 16) + bId;
    unsigned int bucket = hash % 0x2b7b;
    Rva009A3540PairNode *node = ((Rva009A3540PairNode **)((char *)this + 0x18))[bucket];
    while (node != 0 && (node->key0 != aId || node->key1 != bId))
        node = *(Rva009A3540PairNode **)((char *)node + 0x30);
    if (node == 0)
        return;

    if (node->counter == *(unsigned int *)((char *)this + 0xc068))
    {
        unsigned char keyRecord[44];
        *(unsigned int *)(keyRecord + 8) = aId;
        *(unsigned int *)(keyRecord + 0xc) = bId;
        ((Rva009A3300HashTable *)((char *)this + 0xae10))->remove(
            (Rva009A3300Node *)keyRecord);
    }

    --node->counter;
    if (node->counter != 0)
        return;

    if (node->link14.next)
        node->link14.next->backlink = node->link14.backlink;
    *node->link14.backlink = node->link14.next;
    // Capture the second link before clearing the first, as in retail.
    Rva009A3540PairNode::Link *next = node->link20.next;
    node->link14.backlink = 0;
    if (next)
        next->backlink = node->link20.backlink;
    *node->link20.backlink = node->link20.next;
    node->link20.backlink = 0;
    ((BfmeListZT *)((char *)this + 0x18))->bfmeFreeZT((BfmeNodeZT *)node);
}
