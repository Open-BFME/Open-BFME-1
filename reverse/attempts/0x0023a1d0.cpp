// ?dispatchMissing@BfmeMissingObjectDispatch@@QAEXPAX0@Z
// partial score=0.92 date=2026-09-11
// Identity: list head at this-0xAC, dispatch tree at this+0x30 (sentinel==tree
// header), object id at +0x74, dispatch interface at +0x204, virtual slot 120.

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

        if (found != (BfmeDispatchTreeNode *)tree && key < found->key)
        {
            found = (BfmeDispatchTreeNode *)tree;
        }

        BfmeDispatchInterface *dispatch = object->dispatch;
        if (found == (BfmeDispatchTreeNode *)*(BfmeDispatchTree *volatile *)((char *)this + 0x30) && dispatch != 0)
        {
            void **vtable = *(void ***)dispatch;
            BfmeDispatchMethod method = *(BfmeDispatchMethod *)&vtable[120];
            (dispatch->*method)(first, second);
        }
    }
}
