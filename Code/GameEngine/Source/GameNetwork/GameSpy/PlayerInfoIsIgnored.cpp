// cl: /O2 /DNDEBUG /MD /EHsc-
#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// BFME vtable 0x011188D0: +0x12c routes via ILT1500 to isSavedIgnored632D20;
// +0x144 routes via ILT154A6 to isIgnored635600. Both targets are matched.
// The upstream interface has different slot indices, so keep this ABI view local.
class GameSpyInfoView
{
public:
#define GS_SLOT(n) virtual void slot##n();
    GS_SLOT(00) GS_SLOT(01) GS_SLOT(02) GS_SLOT(03) GS_SLOT(04)
    GS_SLOT(05) GS_SLOT(06) GS_SLOT(07) GS_SLOT(08) GS_SLOT(09)
    GS_SLOT(10) GS_SLOT(11) GS_SLOT(12) GS_SLOT(13) GS_SLOT(14)
    GS_SLOT(15) GS_SLOT(16) GS_SLOT(17) GS_SLOT(18) GS_SLOT(19)
    GS_SLOT(20) GS_SLOT(21) GS_SLOT(22) GS_SLOT(23) GS_SLOT(24)
    GS_SLOT(25) GS_SLOT(26) GS_SLOT(27) GS_SLOT(28) GS_SLOT(29)
    GS_SLOT(30) GS_SLOT(31) GS_SLOT(32) GS_SLOT(33) GS_SLOT(34)
    GS_SLOT(35) GS_SLOT(36) GS_SLOT(37) GS_SLOT(38) GS_SLOT(39)
    GS_SLOT(40) GS_SLOT(41) GS_SLOT(42) GS_SLOT(43) GS_SLOT(44)
    GS_SLOT(45) GS_SLOT(46) GS_SLOT(47) GS_SLOT(48) GS_SLOT(49)
    GS_SLOT(50) GS_SLOT(51) GS_SLOT(52) GS_SLOT(53) GS_SLOT(54)
    GS_SLOT(55) GS_SLOT(56) GS_SLOT(57) GS_SLOT(58) GS_SLOT(59)
    GS_SLOT(60) GS_SLOT(61) GS_SLOT(62) GS_SLOT(63) GS_SLOT(64)
    GS_SLOT(65) GS_SLOT(66) GS_SLOT(67) GS_SLOT(68) GS_SLOT(69)
    GS_SLOT(70) GS_SLOT(71) GS_SLOT(72) GS_SLOT(73) GS_SLOT(74)
    virtual bool isSavedIgnored(int profileID);
    GS_SLOT(76) GS_SLOT(77) GS_SLOT(78) GS_SLOT(79) GS_SLOT(80)
    virtual bool isIgnored(AsciiString nick);
#undef GS_SLOT
};
class GameSpyInfo;
extern GameSpyInfo *TheGameSpyInfo;

// BFME layout independently used by matched GameSpyInfo::updatePlayerInfo636C60.
// The third AsciiString is absent in the Zero Hour PlayerInfo declaration.
// That shifts profileID to +0x14; the full BFME record occupies 52 bytes.
// Only the nickname and profile ID identities are needed here. Existing
// reconstructions disagree on unused field labels (the matched lobby display
// helper reads its side at +0x2C), so do not inherit their guessed names.
class PlayerInfo
{
public:
    AsciiString m_name;
    AsciiString m_unmodelledString04;
    AsciiString m_unmodelledString08;
    int m_unmodelled0c[2];
    int m_profileID;
    int m_unmodelled18[7];
    bool isIgnored();
};

// 0x006318A0, 56 bytes: BFME PlayerInfo ignore query, not a room sender.
// Reference algorithm: PeerDefs.cpp PlayerInfo::isIgnored. The named PlayerInfoMap
// owner, profile field, and independently named vtable targets establish identity.
bool PlayerInfo::isIgnored()
{
    return m_profileID ? ((GameSpyInfoView *)TheGameSpyInfo)->isSavedIgnored(m_profileID)
                       : ((GameSpyInfoView *)TheGameSpyInfo)->isIgnored(m_name);
}
