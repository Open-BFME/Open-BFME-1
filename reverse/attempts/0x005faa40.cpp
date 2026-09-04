// ?d_005faa40@@YAXXZ
// partial score=0.86 date=2026-09-04
extern float GetGameClientRandomValueReal(float low, float high, char *file, int line);

namespace FXParticleSystem {

struct Coord3D {
    void scale(float scale)
    {
        x *= scale;
        y *= scale;
        z *= scale;
    }

    float x;
    float y;
    float z;
};

inline Coord3D operator*(const Coord3D &value, float scale)
{
    Coord3D result;
    result.x = value.x * scale;
    result.y = value.y * scale;
    result.z = value.z * scale;
    return result;
}

extern Coord3D *getRandomUnitVector(Coord3D *result);

class SphereEmissionVolumeModule {
public:
    Coord3D getPosition(float, float, float, float);

private:
    char m_base[0x20];
    bool m_hollow;
    char m_pad[3];
    float m_radius;
};

Coord3D SphereEmissionVolumeModule::getPosition(float, float, float, float)
{
    char *source = "F:\\bfme\\Code\\gameengine\\Source\\GameClient\\System\\FXParticleSystem\\fxpsemitterspherevolumemodule.cpp";
    float radius = m_hollow ? m_radius : GetGameClientRandomValueReal(0.0f, m_radius, source, 86);
    Coord3D randomPoint;
    Coord3D result = *getRandomUnitVector(&randomPoint);
    return result * radius;
}

}
// cl: /DNDEBUG /MD /GX- /O2 /Ob2
