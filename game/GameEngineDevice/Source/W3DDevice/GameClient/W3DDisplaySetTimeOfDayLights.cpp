// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
//
// The 0x006EBAF0 helper updates four directional lights from one terrain-light
// group.  W3DDisplay::setTimeOfDay calls it for the two four-light groups at
// 0x006EBC30.  The retail caller passes the terrain-light pointer in EAX and
// the LightClass array in EBX, which MSVC emits for this static helper.
//
// W3DDisplay::setTimeOfDay (0x006EBC30, vtable 0x0111EDD0 slot 37; ilt_oracle
// confirms the decoration exactly) lives here with it: BFME keeps two
// terrain-light tables per time of day and feeds both to the scene and to the
// two four-light groups before forwarding the time to the terrain object.

#include "vector3.h"
#include "matrix3d.h"

typedef int Int;

struct RGBColor
{

    float red;
    float green;
    float blue;

};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

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
            mtx.Set(Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(ol->lightPos.x, ol->lightPos.y, ol->lightPos.z), Vector3(0, 0, 0));
            myLight[i]->Set_Transform(mtx);

        }

        ++i;
        ++ol;

    }

}

enum TimeOfDay { TIME_OF_DAY_INVALID = 0 };

// The two terrain-light tables GlobalData keeps per time of day, three lights each.
class GlobalData
{
public:
    unsigned char m_unreconstructed_000[0x4ac];
    TerrainLighting m_terrainLighting[6][3];            // +0x4AC
    TerrainLighting m_terrainObjectsLighting[6][3];     // +0x734
};

extern GlobalData *TheWritableGlobalData;

class RTS3DScene
{
public:
    virtual void unused00();
    virtual void unused01();
    virtual void unused02();
    virtual void unused03();
    virtual void unused04();
    virtual void unused05();
    virtual void Set_Ambient_Light(const Vector3 &color);   // +0x18

    unsigned char m_unreconstructed_004[0x140 - 4];
    Vector3 m_objectAmbient;                            // +0x140
};

// TheTerrainRenderObject's time-of-day setter, retail 0x006C8E00.
class Rva006C8E00Dispatch
{
public:
    void invoke(Int tod);
};

class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class View
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
    virtual void forceRedraw();                         // +0x50
};

extern View *TheTacticalView;

class DX8Wrapper
{
public:
    static bool Owns_Device_Lock();
};

class W3DDisplay
{
public:
    virtual void setTimeOfDay(TimeOfDay tod);

    static RTS3DScene *m_3DScene;

private:
    unsigned char m_unreconstructed_004[0x144 - 4];
    LightClass *m_myLight[4];                           // +0x144
    LightClass *m_myObjectLight[4];                     // +0x154
};

// ?setTimeOfDay@W3DDisplay@@UAEXW4TimeOfDay@@@Z
void W3DDisplay::setTimeOfDay(TimeOfDay tod)
{

    const TerrainLighting *ol = &TheWritableGlobalData->m_terrainLighting[tod][0];
    const TerrainLighting *objl = &TheWritableGlobalData->m_terrainObjectsLighting[tod][0];

    if (m_3DScene)
    {

        m_3DScene->Set_Ambient_Light(Vector3(ol->ambient.red, ol->ambient.green, ol->ambient.blue));
        m_3DScene->m_objectAmbient = Vector3(objl->ambient.red, objl->ambient.green, objl->ambient.blue);

    }

    updateLights(ol, m_myLight);
    updateLights(objl, m_myObjectLight);

    if (TheTerrainRenderObject)
    {

        ((Rva006C8E00Dispatch *)TheTerrainRenderObject)->invoke(tod);
        if (DX8Wrapper::Owns_Device_Lock())
            TheTacticalView->forceRedraw();

    }

}

void updateTimeOfDayLights(const TerrainLighting *ol, LightClass **myLight)
{

    updateLights(ol, myLight);

}
