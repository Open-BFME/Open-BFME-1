// ?insert@Rva009A3960PairTable@@QAEXPAURva009A3960PairOwner@@0@Z
// partial score=0.14876 date=2026-09-25
// Address-derived identity: pair-key hash insertion at 0x009A3960.
extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
void *__cdecl operator new(unsigned int);

struct Rva009A3960PairOwner;
struct Rva009A3960PairNode
{
    unsigned char record00[0x14];
    struct Link { Link **backlink; Link *next; } link14;
    Rva009A3960PairNode *self1c;
    Link link20;
    Rva009A3960PairNode *self28;
    Rva009A3960PairNode **backlink2c;
    Rva009A3960PairNode *next30;
};

class Rva009A3960PairTable
{
public:
    void insert(Rva009A3960PairOwner *, Rva009A3960PairOwner *);
};

struct Rva009A3960PairOwner
{
    unsigned char pad00[0x18];
    Rva009A3960PairNode *buckets[0x2b7b];
};

struct Rva009A3770Node;
class Rva009A3770HashTable
{
public:
    Rva009A3770Node *insert(Rva009A3770Node *);
};

struct Rva009A3960PairKeyRecord
{
    Rva009A3960PairOwner *first;
    Rva009A3960PairOwner *second;
    unsigned int key0;
    unsigned int key1;
    unsigned int count;
    unsigned char rest[0x18];
};

struct Rva009A3770Node
{
    unsigned char bytes[0x2c];
};

void Rva009A3960PairTable::insert(
    Rva009A3960PairOwner *a, Rva009A3960PairOwner *b)
{
    unsigned int group = *(unsigned int *)((char *)a + 0xa0);
    if (group != 0 && group == *(unsigned int *)((char *)b + 0xa0))
        return;

    if (*(unsigned int *)((char *)a + 0x9c) >
        *(unsigned int *)((char *)b + 0x9c))
    {
        Rva009A3960PairOwner *tmp = a;
        a = b;
        b = tmp;
    }

    unsigned int key0 = *(unsigned int *)((char *)a + 0x9c);
    unsigned int key1 = *(unsigned int *)((char *)b + 0x9c);
    unsigned int h = (key0 << 16) + key1;
    unsigned int bucket = h % 0x2b7b;
    Rva009A3960PairKeyRecord record;
    record.key0 = key0;
    record.key1 = key1;
    Rva009A3960PairNode *node = ((Rva009A3960PairNode **)((char *)this + 0x18))[bucket];
    while (node != 0 && (*(unsigned int *)((char *)node + 8) != key0 ||
                         *(unsigned int *)((char *)node + 0xc) != key1))
        node = *(Rva009A3960PairNode **)((char *)node + 0x30);

    if (node == 0)
    {

    record.first = a;
    record.second = b;
    record.key0 = key0;
    record.key1 = key1;
    record.count = 1;
    Rva009A3960PairNode *freeNode = *(Rva009A3960PairNode **)((char *)this + 0xae04);
    if (freeNode != 0)
        *(Rva009A3960PairNode **)((char *)this + 0xae04) = freeNode->next30;
    else
        freeNode = (Rva009A3960PairNode *)operator new(0x34);
    memcpy(freeNode, &record, 0x2c);

    Rva009A3960PairNode **bucketSlot =
        (Rva009A3960PairNode **)((char *)this + 0x18 + bucket * 4);
    freeNode->backlink2c = (Rva009A3960PairNode **)bucketSlot;
    Rva009A3960PairNode *head = *bucketSlot;
    freeNode->next30 = head;
    if (head != 0)
        head->backlink2c = (Rva009A3960PairNode **)&freeNode->next30;
    *bucketSlot = freeNode;

    Rva009A3960PairNode::Link **headA =
        (Rva009A3960PairNode::Link **)((char *)a + 0x20);
    freeNode->link14.backlink = headA;
    Rva009A3960PairNode::Link *nextA = *headA;
    freeNode->link14.next = nextA;
    if (nextA != 0)
        nextA->backlink = &freeNode->link14.next;
    *headA = &freeNode->link14;

    Rva009A3960PairNode::Link **headB =
        (Rva009A3960PairNode::Link **)((char *)b + 0x20);
    freeNode->link20.backlink = headB;
    Rva009A3960PairNode::Link *nextB = *headB;
    freeNode->link20.next = nextB;
    if (nextB != 0)
        nextB->backlink = &freeNode->link20.next;
    *headB = &freeNode->link20;
    freeNode->self28 = freeNode;
    freeNode->self1c = freeNode;
    }
    else
    {

        ++*(unsigned int *)((char *)node + 0x10);
        if (*(unsigned int *)((char *)node + 0x10) ==
            *(unsigned int *)((char *)this + 0xc068))
        {
            record.first = a;
            record.second = b;
            record.key0 = key0;
            record.key1 = key1;
            record.count = 0;
            ((Rva009A3770HashTable *)((char *)this + 0xae10))->insert(
                (Rva009A3770Node *)&record);
        }
    }
}
