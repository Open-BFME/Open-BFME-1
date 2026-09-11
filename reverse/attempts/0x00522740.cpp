// ?run@ReleaseWindowLayoutShim@@SAXPAVWindowLayout@@@Z
// partial score=0.46 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class WindowLayout;

void ReleaseWindowLayout(WindowLayout *);

class ReleaseWindowLayoutShim
{
public:
    static void run(WindowLayout *layout);
};

void ReleaseWindowLayout(WindowLayout *layout)
{
    ReleaseWindowLayoutShim::run(layout);
}

struct ReferenceCountedReleaseValue
{
    virtual void release(int deletingFlag);
    int referenceCount;
};

struct ReferencePointerAssignmentThunk
{
    ReferenceCountedReleaseValue *value;

    ReferencePointerAssignmentThunk *assign(const ReferencePointerAssignmentThunk *other);
};

struct ReleaseWindowLayoutTempRef
{
    ReferenceCountedReleaseValue *value;

    ReleaseWindowLayoutTempRef() : value(0) { }
    ~ReleaseWindowLayoutTempRef()
    {
        if (value != 0 && --value->referenceCount <= 0)
        {
            value->release(1);
        }
    }
};

struct BfmeOne924G
{
    void bfmeCall924G();
};

struct Rva00579160Manager
{
    unsigned char padding[0x1ae];
    unsigned char flag;
};

class BfmeThingCB
{
public:
    unsigned char padding0[0x34];
    int mode;
    int state;
    ReferencePointerAssignmentThunk current;
    unsigned char padding1[4];
    int index;
    unsigned char padding2;
    unsigned char released;
};

extern BfmeThingCB *g_bfmeThingCB;
extern Rva00579160Manager *Rva00579160TheManager;

void ReleaseWindowLayoutShim::run(WindowLayout *layout)
{
    if (g_bfmeThingCB == 0)
    {
        return;
    }

    if (g_bfmeThingCB->state != 4)
    {
        g_bfmeThingCB->state = 4;
    }

    ReleaseWindowLayoutTempRef temp;
    ReferencePointerAssignmentThunk *slot = &g_bfmeThingCB->current;
    slot->assign(reinterpret_cast<const ReferencePointerAssignmentThunk *>(&temp));

    g_bfmeThingCB->index = -1;

    if (g_bfmeThingCB->mode != 0 && g_bfmeThingCB->mode != 3)
    {
        g_bfmeThingCB->mode = 3;
    }

    if (*reinterpret_cast<unsigned char *>(&layout) != 0)
    {
        g_bfmeThingCB->released = 1;
    }

    if (Rva00579160TheManager != 0 && Rva00579160TheManager->flag == 0)
    {
        reinterpret_cast<BfmeOne924G *>(g_bfmeThingCB)->bfmeCall924G();
    }
}
