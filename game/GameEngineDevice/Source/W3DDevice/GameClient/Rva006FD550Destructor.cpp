// cl: /DNDEBUG /MD /EHsc /O2
// Retail body at 0x006FD550, 294 bytes: the base (non-deleting) destructor
// for the class that installs the 29-slot table 0x011207C0 (constructor at
// 0x006FC970, slot-8 body at 0x006FD090 -- Rva006FD090Projection.cpp, whose
// m_renderObject lives at +0x6C of the same object). Reached only from the
// scalar deleting destructor ??_GGen_dtor_006FE570 through slot 0 of the
// same table.
//
// The body first delegates to the already-landed
// Rva006FCE40Owner::releaseInterfaces (thunk j_00048b67 -> retail 0x006FCE40)
// on the very same `this`, then conditionally unregisters three more
// scene-tracked resources at +0x78, +0x7C and +0x80 through the scene
// pointer at +0x74 (vtable slot 3, matching the already-proven
// Rva006FCE40SceneView::remove_resource shape), gated by a per-resource
// query at vtable slot 0x1E8/4=122. It then uniformly releases five
// refcounted members at +0x70, +0x74, +0x78, +0x7C and +0x80 through the
// shared RefCountClass ABI (Delete_This at vtable slot zero, refcount at
// +4), and finally forwards to the base-class destructor through thunk
// j_00011356 (-> pinned dump 0x00609E30).
//
// The address-derived class name records the body identity without
// claiming a semantic class name the retail image does not independently
// prove.

extern void j_00048b67();
extern void j_00011356();

class Rva006FD550RefCounted
{
public:
    virtual void deleteThis();

    void release()
    {
        if (--m_refs == 0)
            deleteThis();
    }

private:
    int m_refs;
};

#define D_SLOT(n) virtual void d##n();

class Rva006FD550ResourceQuery
{
public:
    D_SLOT(000) D_SLOT(001) D_SLOT(002) D_SLOT(003) D_SLOT(004) D_SLOT(005) D_SLOT(006) D_SLOT(007)
    D_SLOT(008) D_SLOT(009) D_SLOT(010) D_SLOT(011) D_SLOT(012) D_SLOT(013) D_SLOT(014) D_SLOT(015)
    D_SLOT(016) D_SLOT(017) D_SLOT(018) D_SLOT(019) D_SLOT(020) D_SLOT(021) D_SLOT(022) D_SLOT(023)
    D_SLOT(024) D_SLOT(025) D_SLOT(026) D_SLOT(027) D_SLOT(028) D_SLOT(029) D_SLOT(030) D_SLOT(031)
    D_SLOT(032) D_SLOT(033) D_SLOT(034) D_SLOT(035) D_SLOT(036) D_SLOT(037) D_SLOT(038) D_SLOT(039)
    D_SLOT(040) D_SLOT(041) D_SLOT(042) D_SLOT(043) D_SLOT(044) D_SLOT(045) D_SLOT(046) D_SLOT(047)
    D_SLOT(048) D_SLOT(049) D_SLOT(050) D_SLOT(051) D_SLOT(052) D_SLOT(053) D_SLOT(054) D_SLOT(055)
    D_SLOT(056) D_SLOT(057) D_SLOT(058) D_SLOT(059) D_SLOT(060) D_SLOT(061) D_SLOT(062) D_SLOT(063)
    D_SLOT(064) D_SLOT(065) D_SLOT(066) D_SLOT(067) D_SLOT(068) D_SLOT(069) D_SLOT(070) D_SLOT(071)
    D_SLOT(072) D_SLOT(073) D_SLOT(074) D_SLOT(075) D_SLOT(076) D_SLOT(077) D_SLOT(078) D_SLOT(079)
    D_SLOT(080) D_SLOT(081) D_SLOT(082) D_SLOT(083) D_SLOT(084) D_SLOT(085) D_SLOT(086) D_SLOT(087)
    D_SLOT(088) D_SLOT(089) D_SLOT(090) D_SLOT(091) D_SLOT(092) D_SLOT(093) D_SLOT(094) D_SLOT(095)
    D_SLOT(096) D_SLOT(097) D_SLOT(098) D_SLOT(099) D_SLOT(100) D_SLOT(101) D_SLOT(102) D_SLOT(103)
    D_SLOT(104) D_SLOT(105) D_SLOT(106) D_SLOT(107) D_SLOT(108) D_SLOT(109) D_SLOT(110) D_SLOT(111)
    D_SLOT(112) D_SLOT(113) D_SLOT(114) D_SLOT(115) D_SLOT(116) D_SLOT(117) D_SLOT(118) D_SLOT(119)
    D_SLOT(120) D_SLOT(121)
    virtual bool slot122();
};

