// cl: /DNDEBUG /MD /EHsc

#include <string.h>

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

    unsigned int m_dummy;
    volatile unsigned int m_second;
};

struct SixDwords
{
    SixDwords() { memset(this, 0, sizeof(*this)); }

    volatile unsigned int v[6];
};

class LevelGrantSpecialPowerModuleData : public SpecialAbilityUpdateModuleData
{
public:
    LevelGrantSpecialPowerModuleData();

private:
    volatile unsigned int m_field254;
    unsigned int m_field258;
    volatile unsigned int m_field25c;
    RS_Member m_member;
    SixDwords m_fields268;
    unsigned char m_field280;
};

// ??0LevelGrantSpecialPowerModuleData@@QAE@XZ
LevelGrantSpecialPowerModuleData::LevelGrantSpecialPowerModuleData()
    : m_field258(0), m_fields268()
{
    m_field25c = 0;
    m_member.m_second = 0;
    m_field254 = 1;
    memset(&m_fields268, 0, sizeof(m_fields268));
    m_field280 = 0;
}
