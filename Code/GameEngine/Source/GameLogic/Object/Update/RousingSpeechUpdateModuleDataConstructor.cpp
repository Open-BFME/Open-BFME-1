// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RousingSpeechUpdateModuleData constructor.
// The +270/+274/+278 fragments preserve the ModifierName vector's emitted
// initialization. The tracked +278 fragment is zeroed at retail 0x002654B4;
// state 1 is established at 0x002654C0 before the +280 filter constructor.
// Original fragment types remain opaque.

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

class RS_SubObj
{
public:
    RS_SubObj() : m_value(0) {}
    ~RS_SubObj();

private:
    unsigned int m_value;
};

class RS_Member
{
public:
    RS_Member();

private:
    unsigned int m_dummy;
};

// Named factory 0x0011C6C0 passes ILT 0x0002009A -> 0x00264AC0.
// Own table RVA 0x00CB6BB8 names BonusRadius/+254, SpeechDuration/+258,
// UpdateInterval/+25c, LeaderFX/+260, FollowerFX/+264, CreateWave/+268,
// WaveWidth/+26c, LevelUp/+27c and ObjectFilter/+280. Keep the existing
// raw four-byte views for floating-point and pointer fields. ModifierName
// uses the vector parser at +270, so its three fragments stay opaque.
class RousingSpeechUpdateModuleData : public SpecialAbilityUpdateModuleData
{
public:
    RousingSpeechUpdateModuleData();

private:
    unsigned int m_bonusRadius;
    unsigned int m_speechDuration;
    unsigned int m_updateInterval;
    unsigned int m_leaderFX;
    unsigned int m_followerFX;
    unsigned char m_createWave;
    unsigned int m_waveWidth;
    unsigned int m_h;
    unsigned int m_i;
    RS_SubObj m_tracked;
    unsigned char m_levelUp;
    RS_Member m_objectFilter;
};

// ??0RousingSpeechUpdateModuleData@@QAE@XZ
RousingSpeechUpdateModuleData::RousingSpeechUpdateModuleData()
    : m_bonusRadius(0), m_speechDuration(0), m_updateInterval(0),
      m_leaderFX(0), m_followerFX(0), m_createWave(0), m_waveWidth(0),
      m_h(0), m_i(0), m_levelUp(0)
{
}
