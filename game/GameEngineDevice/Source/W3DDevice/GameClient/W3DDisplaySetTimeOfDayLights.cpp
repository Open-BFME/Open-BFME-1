// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
//
// The 0x006EBAF0 helper updates four directional lights from one terrain-light
// group.  W3DDisplay::setTimeOfDay calls it for the two four-light groups at
// 0x006EBC30.  The retail caller passes the terrain-light pointer in EAX and
// the LightClass array in EBX, which MSVC emits for this static helper.

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
            mtx.Set(Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(ol->lightPos.x, ol->lightPos.y, ol->lightPos.z), Vector3(0, 0, 0));
            myLight[i]->Set_Transform(mtx);

        }

        ++i;
        ++ol;

    }

}

void updateTimeOfDayLights(const TerrainLighting *ol, LightClass **myLight)
{

    updateLights(ol, myLight);

}
