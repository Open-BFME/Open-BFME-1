// cl: /DNDEBUG /MD /EHsc

#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class HordeSiegeEngineContainModuleDataBase
{
public:
    virtual ~HordeSiegeEngineContainModuleDataBase();

private:
    unsigned char m_pad[0x220];
};

// Its retail complete destructor is a five-byte tail thunk, so folding the empty
// body here must reach the independently pinned HordeSiegeEngine base directly.
class __declspec(novtable) HordeGarrisonContainModuleData
    : public HordeSiegeEngineContainModuleDataBase
{
public:
    HordeGarrisonContainModuleData();
    virtual ~HordeGarrisonContainModuleData() {}
};

class AttributeHandleStandIn
{
public:
    AttributeHandleStandIn();
    ~AttributeHandleStandIn();

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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TunnelContain.h
class TunnelContainModuleData : public HordeGarrisonContainModuleData
{
public:
    TunnelContainModuleData();
    virtual ~TunnelContainModuleData();

private:
    AttributeHandleStandIn m_attributeHandle;
    AsciiString m_name;
    unsigned int m_c;
    float m_framesForFullHeal;
    unsigned char m_d;
    unsigned char m_e;
    unsigned char m_padding[2];
    TC_Triple m_values;
};

// ??0TunnelContainModuleData@@QAE@XZ
TunnelContainModuleData::TunnelContainModuleData()
    : m_c(0), m_values()
{
    m_attributeHandle.m_second = 0;
    m_d = 0;
    m_e = 0;
    m_framesForFullHeal = 1.0f;
}

// Suppress the derived-vftable store only in the destructor. The constructor
// above must retain it; retail teardown begins directly with member cleanup.
class __declspec(novtable) TunnelContainModuleData;

// ??1TunnelContainModuleData@@UAE@XZ
TunnelContainModuleData::~TunnelContainModuleData()
{
}
