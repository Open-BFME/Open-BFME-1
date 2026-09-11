// ?getPosition@SphereEmissionVolumeModule@FXParticleSystem@@QAE?AUCoord3D@2@MMMM@Z
// partial score=0.9 date=2026-09-10
extern float GetGameClientRandomValueReal(float low, float high, char *file, int line);

namespace FXParticleSystem {

struct Coord3D {
    Coord3D() {}

    Coord3D(const Coord3D &that)
    {
        x = that.x;
        y = that.y;
        z = that.z;
    }

    ~Coord3D()
    {
    }

    float x;
    float y;
    float z;
};

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
    getRandomUnitVector(&randomPoint);
    Coord3D result = randomPoint;
    result.x *= radius;
    result.y *= radius;
    result.z *= radius;
    return result;
}

}
// cl: /DNDEBUG /MD /GX- /O2 /Ob2
