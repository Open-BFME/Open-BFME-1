// ??0Rva00700030@@QAE@XZ
// partial score=0.30 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc /O2
// Retail body at 0x00700030, 329 bytes: the constructor counterpart to the
// already-landed Rva006FD550::destruct base destructor
// (Code/GameEngineDevice/Source/W3DDevice/GameClient/Rva006FD550Destructor.cpp),
// which releases the SAME five refcounted members this body allocates at
// +0x70 (CameraClass), +0x74 (the class installing vtable 0x01120850 --
// pinned dump ctor 0x00944940), +0x78/+0x7C/+0x80 (LightClass), matching
// sizes 0x3C0/0x108/0x124/0x124/0x124.  The address-derived class name
// records the body identity without claiming a semantic class name the
// retail image does not independently prove.

class CameraClass
{
public:
    CameraClass();

private:
    unsigned char m_opaque[0x3c0];
};

class GenBase00944940
{
public:
    GenBase00944940();

private:
    unsigned char m_opaque[0x108];
};

enum LightType
{
    LIGHT_TYPE_POINT = 1
};

class LightClass
{
public:
    LightClass(LightType type);

private:
    unsigned char m_opaque[0x124];
};

extern void j_00048b67();
extern void j_000460a1();
extern void j_0003d01e();

static void callFirstInterfaceStep(void *self)
{
    struct Thunk { void call(); };
    typedef void (Thunk::*Function)();
    union { void (*raw)(); Function member; } function;
    function.raw = j_00048b67;
    (reinterpret_cast<Thunk *>(self)->*function.member)();
}

static void callLastStepA(void *self)
{
    struct Thunk { void call(); };
    typedef void (Thunk::*Function)();
    union { void (*raw)(); Function member; } function;
    function.raw = j_000460a1;
    (reinterpret_cast<Thunk *>(self)->*function.member)();
}

static void callLastStepB(void *self)
{
    struct Thunk { void call(); };
    typedef void (Thunk::*Function)();
    union { void (*raw)(); Function member; } function;
    function.raw = j_0003d01e;
    (reinterpret_cast<Thunk *>(self)->*function.member)();
}

class Rva00700030
{
public:
    Rva00700030();

private:
    unsigned char m_pad000[0x70];
    CameraClass *m_camera;
    GenBase00944940 *m_gen74;
    LightClass *m_light78;
    LightClass *m_light7c;
    LightClass *m_light80;
    unsigned char m_pad084[0xe4 - 0x84];
    float m_ze4;
};

Rva00700030::Rva00700030()
{
    callFirstInterfaceStep(this);

    m_camera = new CameraClass();

    m_gen74 = new GenBase00944940();
    if (m_gen74 != 0)
        *(unsigned int *)m_gen74 = 0x01120850u;

    m_light78 = new LightClass(LIGHT_TYPE_POINT);
    m_light7c = new LightClass(LIGHT_TYPE_POINT);
    m_light80 = new LightClass(LIGHT_TYPE_POINT);

    m_ze4 = 1.0f;

    callLastStepA(this);
    callLastStepB(this);
}
