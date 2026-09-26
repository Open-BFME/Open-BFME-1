// cl: /DNDEBUG /MD /EHsc

#include <string.h>

#include "../../../../Include/GameLogic/Rva0039D550.h"

// BFME base view: named SpecialAbilityUpdate factory 0x00114140 allocates
// 0x254 bytes and calls ILT 0x0003F503 -> matched constructor 0x002A5AA0.
// This derived constructor calls that same base. Keep its witnessed size:
// BFME puts AudioEventRTS at +8/+78/+e8/+158, unlike the vendored Generals
// header, which begins with AsciiStrings. No compatible Code header exists.
class SpecialAbilityUpdateModuleData
{
public:
    SpecialAbilityUpdateModuleData();
    virtual ~SpecialAbilityUpdateModuleData();

private:
    unsigned char m_pad[0x250];
};

class RS_Member
{
public:
    RS_Member();

    // Local emission carrier: these are owner offsets +0x260/+0x264,
    // not an identified original aggregate type. The aligned owner table
    // names AcceptanceFilter and LevelFX at those absolute offsets.
    unsigned int m_acceptanceFilter;
    volatile unsigned int m_levelFX;
};

struct SixDwords
{
    SixDwords() { memset(this, 0, sizeof(*this)); }

    volatile unsigned int v[6];
};

// Named factory 0x00120010 passes ILT 0x0004128B -> 0x0025FCF0.
// Its own table at RVA 0x00CB5AD0 names NumberOfLevels/+254, Experience/+258,
// RadiusEffect/+25c, AcceptanceFilter/+260, LevelFX/+264, AffectsKindOf/+268
// and UseKindOf/+280. Preserve the raw/volatile constructor storage here;
// RadiusEffect is parsed as a float and the six-word carrier is not a claim
// about the original bit-mask template identity.
class LevelGrantSpecialPowerModuleData : public SpecialAbilityUpdateModuleData
{
public:
    LevelGrantSpecialPowerModuleData();
    virtual ~LevelGrantSpecialPowerModuleData();

private:
    volatile unsigned int m_numberOfLevels;
    unsigned int m_experience;
    volatile unsigned int m_radiusEffect;
    RS_Member m_member;
    SixDwords m_affectsKindOf;
    unsigned char m_useKindOf;
};

// ??0LevelGrantSpecialPowerModuleData@@QAE@XZ
LevelGrantSpecialPowerModuleData::LevelGrantSpecialPowerModuleData()
    : m_experience(0), m_affectsKindOf()
{
    m_radiusEffect = 0;
    m_member.m_levelFX = 0;
    m_numberOfLevels = 1;
    memset(&m_affectsKindOf, 0, sizeof(m_affectsKindOf));
    m_useKindOf = 0;
}

class __declspec(novtable) LevelGrantSpecialPowerModuleData;

// ??1LevelGrantSpecialPowerModuleData@@UAE@XZ
LevelGrantSpecialPowerModuleData::~LevelGrantSpecialPowerModuleData()
{
    reinterpret_cast<Rva0039D550 *>(&m_member.m_acceptanceFilter)->~Rva0039D550();
}
