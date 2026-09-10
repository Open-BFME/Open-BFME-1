// ?rva006EBC30@W3DDisplay@@QAEXH@Z
// partial score=0.86 date=2026-09-10
// cl: /O2 /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib

// Retail 0x006EBC30 is the complete 192-byte body in slot 37 of the
// W3DDisplay vtable at 0x0111EDD0.  W3DGameClient::setTimeOfDay reaches that
// slot through [Display vptr+0x94].  The retail slot is retained under an
// address-derived name because the BFME body uses a different lighting layout
// from the older W3DDisplay source spelling.

#include "vector3.h"
#include "matrix3d.h"

typedef int Int;

struct RGBColor
{
    float red;
    float green;
    float blue;
};

struct Coord3D
{
    float x;
    float y;
    float z;
};

struct TerrainLighting
{
    RGBColor ambient;
    RGBColor diffuse;
    Coord3D lightPos;
};

class LightClass
{
public:
    virtual void unused00();
    virtual void unused01();
    virtual void unused02();
    virtual void unused03();
    virtual void unused04();
    virtual void unused05();
    virtual void unused06();
    virtual void unused07();
    virtual void unused08();
    virtual void unused09();
    virtual void unused10();
    virtual void unused11();
    virtual void unused12();
    virtual void unused13();
    virtual void unused14();
    virtual void unused15();
    virtual void unused16();
    virtual void unused17();
    virtual void unused18();
    virtual void unused19();
    virtual void unused20();
    virtual void Set_Transform(const Matrix3D &value);

    void Set_Ambient(const Vector3 &value) { ambient = value; }
    void Set_Diffuse(const Vector3 &value) { diffuse = value; }
    void Set_Specular(const Vector3 &value) { specular = value; }

private:
    unsigned char padding[0xd8 - 4];
    Vector3 ambient;
    Vector3 diffuse;
    Vector3 specular;
};

static void updateLights(const TerrainLighting *ol, LightClass **myLight)
{
    Int i = 0;
    while (i < 4)
    {
        if (myLight[i])
        {
            myLight[i]->Set_Ambient(Vector3(0.0f, 0.0f, 0.0f));
            myLight[i]->Set_Diffuse(Vector3(ol->diffuse.red, ol->diffuse.green, ol->diffuse.blue));
            myLight[i]->Set_Specular(Vector3(0, 0, 0));

            Matrix3D mtx;
            mtx.Set(Vector3(1, 0, 0), Vector3(0, 1, 0),
                Vector3(ol->lightPos.x, ol->lightPos.y, ol->lightPos.z),
                Vector3(0, 0, 0));
            myLight[i]->Set_Transform(mtx);
        }
        ++i;
        ++ol;
    }
}

class BfmeGlobPB
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void Set_Ambient_Light(const Vector3 &value);

private:
    unsigned char m_padding04[0x140 - 4];

public:
    Vector3 m_ambient;
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;
extern BfmeGlobPB *g_bfmeGlobPB;

struct TimeOfDayLighting
{
    unsigned char data[0x6c];
};

class BfmeA1087
{
};
extern BfmeA1087 *g_bfmeA1087;

class DX8Wrapper
{
public:
    static int Owns_Device_Lock(void);
};

class View
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void forceRedraw();
};

extern View *TheTacticalView;

// Incremental-link thunk used by the retail terrain virtual-zero forwarder.
extern void j_00040bc9();

class W3DDisplay
{
public:
    void rva006EBC30(Int tod);

private:
    unsigned char m_padding04[0x144];
    LightClass *m_myLight[4];
    LightClass *m_myLightSecond[4];
};

void W3DDisplay::rva006EBC30(Int tod)
{
    TimeOfDayLighting *timeOfDay = reinterpret_cast<TimeOfDayLighting *>(TheWritableGlobalData);
    const char *lighting = reinterpret_cast<const char *>(timeOfDay[tod].data);
    const TerrainLighting *first = reinterpret_cast<const TerrainLighting *>(lighting + 0x4ac);
    const TerrainLighting *second = reinterpret_cast<const TerrainLighting *>(lighting + 0x734);

    if (g_bfmeGlobPB)
    {
        {
            Vector3 ambient(first->ambient.red, first->ambient.green, first->ambient.blue);
            g_bfmeGlobPB->Set_Ambient_Light(ambient);
        }
        g_bfmeGlobPB->m_ambient = Vector3(second->ambient.red, second->ambient.green, second->ambient.blue);
    }

    updateLights(first, m_myLight);
    updateLights(second, m_myLightSecond);

    if (g_bfmeA1087)
    {
        typedef void (BfmeA1087::*J00040bc9Member)(Int value);
        union
        {
            void (__cdecl *freeFunction)();
            J00040bc9Member memberFunction;
        } call;
        call.freeFunction = ::j_00040bc9;
        (g_bfmeA1087->*call.memberFunction)(*reinterpret_cast<const Int *>(&first->ambient.red));
        if (DX8Wrapper::Owns_Device_Lock())
            TheTacticalView->forceRedraw();
    }
}
