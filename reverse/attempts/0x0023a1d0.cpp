// ?d_0023a1d0@@YAXXZ
// partial score=0.55 date=2026-09-02
// Recovered from retail code at 0x0063A1D0.

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
        BfmeDispatchTreeNode *sentinel = (BfmeDispatchTreeNode *)tree;
        BfmeDispatchTreeNode *cursor = tree->root;
        BfmeDispatchTreeNode *found = sentinel;
        int key = object->id;
        node = node->next;

        while (cursor != 0)
        {
            if (cursor->key < key)
            {
                found = cursor;
                cursor = cursor->child_b;
            }
            else
            {
                cursor = cursor->child_c;
            }
        }

        if (found != sentinel && key < found->key)
        {
            found = sentinel;
        }

        if (found == sentinel && object->dispatch != 0)
        {
            void **vtable = *(void ***)object->dispatch;
            BfmeDispatchMethod method = *(BfmeDispatchMethod *)&vtable[120];
            (object->dispatch->*method)(first, second);
        }
    }
}
