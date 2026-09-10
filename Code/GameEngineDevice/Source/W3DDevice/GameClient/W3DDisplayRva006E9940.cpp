// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib

// Retail 0x006E9940 is the complete 183-byte body reached by slot 39
// (+0x9c) of the W3DDisplay vtable at 0x0111EDD0.  The constructor at
// 0x006EF850 installs that table and its slot's incremental-link thunk at
// 0x0001D70A routes to this body.  The source-level operation name is not
// proven, so the W3DDisplay identity remains address-derived.

#include "vector3.h"

typedef int Int;

struct TerrainLighting
{
    float ambient[3];
    float diffuse[3];
    float lightPos[3];
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
    virtual void Set_Transform(const void *value);

    void Set_Ambient(const Vector3 &value) { m_ambient = value; }
    void Set_Diffuse(const Vector3 &value) { m_diffuse = value; }
    void Set_Specular(const Vector3 &value) { m_specular = value; }

private:
    unsigned char m_pad[0xd8 - 4];
    Vector3 m_ambient;
    Vector3 m_diffuse;
    Vector3 m_specular;
};

// This is the same internal helper body as the matched 0x006E9760 body.
// Declaring the scalar first is a TU-local VC7.1 ABI view: the compiler still
// passes TerrainLighting in EAX, LightClass ** in EDX, and scale on the stack,
// while it emits the retail call-site evaluation order.
static void updateLights(float scale, const TerrainLighting *lighting,
    LightClass **lights)
{
    Int i = 0;
    while (i < 4)
    {
        if (lights[i])
        {
            lights[i]->Set_Ambient(Vector3(0.0f, 0.0f, 0.0f));
            lights[i]->Set_Diffuse(Vector3(
                lighting[i].diffuse[0] * scale,
                lighting[i].diffuse[1] * scale,
                lighting[i].diffuse[2] * scale));
            lights[i]->Set_Specular(Vector3(0, 0, 0));
        }

        ++i;
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

class GlobalData
{
private:
    unsigned char m_padding00[0x218];

public:
    Int m_timeOfDay;
};

extern GlobalData *TheWritableGlobalData;
extern BfmeGlobPB *g_bfmeGlobPB;

class W3DDisplay
{
public:
    virtual void rva006E9940(float scale);

private:
    unsigned char m_padding04[0x140];
    LightClass *m_myLight[4];
    LightClass *m_myLightSecond[4];
};

// ?rva006E9940@W3DDisplay@@UAEXM@Z
void W3DDisplay::rva006E9940(float scale)
{
    const char *lighting = reinterpret_cast<const char *>(TheWritableGlobalData) +
        TheWritableGlobalData->m_timeOfDay * 0x6c;
    const TerrainLighting *first =
        reinterpret_cast<const TerrainLighting *>(lighting + 0x4ac);
    const TerrainLighting *second =
        reinterpret_cast<const TerrainLighting *>(lighting + 0x734);

    if (g_bfmeGlobPB)
    {
        g_bfmeGlobPB->Set_Ambient_Light(Vector3(
            first->ambient[0] * scale,
            first->ambient[1] * scale,
            first->ambient[2] * scale));
        g_bfmeGlobPB->m_ambient = Vector3(
            second->ambient[0] * scale,
            second->ambient[1] * scale,
            second->ambient[2] * scale);
    }

    updateLights(scale, first,
        reinterpret_cast<LightClass **>(reinterpret_cast<char *>(this) + 0x144));
    updateLights(scale, second,
        reinterpret_cast<LightClass **>(reinterpret_cast<char *>(this) + 0x154));
}
