// cl: /DNDEBUG /MD /EHsc
// readable body of ??1UpgradeTemplate@@MAE@XZ: Code/GameEngine/Source/Common/System/Upgrade.cpp
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class UpgradeStringMember
{
public:
    ~UpgradeStringMember();

private:
    char *m_text;
};

class UpgradeAudioMember
{
public:
    virtual ~UpgradeAudioMember();

private:
    unsigned char m_data[0x6c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeTemplate
{
protected:
    virtual ~UpgradeTemplate();

private:
    unsigned int m_pad04;
    UpgradeStringMember m_member08;
    unsigned char m_pad0c[4];
    UpgradeStringMember m_member10;
    UpgradeStringMember m_member14;
    unsigned char m_pad18[0x0c];
    UpgradeStringMember m_member24;
    UpgradeAudioMember m_member28;
    UpgradeAudioMember m_member98;
    unsigned char m_pad108[8];
    UpgradeStringMember m_member110;
    unsigned char m_pad114[4];
    UpgradeStringMember m_member118;
};

// ??1UpgradeTemplate@@MAE@XZ
UpgradeTemplate::~UpgradeTemplate()
{
}
