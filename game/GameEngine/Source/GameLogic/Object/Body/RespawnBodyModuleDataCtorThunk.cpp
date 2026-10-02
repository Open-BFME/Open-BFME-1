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

// The default policy is retail's global at 0x012ED8B8, which KindOf.cpp owns as
// `const BitFlags<192> KINDOFMASK_NONE`. This TU's RespawnPolicy is only a
// six-word view of that object, so the canonical extern is forward declared here
// and the view is cast at the use below. BitFlags is a class template, so its
// forward declaration mangles KINDOFMASK_NONE as
// ?KINDOFMASK_NONE@@3V?$BitFlags@$0MA@@@B -- the one symbol KindOf.cpp defines.
template <int NUMBITS> class BitFlags;
extern const BitFlags<192> KINDOFMASK_NONE;

class RespawnBodyModuleData : public RespawnBodyModuleDataBase
{
public:
    RespawnBodyModuleData();

    // Retail scalar wrapper 0x214AC0 calls complete-destructor ILT 0x1BE1E
    // (target 0x212BB0). Keep that out-of-line call instead of emitting an
    // implicit destructor from this constructor-only layout view.
    virtual ~RespawnBodyModuleData();

private:
    RespawnPolicyMember m_policy;
    bool m_enabled;
};

// ??0RespawnBodyModuleData@@QAE@XZ
RespawnBodyModuleData::RespawnBodyModuleData()
    : RespawnBodyModuleDataBase(), m_policy()
{
    m_policy.setPolicies(*(const RespawnPolicy *)&KINDOFMASK_NONE,
                         *(const RespawnPolicy *)&KINDOFMASK_NONE);
    m_enabled = true;
}
