// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the RadarUpgradeModuleData ctor dump to clean C++.
// Same ICF-folded body as StealthUpgradeModuleData at 0x129C10.

#include <string.h>

struct SixDwords
{
    SixDwords() { memset(this, 0, sizeof(*this)); }

    unsigned int v[6];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RadarUpgrade.h
class RadarUpgradeModuleData
{
public:
    RadarUpgradeModuleData();

private:
    SixDwords m_block0;
    SixDwords m_block1;
    unsigned int m0, m1, m2, m3, m4, m5, m6, m7, m8, m9;
    unsigned char m_byte;
    int m_sentinel;
    int m_a;
    int m_b;
};

// ??0RadarUpgradeModuleData@@QAE@XZ
RadarUpgradeModuleData::RadarUpgradeModuleData()
    : m_block0(),
      m_block1(),
      m0(0), m1(0), m2(0), m3(0), m4(0), m5(0), m6(0), m7(0), m8(0), m9(0),
      m_byte(0),
      m_sentinel(-1),
      m_a(0),
      m_b(0)
{
}
