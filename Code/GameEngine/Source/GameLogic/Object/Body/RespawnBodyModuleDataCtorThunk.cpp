// cl: /DNDEBUG /MD /EHsc

class RespawnBodyModuleDataBase
{
public:
    RespawnBodyModuleDataBase();
    virtual ~RespawnBodyModuleDataBase();

private:
    unsigned char m_data[0x58];
};

struct RespawnPolicy
{
    unsigned int values[6];
};

class RespawnPolicyMember
{
public:
    RespawnPolicyMember();
    ~RespawnPolicyMember();
    void setPolicies(RespawnPolicy first, RespawnPolicy second);

private:
    unsigned int m_value;
};

extern RespawnPolicy g_defaultRespawnPolicy;

class RespawnBodyModuleData : public RespawnBodyModuleDataBase
{
public:
    RespawnBodyModuleData();

private:
    RespawnPolicyMember m_policy;
    bool m_enabled;
};

// ??0RespawnBodyModuleData@@QAE@XZ
RespawnBodyModuleData::RespawnBodyModuleData()
    : RespawnBodyModuleDataBase(), m_policy()
{
    m_policy.setPolicies(g_defaultRespawnPolicy, g_defaultRespawnPolicy);
    m_enabled = true;
}
