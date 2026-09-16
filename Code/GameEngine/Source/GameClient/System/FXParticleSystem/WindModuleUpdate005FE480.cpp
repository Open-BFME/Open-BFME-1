// Wind-family update at RVA 0x005FE480, complete 408-byte RET0 body.
// The matched constructor at 0x005FEAD0 (WindModuleConstructor.cpp) installs
// primary table 0x011148EC, whose slot 1 via ILT 0xBD20 reaches this body.
// Tables 0x01111724 and 0x011120CC use the same slot. The original class and
// method names are unproven, so the owner retains its address token.
// The constructor independently supplies the offsets used below. Retail's
// source-path literal and all seven diagnostic line values are preserved.
// cl: /DNDEBUG /MD /EHsc
#include <math.h>
#pragma intrinsic(fabs)

// Signature from client_random_value.h and matched random_value.cpp.
// That header's base_type.h currently pulls in the full PreRTS dependency
// graph; this function declaration needs none of its object layouts.
extern float GetGameClientRandomValueReal(float, float, char *, int);

class Rva005FE480Owner {
public:
    void update();
    char m_prefix[0x20];
    int m_at20;
    char m_at24[0x0C];
    float m_at30, m_at34, m_at38, m_at3C;
    float m_at40, m_at44, m_at48, m_at4C, m_at50, m_at54;
    bool m_at58;
};

void Rva005FE480Owner::update()
{
    const char *file = "F:\\bfme\\Code\\gameengine\\Source\\GameClient\\System\\FXParticleSystem\\fxpswindmodule.cpp";
    switch (m_at20) {
    case 3:
        if (m_at34 == 0.0f)
            m_at34 = GetGameClientRandomValueReal(m_at38, m_at3C, (char *)file, 0x154);
        m_at30 += m_at34;
        if (m_at30 > 6.2831855f)
            m_at30 -= 6.2831855f;
        else if (m_at30 < 0.0f)
            m_at30 += 6.2831855f;
        break;
    case 2:
        {
            float lower = m_at40;
            float upper = m_at4C;
            float halfRange = (upper - lower) * 0.5f;
            float speed = (1.0f - (float)fabs(halfRange - m_at30 + lower) / halfRange) * m_at34;
            if (speed < 0.005f)
                speed = 0.005f;
            if (m_at58) {
                m_at30 += speed;
                if (m_at30 >= upper) {
                    m_at58 = false;
                    m_at34 = GetGameClientRandomValueReal(m_at38, m_at3C, (char *)file, 0x120);
                    m_at40 = GetGameClientRandomValueReal(m_at44, m_at48, (char *)file, 0x125);
                    m_at4C = GetGameClientRandomValueReal(m_at50, m_at54, (char *)file, 0x128);
                }
            } else {
                m_at30 -= speed;
                if (m_at30 <= lower) {
                    m_at58 = true;
                    m_at34 = GetGameClientRandomValueReal(m_at38, m_at3C, (char *)file, 0x13C);
                    m_at40 = GetGameClientRandomValueReal(m_at44, m_at48, (char *)file, 0x141);
                    m_at4C = GetGameClientRandomValueReal(m_at50, m_at54, (char *)file, 0x144);
                }
            }
        }
        break;
    }
}
