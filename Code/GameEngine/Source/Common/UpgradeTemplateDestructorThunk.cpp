// cl: /DNDEBUG /MD /EHsc
// readable body of ??1UpgradeTemplate@@MAE@XZ: Code/GameEngine/Source/Common/System/Upgrade.cpp
// Open-BFME5: lift MASM dump to standalone C++ thunk.
//
// Named members come from retail's INI field table at 0x00C88B60 joined to
// upstream's m_upgradeFieldParseTable on the key: retail supplies the offset,
// upstream only the name. BuildTime (+0x18) and BuildCost (+0x1C) are named in
// the assignment TU but not here -- this TU covers them with one padding run,
// and a name on a padding array would be a claim about a layout it does not
// make.

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
    unsigned int m_type;
    UpgradeStringMember m_member08;
    unsigned char m_pad0c[4];
    UpgradeStringMember m_displayNameLabel;
    UpgradeStringMember m_member14;
    unsigned char m_pad18[0x0c];
    UpgradeStringMember m_member24;
    UpgradeAudioMember m_researchSound;
    UpgradeAudioMember m_unitSpecificSound;
    unsigned char m_pad108[8];
    UpgradeStringMember m_buttonImageName;
    unsigned char m_pad114[4];
    UpgradeStringMember m_member118;
};

// ??1UpgradeTemplate@@MAE@XZ
UpgradeTemplate::~UpgradeTemplate()
{
}
