// ?Rva006FE200@Rva006FE200Owner@@QAEXPBUCoord2D@@M@Z
// The owner remains opaque; vtable slot 5 updates position and the rotation angle.
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Include
#include "Lib/Coord2D.h"
#include "Lib/Coord3D.h"
#include <math.h>

extern float g_Va012F8274;
extern float g_Va012BAC54;
extern float g_Va012BAC50;
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
class BfmeLivingWorldManager {
public:
    void rva00615a70(const Coord2D &point);
};

#define DECLARE_TEN(prefix) \
    virtual void prefix##0(); virtual void prefix##1(); \
    virtual void prefix##2(); virtual void prefix##3(); \
    virtual void prefix##4(); virtual void prefix##5(); \
    virtual void prefix##6(); virtual void prefix##7(); \
    virtual void prefix##8(); virtual void prefix##9();

class Rva006FE200Owner {
public:
    DECLARE_TEN(slotA)
    DECLARE_TEN(slotB)
    virtual void slot20(); virtual void slot21(); virtual void slot22();
    virtual void slot23(); virtual void slot24();
    virtual void setPosition(const Coord3D *position);
    void Rva006FE200(const Coord2D *dir, float turnDelta);
private:
    unsigned char m_unmodelled_04[0xA8 - 4];
    Coord3D m_position;
    unsigned char m_unmodelled_B4[0xCC - 0xB4];
    float m_facing;
    unsigned char m_unmodelled_D0[0xE4 - 0xD0];
    float m_gateMetric;
};
#undef DECLARE_TEN

// ?Rva006FE200@Rva006FE200Owner@@QAEXPBUCoord2D@@M@Z
void Rva006FE200Owner::Rva006FE200(const Coord2D *dir, float turnDelta) {
    if (dir) {
        Coord2D delta;
        delta.x = dir->x * 0.5f;
        delta.y = dir->y * 0.5f;
        if (!(m_gateMetric > g_Va012F8274)) {
            if (delta.x != 0.0f || delta.y != 0.0f) {
                Coord3D position;
                position.x = m_position.x;
                position.y = m_position.y;
                position.z = m_position.z;
                float theta = -m_facing;
                float s = (float)sin(theta);
                float c = (float)cos(theta);
                Coord3D rotated;
                rotated.x = c * delta.x - s * delta.y;
                rotated.y = c * delta.y + s * delta.x;
                position.x += 0.25f * rotated.x;
                position.y -= 0.25f * rotated.y;
                setPosition(&position);
                if (TheLivingWorldManager) {
                    Coord2D sample;
                    sample.x = position.x;
                    sample.y = position.y;
                    ((BfmeLivingWorldManager *)TheLivingWorldManager)->rva00615a70(sample);
                }
            }
            m_facing += g_Va012BAC54 * turnDelta;
            if (m_facing < -g_Va012BAC50)
                m_facing = -g_Va012BAC50;
            if (m_facing > g_Va012BAC50)
                m_facing = g_Va012BAC50;
        }
    }
}
