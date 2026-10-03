// cl: /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad
// Open-BFME: state initializer reconstructed from retail RVA 0x0095C7F0.

#include "WW3D2/ww3d.h"

class Rva0095C7F0State
{
public:
    void initialize(void);

private:
    char m_pad0[0x2C];
    int m_syncTime;
    int m_value30;
    int m_value34;
};

void Rva0095C7F0State::initialize(void)
{
    m_syncTime = WW3D::Get_Sync_Time();
    m_value30 = 0;
    m_value34 = 0;
}
