// Box primary vtable slot6 callback, retail RVA0x005F8890, full464 bytes.
// Four unused explicit stack words remain opaque. Hidden Coord3D result
// plus those words are callee-popped by ret0x14. The value copy/destructor
// preserves the observed aggregate return lifetime.
extern int GetGameClientRandomValue(int low, int high, char *file, int line);
extern float GetGameClientRandomValueReal(float low, float high,
    char *file, int line);

namespace FXParticleSystem {

struct Rva005F8890Coord3D {
    Rva005F8890Coord3D() {}
    Rva005F8890Coord3D(const Rva005F8890Coord3D &that) {
        x = that.x;
        y = that.y;
        z = that.z;
    }
    ~Rva005F8890Coord3D() {}
    float x;
    float y;
    float z;
};

class Rva005F8890BoxEmissionVolumeModule {
public:
    // Unused prefix slots are placeholders; no signature claims or bodies.
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0C(); virtual void slot10(); virtual void slot14();
    virtual Rva005F8890Coord3D Rva005F8890Sample(unsigned int, unsigned int, unsigned int, unsigned int);

private:
    char m_base[0x1c];
    bool m_hollow;
    char m_pad[3];
    float m_extentX;
    float m_extentY;
    float m_extentZ;
};

Rva005F8890Coord3D
Rva005F8890BoxEmissionVolumeModule::Rva005F8890Sample(
    unsigned int, unsigned int, unsigned int, unsigned int)
{
    char *source = "F:\\bfme\\Code\\gameengine\\Source\\GameClient\\System\\FXParticleSystem\\fxpsemitterboxvolumemodule.cpp";
    Rva005F8890Coord3D result;

    if (m_hollow) {
        int side = GetGameClientRandomValue(0, 6, source, 108);

        if (side % 3 == 0) {
            result.x = GetGameClientRandomValueReal(-m_extentX, m_extentX, source, 111);
            result.y = GetGameClientRandomValueReal(-m_extentY, m_extentY, source, 112);
            if (side == 0)
                result.z = -m_extentZ;
            else
                result.z = m_extentZ;
        } else if (side % 3 == 1) {
            result.y = GetGameClientRandomValueReal(-m_extentY, m_extentY, source, 121);
            result.z = GetGameClientRandomValueReal(-m_extentZ, m_extentZ, source, 122);
            if (side == 1)
                result.x = -m_extentX;
            else
                // Retail preserves the upstream Box sampler's Y-extent typo.
                result.x = m_extentY;
        } else if (side % 3 == 2) {
            result.x = GetGameClientRandomValueReal(-m_extentX, m_extentX, source, 131);
            result.z = GetGameClientRandomValueReal(-m_extentZ, m_extentZ, source, 132);
            if (side == 2)
                result.y = -m_extentY;
            else
                result.y = m_extentY;
        }
    } else {
        result.x = GetGameClientRandomValueReal(-m_extentX, m_extentX, source, 140);
        result.y = GetGameClientRandomValueReal(-m_extentY, m_extentY, source, 141);
        result.z = GetGameClientRandomValueReal(-m_extentZ, m_extentZ, source, 142);
    }

    return result;
}

}
