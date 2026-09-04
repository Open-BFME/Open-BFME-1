// ?d_005f9ab0@@YAXXZ
// partial score=0.99 date=2026-08-30
extern float GetGameClientRandomValueReal(float low, float high, char *file, int line);

namespace FXParticleSystem {

struct LineCoord3D {
    __forceinline LineCoord3D() {}
    __forceinline LineCoord3D(float xValue, float yValue, float zValue)
        : x(xValue), y(yValue), z(zValue) {}

    float x;
    float y;
    float z;
};

__forceinline LineCoord3D makeLineCoord(float z, float y, float x)
{
    return LineCoord3D(x, y, z);
}

class LineEmissionVolumeModule {
public:
    LineCoord3D getPosition(float, float, float, float);

private:
    char m_base[0x24];
    LineCoord3D m_start;
    LineCoord3D m_end;
};

LineCoord3D LineEmissionVolumeModule::getPosition(float, float, float, float)
{
    LineCoord3D start = m_start;
    LineCoord3D end = m_end;
    LineCoord3D delta(end.x - start.x, end.y - start.y, end.z - start.z);
    volatile float scale = GetGameClientRandomValueReal(
        0.0f,
        1.0f,
        "F:\\bfme\\Code\\gameengine\\Source\\GameClient\\System\\FXParticleSystem\\fxpsemitterlinevolumemodule.cpp",
        114);
    return LineCoord3D(
        scale * delta.z + start.z,
        scale * delta.y + start.y,
        scale * delta.x + start.x);
}

}
