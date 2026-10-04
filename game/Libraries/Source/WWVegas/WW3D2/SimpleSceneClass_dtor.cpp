// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep

// list_bc/list_d4 are retail's MultiListClass<DX8TextureCategoryClass> members:
// naming the real template here lets the compiler emit calls to its own
// destructor (0x009435A0) directly, so no linker alias is needed for them.
#include "../WWLib/multilist.h"

class DX8TextureCategoryClass;

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
    MultiListClass<DX8TextureCategoryClass> list_bc;
    MultiListClass<DX8TextureCategoryClass> list_d4;
    BfmeRefSceneList visible_list;
};

SimpleSceneClass::~SimpleSceneClass()
{
    remove_all_render_objects();
}

// The five BfmeRefSceneList destructor call sites are compiler-generated
// implicit destructor calls, each preceded by the /EHsc destructor-state byte
// written into the SEH record's state slot (`mov byte ptr [esp+0x18], N`) plus
// the `push ebx` frame the state tracking needs.  A hand-written call to the
// thunk loses both, so this alias cannot be replaced by a member-pointer call.
#pragma comment(linker, "/alternatename:??1BfmeRefSceneList@@UAE@XZ=?j_000319df@@YAXXZ")
// Same for the element destructor address that `delete[]` passes to the MSVC
// CRT array-destruction helper ??_M@YGXPAXIHP6EX0@Z@Z: the compiler always
// pushes that class's own ??1 name, never a plain member function such as
// ?invoke@Rva00943970@@QAEXXZ, so no C++ spelling resolves it to the thunk.
#pragma comment(linker, "/alternatename:??1BfmeSceneVectorElement@@QAE@XZ=?invoke@Rva00943970@@QAEXXZ")
