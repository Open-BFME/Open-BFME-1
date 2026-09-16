// Retail 0x0023A1D0, 116 bytes.
// The method scans the containment list, searches the dispatch tree, and calls
// virtual slot 120 when the object ID has no tree entry.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct BfmeDispatchInterface
{
};

typedef void (BfmeDispatchInterface::*BfmeDispatchMethod)(void *, void *);

struct BfmeDispatchObject
{
    unsigned char unknown_0000[0x74];
    int id;
    unsigned char unknown_0078[0x18c];
    BfmeDispatchInterface *dispatch;
};

struct BfmeDispatchListNode
{
    BfmeDispatchListNode *next;
    BfmeDispatchListNode *previous;
    BfmeDispatchObject *object;
};

struct BfmeDispatchTreeNode
{
    unsigned char unknown_0000[4];
    BfmeDispatchTreeNode *child_a;
    BfmeDispatchTreeNode *child_b;
    BfmeDispatchTreeNode *child_c;
    int key;
};

struct BfmeDispatchTree
{
    unsigned char unknown_0000[4];
    BfmeDispatchTreeNode *root;
};

struct BfmeMissingObjectDispatch
{
    void dispatchMissing(void *first, void *second);
};

void BfmeMissingObjectDispatch::dispatchMissing(void *first, void *second)
{
    BfmeDispatchListNode *node = (*(BfmeDispatchListNode **)((char *)this - 0xac))->next;

    while (node != *(BfmeDispatchListNode **)((char *)this - 0xac))
    {
        BfmeDispatchObject *object = node->object;
        BfmeDispatchTree *tree = *(BfmeDispatchTree **)((char *)this + 0x30);
        BfmeDispatchTreeNode *cursor = tree->root;
        node = node->next;
        int key = object->id;
        BfmeDispatchTreeNode *found = (BfmeDispatchTreeNode *)tree;

        while (cursor != 0)
        {
            if (cursor->key >= key)
            {
                found = cursor;
                cursor = cursor->child_b;
            }
            else
            {
                cursor = cursor->child_c;
            }
        }

        _ReadWriteBarrier();

        if (found == (BfmeDispatchTreeNode *)tree)
            goto reset;
        if (key >= found->key)
            goto dispatch;
reset:
        found = (BfmeDispatchTreeNode *)tree;
dispatch:

        if (found == (BfmeDispatchTreeNode *)*(BfmeDispatchTree *volatile *)((char *)this + 0x30))
        {
            BfmeDispatchInterface *dispatch = object->dispatch;
            if (dispatch == 0)
                continue;

            void **vtable = *(void ***)dispatch;
            BfmeDispatchMethod method = *(BfmeDispatchMethod *)&vtable[120];
            (dispatch->*method)(first, second);
        }
    }
}