#undef D_SLOT

class Rva006FD550Scene
{
public:
    virtual void d000();
    virtual void d001();
    virtual void d002();
    virtual void remove_resource(Rva006FD550ResourceQuery *resource);
};

static void callReleaseInterfaces(void *self)
{
    struct Thunk { void call(); };
    typedef void (Thunk::*Function)();
    union { void (*raw)(); Function member; } function;
    function.raw = j_00048b67;
    (reinterpret_cast<Thunk *>(self)->*function.member)();
}

static void callBaseDtor(void *self)
{
    struct Thunk { void call(); };
    typedef void (Thunk::*Function)();
    union { void (*raw)(); Function member; } function;
    function.raw = j_00011356;
    (reinterpret_cast<Thunk *>(self)->*function.member)();
}

class Rva006FD550
{
public:
    void destruct();
};

struct Rva006FD550BaseDtorGuard
{
    void *m_self;
    Rva006FD550BaseDtorGuard(void *self) : m_self(self)
    {
        *(unsigned int *)self = 0x011207C0u;
    }
    ~Rva006FD550BaseDtorGuard() { callBaseDtor(m_self); }
};

void Rva006FD550::destruct()
{
    char *self = (char *)this;
    Rva006FD550BaseDtorGuard baseGuard(this);

    callReleaseInterfaces(this);

    Rva006FD550ResourceQuery **res78 = (Rva006FD550ResourceQuery **)(self + 0x78);
    Rva006FD550Scene **scene = (Rva006FD550Scene **)(self + 0x74);
    if (*res78 != 0 && *scene != 0 && (*res78)->slot122())
        (*scene)->remove_resource(*res78);

    Rva006FD550ResourceQuery **res7c = (Rva006FD550ResourceQuery **)(self + 0x7c);
    if (*res7c != 0 && *scene != 0 && (*res7c)->slot122())
        (*scene)->remove_resource(*res7c);

    Rva006FD550ResourceQuery **res80 = (Rva006FD550ResourceQuery **)(self + 0x80);
    if (*res80 != 0 && *scene != 0 && (*res80)->slot122())
        (*scene)->remove_resource(*res80);

    Rva006FD550RefCounted **res70 = (Rva006FD550RefCounted **)(self + 0x70);
    if (*res70 != 0)
    {
        (*res70)->release();
        *res70 = 0;
    }

    Rva006FD550RefCounted **sceneRc = (Rva006FD550RefCounted **)(self + 0x74);
    if (*sceneRc != 0)
    {
        (*sceneRc)->release();
        *sceneRc = 0;
    }

    Rva006FD550RefCounted **res78Rc = (Rva006FD550RefCounted **)(self + 0x78);
    if (*res78Rc != 0)
    {
        (*res78Rc)->release();
        *res78Rc = 0;
    }

    Rva006FD550RefCounted **res7cRc = (Rva006FD550RefCounted **)(self + 0x7c);
    if (*res7cRc != 0)
    {
        (*res7cRc)->release();
        *res7cRc = 0;
    }

    Rva006FD550RefCounted **res80Rc = (Rva006FD550RefCounted **)(self + 0x80);
    if (*res80Rc != 0)
    {
        (*res80Rc)->release();
        *res80Rc = 0;
    }
}
