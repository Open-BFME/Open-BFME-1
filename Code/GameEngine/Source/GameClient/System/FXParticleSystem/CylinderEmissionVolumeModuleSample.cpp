#include <math.h>

extern float GetGameClientRandomValueReal(float low, float high, char *file, int line);

namespace FXParticleSystem {

struct Coord3D {
    Coord3D(float xValue, float yValue, float zValue) : x(xValue), y(yValue), z(zValue) {}

    float x;
    float y;
    float z;
};

class CylinderEmissionVolumeModule {
public:
    Coord3D getPosition(float, float, float, float);

private:
    char m_base[0x20];
    bool m_hollow;
    char m_pad[3];
    float m_radius;
    float m_length;
    float m_centerX;
    float m_centerY;
    float m_centerZ;
};

Coord3D CylinderEmissionVolumeModule::getPosition(float, float, float, float)
{
    char *source = "F:\\bfme\\Code\\gameengine\\Source\\GameClient\\System\\FXParticleSystem\\fxpsemittercylindervolumemodule.cpp";
    float angle = GetGameClientRandomValueReal(0.0f, 6.28318530717958647692f, source, 93);
    float radius = m_hollow ? m_radius : GetGameClientRandomValueReal(0.0f, m_radius, source, 99);

    Coord3D result(0.0f, 0.0f, 0.0f);
    result.x = radius * (float)cos(angle) + m_centerX;
    result.y = radius * (float)sin(angle) + m_centerY;

    float halfLength = m_length * 0.5f;
    float z = GetGameClientRandomValueReal(-halfLength, halfLength, source, 105) + m_centerZ;
    return Coord3D(result.x, result.y, z);
}

}
