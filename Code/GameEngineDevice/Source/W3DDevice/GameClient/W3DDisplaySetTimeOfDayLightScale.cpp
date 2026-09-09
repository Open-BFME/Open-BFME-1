// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib

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

static void updateLights(const TerrainLighting *lighting, LightClass **lights,
    float scale)
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

void updateTimeOfDayLightScale(const TerrainLighting *lighting,
    LightClass **lights, float scale)
{
    updateLights(lighting, lights, scale);
}
