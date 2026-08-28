// cl: /DNDEBUG /MD /EHsc

class HordeGarrisonContainModuleData
{
public:
    HordeGarrisonContainModuleData();
    virtual ~HordeGarrisonContainModuleData();

private:
    unsigned char m_pad[0x220];
};

class RS_Member
{
public:
    RS_Member();

public:
    unsigned int m_dummy;
    unsigned int m_second;
};

class TC_Triple
{
public:
    float m_x;
    float m_y;
    float m_z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TunnelContain.h
class TunnelContainModuleData : public HordeGarrisonContainModuleData
{
public:
    TunnelContainModuleData();

private:
    RS_Member m_member;
    unsigned int m_b;
    unsigned int m_c;
    float m_framesForFullHeal;
    unsigned char m_d;
    unsigned char m_e;
    unsigned char m_padding[2];
    TC_Triple m_values;
};

// ??0TunnelContainModuleData@@QAE@XZ
TunnelContainModuleData::TunnelContainModuleData()
    : m_b(0), m_c(0), m_values()
{
    m_member.m_second = 0;
    m_d = 0;
    m_e = 0;
    m_framesForFullHeal = 1.0f;
}
