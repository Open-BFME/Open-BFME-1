// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

class RenderObjClass;

struct BfmeSceneListNode
{
    void *prev;
    void *next;
    void *next_list;
    void *object_link;
    void *list;
};

class BfmeRefSceneList
{
public:
    virtual ~BfmeRefSceneList();
    BfmeSceneListNode head;

    RenderObjClass *Peek_Head()
    {
        BfmeSceneListNode *node = (BfmeSceneListNode *)head.next;
        if (node == &head || node->object_link == 0)
            return 0;
        return (RenderObjClass *)((char *)node->object_link - 8);
    }
};

class BfmeNonRefSceneList
{
public:
    virtual ~BfmeNonRefSceneList();
    BfmeSceneListNode head;
};

class BfmeSceneVectorElement
{
public:
    ~BfmeSceneVectorElement();
    static void operator delete[](void *ptr);
    unsigned char pad[0x1c];
};

class BfmeSceneVector
{
public:
    void release_vector()
    {
        if (vector)
            delete[] vector;
    }

    ~BfmeSceneVector()
    {
        release_vector();
    }

    void *unused;
    BfmeSceneVectorElement *vector;
    int vector_max;
    int active_count;
};

class BfmeSceneBase
{
public:
    virtual ~BfmeSceneBase() {}
    int ref_count;
};

class SimpleSceneClass : public BfmeSceneBase
{
public:
    virtual ~SimpleSceneClass();
    virtual void slot_1();
    virtual void Add_Render_Object(RenderObjClass *obj);
    virtual void Remove_Render_Object(RenderObjClass *obj);

private:
    void remove_all_render_objects()
    {
        RenderObjClass *obj;
        while ((obj = render_list.Peek_Head()) != 0)
            Remove_Render_Object(obj);
    }

    unsigned char pad_to_vector[0x40];
    BfmeSceneVector scene_vector;
    unsigned char pad_to_render_list[4];
    BfmeRefSceneList render_list;
    BfmeRefSceneList update_list;
    BfmeRefSceneList light_list;
    BfmeRefSceneList release_list;
    BfmeNonRefSceneList list_bc;
    BfmeNonRefSceneList list_d4;
    BfmeRefSceneList visible_list;
};

SimpleSceneClass::~SimpleSceneClass()
{
    remove_all_render_objects();
}

#pragma comment(linker, "/alternatename:??1BfmeRefSceneList@@UAE@XZ=?j_000319df@@YAXXZ")
#pragma comment(linker, "/alternatename:??1BfmeNonRefSceneList@@UAE@XZ=??1?$MultiListClass@VDX8TextureCategoryClass@@@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1BfmeSceneVectorElement@@QAE@XZ=?invoke@Rva00943970@@QAEXXZ")
