// cl: /O2 /Ob2 /GR- /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// BFME addGhostObject, RVA 0x006BD280, 203 bytes. The ZH implementation
// supplies the list operations and DrawableInfo identities; BFME accepts only
// Object*, and pops only the free-list head. No PartitionData argument/store.
// Layout agrees with W3DGhostObjectSetLocalPlayerIndex.cpp and the constructor
// at 0x006BCEC0: snapshots +0x80, DrawableInfo +0x100, links +0x110/+0x114.
// The constructor's hidden virtual-base flag and destructor's three vptrs
// establish the multiple/virtual inheritance ABI used by new below.

class Object;
class W3DGhostObject;
class GhostPrimary { public: virtual ~GhostPrimary(); };
class GhostSecondary { public: virtual ~GhostSecondary(); };
// Opaque interface names: only their ABI is known here. The overridden virtual
// slot makes MSVC reserve the witnessed vtordisp at +0x118, before the virtual
// base vptr at +0x11c. None of these declarations emits a method body.
class GhostVirtualBase { public: virtual void virtualBaseSlot(); };

class GhostObject : public GhostPrimary, public GhostSecondary, public virtual GhostVirtualBase
{
public:
    GhostObject();
    virtual ~GhostObject();
    virtual void virtualBaseSlot();
    Object *m_parentObject;
    char m_basePadding[0x70];
};

struct GhostDrawableInfo
{
    void *m_field0;
    void *m_drawable;
    W3DGhostObject *m_ghostObject;
    void *m_fieldC;
    GhostDrawableInfo() : m_field0(0), m_drawable(0), m_ghostObject(0), m_fieldC(0) {}
};

class W3DGhostObject : public GhostObject
{
public:
    W3DGhostObject();
    virtual ~W3DGhostObject();
    virtual void virtualBaseSlot();
    void *m_parentSnapshots[32];
    GhostDrawableInfo m_drawableInfo;
    W3DGhostObject *m_nextSystem;
    W3DGhostObject *m_prevSystem;
};

W3DGhostObject::W3DGhostObject()
{
    for (int i = 0; i < 32; ++i)
        m_parentSnapshots[i] = 0;
    m_drawableInfo.m_drawable = 0;
    m_drawableInfo.m_fieldC = 0;
    m_drawableInfo.m_ghostObject = 0;
    m_drawableInfo.m_field0 = 0;
    m_nextSystem = 0;
    m_prevSystem = 0;
}

W3DGhostObject::~W3DGhostObject()
{
}

class W3DGhostObjectManager
{
public:
    virtual GhostObject *addGhostObject(Object *object);
    int m_localPlayerIndex;
    bool m_lockGhostObjects;
    bool m_saveLockGhostObjects;
    W3DGhostObject *m_freeModules;
    W3DGhostObject *m_usedModules;
};

GhostObject *W3DGhostObjectManager::addGhostObject(Object *object)
{
    if (m_lockGhostObjects || m_saveLockGhostObjects)
        return 0;
    W3DGhostObject *mod = m_freeModules;
    if (mod)
        m_freeModules = mod->m_nextSystem;
    else
        mod = new W3DGhostObject;
    mod->m_prevSystem = 0;
    mod->m_nextSystem = m_usedModules;
    if (m_usedModules)
        m_usedModules->m_prevSystem = mod;
    m_usedModules = mod;
    mod->m_parentObject = object;
    mod->m_drawableInfo.m_drawable = 0;
    mod->m_drawableInfo.m_ghostObject = mod;
    return mod;
}
