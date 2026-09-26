// ?initialize@Rva00700030@@QAEXXZ
// cl: /DNDEBUG /MD /EHsc /O2 /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Include
// The scene subobject at +0x74 installs vtable 0x01120850 after its base constructor.

#include "camera.h"
#include "light.h"
#include "scene.h"

typedef char CameraSizeCheck[(sizeof(CameraClass) == 0x3c0) ? 1 : -1];
typedef char LightSizeCheck[(sizeof(LightClass) == 0x124) ? 1 : -1];

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

class __declspec(novtable) SimpleSceneDerived00700030 : public SimpleSceneClass
{
public:
    // ??0SimpleSceneDerived00700030@@QAE@XZ absent-from-retail
    SimpleSceneDerived00700030() { *(unsigned int *)this = 0x01120850u; }
private:
    unsigned char m_bfmeTail[0x108 - sizeof(SimpleSceneClass)];
};
typedef char SceneSizeCheck[(sizeof(SimpleSceneDerived00700030) == 0x108) ? 1 : -1];

class Rva00700030
{
public:
    void initialize();

private:
    unsigned char m_pad000[0x70];
    CameraClass *m_camera;
    SimpleSceneDerived00700030 *m_scene;
    LightClass *m_light78;
    LightClass *m_light7c;
    LightClass *m_light80;
    unsigned char m_pad084[0xe4 - 0x84];
    float m_ze4;
};

void Rva00700030::initialize()
{
    callFirstInterfaceStep(this);

    m_camera = new CameraClass();

    m_scene = new SimpleSceneDerived00700030();

    m_light78 = new LightClass(LightClass::DIRECTIONAL);
    m_light7c = new LightClass(LightClass::DIRECTIONAL);
    m_light80 = new LightClass(LightClass::DIRECTIONAL);

    m_ze4 = 1.0f;

    callLastStepA(this);
    callLastStepB(this);
}


